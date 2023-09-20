/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 23:21:12 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t	pipex_exec(t_pipex *var, int fd[3], t_eval *config);

//	fd[0] = reader
//	fd[1] = writer
//	fd[2] = temp
void	pipex(t_pipex *var, char *envp[])
{
	t_eval	config;
	pid_t	pid;
	int		fd[3];

	config.envp = envp;
	config.path = get_path(envp);
	if (!config.path)
		return ;
	fd[2] = open(var->file2, O_WRCT, S_RUWUGO);
	if (fd[2] == -1)
		return (perror(var->file2));
	pid = pipex_exec(var, fd, &config);
	if (pid == -1)
		return (perror("fork"));
	waitpid(pid, NULL, 0);
	close(fd[2]);
	free(config.path);
}

static pid_t	pipex_exec(t_pipex *var, int fd[3], t_eval *config)
{
	size_t	i;
	pid_t	pid;

	i = var->len;
	pid = fork();
	if (pid)
		return (pid);
	while (1)
	{
		fd[1] = fd[2];
		if (1 < i)
			ft_pipe3(&fd[0], &fd[2]);
		else
			fd[0] = open(var->file1, O_RDONLY);
		ft_excption((char *[]){var->file1, "pipe"}[1 < i], fd[0] == -1);
		if (i < 1)
			exit(EXIT_SUCCESS);
		ft_memcpy(&config->execute_var, &(t_execute){.stdin = fd[0],
			.stdout = fd[1], .run_here = (i <= 1)}, sizeof(t_eval));
		pid = eval(var->cmds[--i], config);
		if (pid < 0)
			perror("eval");
		if (pid <= 0)
			exit(EXIT_FAILURE);
	}
}
