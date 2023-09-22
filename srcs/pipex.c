/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/23 05:41:35 by hshimizu         ###   ########.fr       */
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
	char	*str;
	size_t	i;
}			t_pipex_local;

static int	init_fd(t_pipex *var, t_pipex_local *sp);
static int	section_to_execute(t_pipex *var, t_pipex_local *sp);
static int	set_fd(t_pipex *var, t_pipex_local *sp);
static int	execute_cmd(t_pipex *var, t_pipex_local *sp);

void	pipex(t_pipex *var, char *envp[])
{
	t_pipex_local	sp;

	if (var->here_doc)
	{
		sp.str = here_doc(var->in);
		if (!sp.str)
			return ;
	}
	sp.config.envp = envp;
	sp.config.path = get_path(envp);
	if (sp.config.path)
	{
		if (!init_fd(var, &sp))
		{
			if (!section_to_execute(var, &sp))
				waitpid(sp.pid, NULL, 0);
			close(sp.tempfd);
		}
		free(sp.config.path);
	}
	if (var->here_doc)
		free(sp.str);
}

static int	init_fd(t_pipex *var, t_pipex_local *sp)
{
	if (!var->append)
		sp->tempfd = open(var->out, O_OVERWRITE, S_RUWUGO);
	else
		sp->tempfd = open(var->out, O_APPENDWRITE, S_RUWUGO);
	if (sp->tempfd < 0)
		perror(var->out);
	return (sp->tempfd < 0);
}

static int	section_to_execute(t_pipex *var, t_pipex_local *sp)
{
	sp->i = var->len;
	sp->pid = fork();
	if (sp->pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (sp->pid)
	{
		while (1)
		{
			if (set_fd(var, sp))
				exit(EXIT_FAILURE);
			if (execute_cmd(var, sp))
				exit(EXIT_FAILURE);
		}
	}
	return (0);
}

static int	set_fd(t_pipex *var, t_pipex_local *sp)
{
	sp->writer = sp->tempfd;
	if (1 < sp->i || var->here_doc)
	{
		if (ft_pipe3(&sp->reader, &sp->tempfd))
			perror("pipe");
	}
	else
	{
		sp->reader = open(var->in, O_RDONLY);
		if (sp->reader < 0)
			perror(var->in);
	}
	return (sp->reader < 0);
}

static int	execute_cmd(t_pipex *var, t_pipex_local *sp)
{
	if (sp->i < 1)
		exit(EXIT_SUCCESS);
	sp->config.execute_var.stdin = sp->reader;
	sp->config.execute_var.stdout = sp->writer;
	sp->config.execute_var.run_here = (sp->i <= 1 && !var->here_doc);
	sp->pid = eval(var->cmds[--sp->i], &sp->config);
	if (sp->pid <= 0)
	{
		if (sp->pid)
			perror("eval");
		return (1);
	}
	if (sp->i < 1 && var->here_doc)
	{
		ft_putstr_fd(sp->str, sp->tempfd);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
