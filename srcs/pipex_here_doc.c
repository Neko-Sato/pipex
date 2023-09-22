/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:56:23 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/22 09:01:20 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

int			here_doc(char *eof, int fd);

void	pipex_here_doc(t_pipex_here_doc *var, char *envp[])
{
	t_pipex	pipex_var;
	int		result;

	tempfilename = nodupfilename("./.here_doc__");
	if (tempfilename)
	{
		temp = open(tempfilename, O_OVERWRITE, S_IWUSR | S_IRUSR);
		if (temp)
		{
			result = here_doc(eof, temp);
			close(temp);
			if (!result)
			{
				pipex_var->cmds = var->cmds;
				pipex_var->len = var->len;
				pipex_var->file1 = tempfilename;
				pipex_var->file2 = var->file;
				pipex_var->append = 1;
				pipex(&pipex_var, envp);
			}
		}
		unlink(tempfilename);
	}
	free(tempfilename)
}

int	here_doc(char *delimited, int fd)
{
	t_bufferio	*stdin;
	char		*temp;
	size_t		delimited_len;

	delimited_len = ft_strlen(delimited);
	stdin = ft_bufferionew(STDIN_FILENO, 0);
	if (!stdin)
		return (-1);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		temp = ft_readline(stdin);
		if (!temp)
		{
			here_doc_put_error(delimited_len);
			ft_bufferiodel(stdin, 0);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(temp, eof, eof_len + 1) == '\n')
		{
			free(temp);
			ft_bufferiodel(stdin, 0);
			return (0);
		}
		ft_putstr_fd(temp, fd);
		free(temp);
	}
}

static void	here_doc_put_error(size_t line, char *eof)
{
	if (line)
	{
		ft_putstr_fd("line ", STDERR_FILENO);
		ft_putnbr_fd(line, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd("warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document at line 0 delimited by end-of-file ",
					STDERR_FILENO);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}