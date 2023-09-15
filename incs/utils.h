/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/16 02:07:11 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/wait.h>

//	O_WRONLY | O_CREAT | O_TRUNC
# define O_WRCT 0b1001000001
//	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define S_RUWUGO 0b110100100

void	setstdio(int input, int output);
pid_t	execute(char *pathname, char *argv[], char *envp[], int fd[2]);
char	**get_path(char *envp[]);
void	ft_pipe3(int *reader, int *writer);

char	**cmdline_split(char *s);

#endif