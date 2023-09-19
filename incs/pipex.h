/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:46:56 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 03:03:55 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "utils.h"
# include <stddef.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char		**cmds;
	size_t		len;
	char		*file1;
	char		*file2;
}				t_pipex;

typedef struct s_eval
{
	char		**envp;
	char		**path;
	t_execute	execute_var;
}				t_eval;

void			pipex(t_pipex *vars, char *envp[]);
char			*executable(char *cmd, char *path[]);
pid_t			eval(char *cmd, t_eval *config);

#endif