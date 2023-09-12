/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:33:06 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/10 14:24:44 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

char	*executable(char *cmd, char *path[])
{
	int		i;
	char	*temp;

	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	i = 0;
	while (path && path[i])
	{
		temp = ft_joinpath(path[i++], cmd);
		if (!temp)
			return (NULL);
		if (!access(temp, X_OK))
			return (temp);
		free(temp);
	}
	return (NULL);
}

char	**get_path(char *envp[])
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(&envp[i][5], ':'));
}
