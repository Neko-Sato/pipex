/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/23 02:46:54 by hshimizu         ###   ########.fr       */
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
	t_pipex	*var;
	t_eval	config;
	pid_t	pid;
	int		reader;
	int		writer;
	int		tempfd;
	char	*str;
	size_t	i;
}			t_pipex_local;

static int	init_fd(t_pipex_local *sp);
static int	section_to_execute(t_pipex_local *sp);
static int	set_fd(t_pipex_local *sp);
static int	execute_cmd(t_pipex_local *sp);

void	pipex(t_pipex *var, char *envp[])
{
	t_pipex_local	sp;

	sp.var = var;
	if (sp.var->here_doc)
		sp.str = here_doc(sp.var->in);
	sp.config.envp = envp;
	sp.config.path = get_path(envp);
	init_fd(&sp);
	section_to_execute(&sp);
	close(sp.tempfd);
	waitpid(sp.pid, NULL, 0);
	free(sp.config.path);
	if (sp.var->here_doc)
		free(sp.str);
}

static int	init_fd(t_pipex_local *sp)
{
	if (!sp->var->append)
		sp->tempfd = open(sp->var->out, O_OVERWRITE, S_RUWUGO);
	else
		sp->tempfd = open(sp->var->out, O_APPENDWRITE, S_RUWUGO);
	return (0);
}

static int	section_to_execute(t_pipex_local *sp)
{
	sp->i = sp->var->len;
	sp->pid = fork();
	if (sp->pid)
	{
		while (1)
		{
			set_fd(sp);
			execute_cmd(sp);
		}
	}
	return (0);
}

static int	set_fd(t_pipex_local *sp)
{
	sp->writer = sp->tempfd;
	if (1 < sp->i || sp->var->here_doc)
		ft_pipe3(&sp->reader, &sp->tempfd);
	else
		sp->reader = open(sp->var->in, O_RDONLY);
	return (0);
}

static int	execute_cmd(t_pipex_local *sp)
{
	if (sp->i <= 0)
		exit(EXIT_SUCCESS);
	ft_memcpy(&sp->config.execute_var, &(t_execute){.stdin = sp->reader,
		.stdout = sp->writer, .run_here = !(1 < sp->i
			|| sp->var->here_doc)}, sizeof(t_execute));
	sp->pid = eval(sp->var->cmds[--sp->i], &sp->config);
	if (!sp->i && sp->var->here_doc)
	{
		ft_putstr_fd(sp->str, sp->tempfd);
		exit(EXIT_SUCCESS);
	}
	if (sp->pid <= 0)
		exit(EXIT_FAILURE);
	return (0);
}
