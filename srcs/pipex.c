/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 22:03:42 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eval.h"
#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//	fd[0] = reader
//	fd[1] = writer
//	fd[2] = temp
void	pipex(t_pipex *var, char *envp[])
{
	t_eval	config;
	pid_t	pid;
	size_t	i;
	int		fd[3];

	config.envp = envp;
	config.path = get_path(envp);
	pid = 0;
	fd[2] = open(var->file2, O_WRCT, S_RUWUGO);
	i = var->len;
	pid = fork();
	while (!pid)
	{
		fd[1] = fd[2];
		if (1 < i)
			ft_pipe3(&fd[0], &fd[2]);
		else
			fd[0] = open(var->file1, O_RDONLY);
		if (i < 1)
			exit(EXIT_SUCCESS);
		config.execute_var.stdin = fd[0];
		config.execute_var.stdout = fd[1];
		config.execute_var.run_here = (i <= 1);
		eval(var->cmds[i - 1], &config);
		i--;
	}
	waitpid(pid, NULL, 0);
	close(fd[2]);
	free(config.path);
}
