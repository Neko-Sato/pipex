/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:46:56 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/20 15:13:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>

typedef struct s_pipex
{
	char	**cmds;
	size_t	len;
	char	*file1;
	char	*file2;
}			t_pipex;

void		pipex(t_pipex *vars, char *envp[]);

#endif