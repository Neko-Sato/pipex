/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 00:56:01 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/29 16:46:59 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <libft.h>

static int	setvar(t_pipex *var, int len, char *args[], int here_doc);

int	main(int argc, char *argv[], char *envp[])
{
	int		here_doc;
	t_pipex	var;

	here_doc = ((1 < argc) && !ft_strcmp(argv[1], "here_doc"));
	if (setvar(&var, argc - 1 - here_doc, &argv[1 + here_doc], here_doc))
	{
		ft_putendl_fd("error", 2);
		return (-1);
	}
	pipex(&var, envp);
	return (0);
}

static int	setvar(t_pipex *var, int len, char *args[], int here_doc)
{
	if (len < 4)
		return (-1);
	var->in = args[0];
	var->cmds = &args[1];
	var->len = len - 2;
	var->out = args[len - 1];
	var->here_doc = here_doc;
	var->append = here_doc;
	return (0);
}
