/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:46:56 by hshimizu          #+#    #+#             */
/*   Updated: 2023/10/02 05:06:48 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>

typedef struct s_pipex
{
	char	**cmds;
	size_t	len;
	char	*in;
	char	*out;
	int		here_doc;
	int		append;
}			t_pipex;

int		pipex(t_pipex *var, char *envp[]);

#endif