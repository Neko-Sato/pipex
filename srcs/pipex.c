/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/10/02 05:48:10 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_pipex_local
{
	t_eval	config;
	pid_t	pid;
	int		reader;
	int		writer;
	int		tempfd;
	int		infile;
	int		outfile;
	size_t	i;
}			t_pipex_local;

static int	init_fd(t_pipex *var, t_pipex_local *sp);
static int	set_fd(t_pipex *var, t_pipex_local *sp, int is_last);
static int	section_to_execute(t_pipex *var, t_pipex_local *sp);
static int	execute_cmd(t_pipex *var, t_pipex_local *sp, size_t i);

int	pipex(t_pipex *var, char *envp[])
{
	t_pipex_local	sp;

	sp.pid = 0;
	sp.config.envp = envp;
	sp.config.path = get_path(envp);
	sp.config.execute_var.run_here = 0;
	if (init_fd(var, &sp))
	{
		free(sp.config.path);
		return (-1);
	}
	if (section_to_execute(var, &sp))
	{
		free(sp.config.path);
		return (-1);
	}
	free(sp.config.path);
	if (0 < sp.pid)
		waitpid(sp.pid, NULL, 0);
	return (0);
}

static int	init_fd(t_pipex *var, t_pipex_local *sp)
{
	if (var->here_doc)
	{
		sp->infile = here_doc_fd(var->in);
		if (sp->infile < 0)
		{
			perror("here_doc");
			return (-1);
		}
	}
	else
		sp->infile = open(var->in, O_RDONLY);
	if (sp->infile < 0)
		perror(var->in);
	if (var->append)
		sp->outfile = open(var->out, O_APPENDWRITE, S_RUWUGO);
	else
		sp->outfile = open(var->out, O_OVERWRITE, S_RUWUGO);
	if (sp->outfile < 0)
		perror(var->out);
	return (0);
}

static int	set_fd(t_pipex *var, t_pipex_local *sp, int is_last)
{
	(void)var;
	if (is_last)
		sp->writer = sp->outfile;
	else if (newpipe(&sp->tempfd, &sp->writer))
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static int	section_to_execute(t_pipex *var, t_pipex_local *sp)
{
	size_t	i;

	i = 0;
	sp->reader = sp->infile;
	while (i++ < var->len)
	{
		if (set_fd(var, sp, i == var->len))
		{
			close(sp->reader);
			return (-1);
		}
		if (execute_cmd(var, sp, i - 1))
		{
			perror("eval");
			close(sp->tempfd);
			return (-1);
		}
		sp->reader = sp->tempfd;
	}
	return (0);
}

static int	execute_cmd(t_pipex *var, t_pipex_local *sp, size_t i)
{
	if (0 < sp->reader && 0 < sp->writer)
	{
		sp->config.execute_var.stdin = sp->reader;
		sp->config.execute_var.stdout = sp->writer;
		sp->pid = eval(var->cmds[i], &sp->config);
	}
	close(sp->reader);
	close(sp->writer);
	return (-(sp->pid < 0));
}
