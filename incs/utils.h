/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/10/02 05:47:50 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/wait.h>
# include <fcntl.h>

//	O_WRONLY | O_CREAT | O_TRUNC  
# define O_OVERWRITE 577
//	O_WRONLY | O_CREAT | O_APPEND
# define O_APPENDWRITE 1089
//	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define S_RUWUGO 420

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
int				here_doc_fd(char *delimited);

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