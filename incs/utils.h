/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/16 00:35:47 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/wait.h>

# define O_WRCT (O_WRONLY | O_CREAT | O_TRUNC)
# define S_RUWUGO (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void	setstdio(int input, int output);
pid_t	execute(char *pathname, char *argv[], char *envp[], int fd[2]);
char	**get_path(char *envp[]);
void	ft_pipe3(int *reader, int *writer);

char	**cmdline_split(char *s);

#endif