/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:46:56 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 20:26:58 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "utils.h"
# include <sys/wait.h>

typedef struct s_eval
{
	char		**envp;
	char		**path;
	t_execute	execute_var;
}				t_eval;

char			*executable(char *cmd, char *path[]);
pid_t			eval(char *cmd, t_eval *config);

#endif