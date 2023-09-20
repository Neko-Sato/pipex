/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 23:22:03 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/wait.h>

typedef struct s_execute
{
	int	stdin;
	int	stdout;
	int	run_here;
}		t_execute;

//	O_WRONLY | O_CREAT | O_TRUNC
# define O_WRCT 0b1001000001
//	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define S_RUWUGO 0b110100100

void	setstdio(int input, int output);
pid_t	execute(char *pathname, char *argv[], char *envp[], t_execute *var);
char	**get_path(char *envp[]);
void	ft_excption(char *s, int abort);
int		ft_pipe3(int *reader, int *writer);

char	**cmdline_split(char *s);

#endif