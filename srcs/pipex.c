// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipex.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/08/22 18:18:02 by hshimizu          #+#    #+#             */
// /*   Updated: 2023/09/16 00:51:51 by hshimizu         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"
// #include "utils.h"
// #include <fcntl.h>
// #include <stdlib.h>
// #include <sys/stat.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int	pipex(t_pipex *vars, char *envp[])
// {
// 	size_t	i;
// 	int		fd[2];
// 	int		temp;
// 	pid_t	pid;

// 	i = 0;
// 	fd[0] = open(vars->file1, O_RDONLY);
// 	while (++i)
// 	{
// 		if (i < vars->len)
// 			ft_pipe3(&temp, &fd[1]);
// 		else
// 			fd[1] = open(vars->file2, O_WRCT, S_RUWUGO);
// 		config->stdin = fd[0];
// 		config->stdout = writer;
// 		pid = execute(vars->cmds[i - 1], config);
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (i >= vars->len)
// 			break ;
// 		fd[0] = temp;
// 	}
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }
