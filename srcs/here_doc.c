/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:56:23 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/24 15:02:04 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*loop(t_bufferio *stdin, char *delimited);
static char	*here_doc_read(t_bufferio *stdin, char *delimited, size_t *line);
static int	chaek_delimited(t_strgen *strgen, char *str, char *delimited);
static void	put_error(size_t line, char *delimited);

char	*here_doc(char *delimited)
{
	char		*ret;
	t_bufferio	*stdin;

	stdin = ft_bufferionew(STDIN_FILENO, 0);
	if (!stdin)
	{
		perror("stdin");
		return (NULL);
	}
	ret = loop(stdin, delimited);
	if (!ret && stdin->strgen->error)
		perror("here_doc");
	ft_bufferiodel(stdin, 0);
	return (ret);
}

static char	*loop(t_bufferio *stdin, char *delimited)
{
	t_strgen	*strgen;
	char		*temp;
	size_t		line;

	strgen = ft_strgennew();
	if (!strgen)
		return (NULL);
	line = 0;
	while (1)
	{
		temp = here_doc_read(stdin, delimited, &line);
		if (!temp)
			break ;
		if (chaek_delimited(strgen, temp, delimited))
		{
			temp = ft_strgencomp(strgen);
			break ;
		}
	}
	ft_strgendel(strgen);
	return (temp);
}

static char	*here_doc_read(t_bufferio *stdin, char *delimited, size_t *line)
{
	char	*temp;

	ft_putstr_fd("> ", STDOUT_FILENO);
	temp = ft_readline(stdin);
	if (!temp)
		put_error(*line, delimited);
	(*line)++;
	return (temp);
}

static int	chaek_delimited(t_strgen *strgen, char *str, char *delimited)
{
	if (ft_strcmp(str, delimited) == '\n')
	{
		free(str);
		return (1);
	}
	else
	{
		ft_strgenstr(strgen, str);
		free(str);
		return (0);
	}
}

static void	put_error(size_t line, char *delimited)
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
	ft_putstr_fd(delimited, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}
