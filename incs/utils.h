/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/23 08:15:56 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/wait.h>

//	O_WRONLY | O_CREAT | O_TRUNC
# define O_OVERWRITE 0b01001000001
//	O_WRONLY | O_APPEND
# define O_APPENDWRITE 0b10000000001
//	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define S_RUWUGO 0b00110100100

//	utils.c
typedef struct s_execute
{
	int			stdin;
	int			stdout;
	int			run_here;
}				t_execute;

void			setstdio(int input, int output);
pid_t			execute(char *pathname, char *argv[], char *envp[],
					t_execute *var);
char			**get_path(char *envp[]);
int				newpipe(int *reader, int *writer);

char			**cmdline_split(char *s);
char			*here_doc(char *delimited);

//	eval.c
typedef struct s_eval
{
	char		**envp;
	char		**path;
	t_execute	execute_var;
}				t_eval;

int				executable(char *cmd, char *path[], char **filename);
pid_t			eval(char *cmd, t_eval *config);

#endif