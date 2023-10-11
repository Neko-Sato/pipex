/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:45:33 by hshimizu          #+#    #+#             */
/*   Updated: 2023/10/11 21:06:31 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	core(char ***lst_ptr, t_strgen *strgen, char *s);
static int	loop(t_strgen *strgen, char **s);
static int	singlequote_mode(t_strgen *strgen, char **s);
static int	doublequote_mode(t_strgen *strgen, char **s);

char	**cmdline_split(char *s)
{
	char		**ret;
	char		**lst;
	t_strgen	*strgen;

	strgen = ft_strgennew();
	if (!strgen)
		return (NULL);
	lst = NULL;
	if (core(&lst, strgen, s))
		ret = NULL;
	else
		ret = ft_xlst2array(lst, sizeof(char *), NULL);
	ft_xlstclear(&lst, sizeof(char *));
	ft_strgendel(strgen);
	return (ret);
}

static int	core(char ***lst_ptr, t_strgen *strgen, char *s)
{
	char	*temp;

	while (1)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		if (loop(strgen, &s))
			return (-2);
		temp = ft_strgencomp(strgen);
		if (!temp || ft_xlstappend(lst_ptr, sizeof(char *), &temp))
			return (-1);
	}
	temp = NULL;
	return (ft_xlstappend(lst_ptr, sizeof(char *), &temp));
}

static int	loop(t_strgen *strgen, char **s)
{
	while (**s && !ft_isspace(**s))
	{
		if (**s == '\'')
		{
			if (singlequote_mode(strgen, s))
				return (-1);
		}
		else if (**s == '"')
		{
			if (doublequote_mode(strgen, s))
				return (-1);
		}
		else
			ft_strgenchr(strgen, *(*s)++);
	}
	return (0);
}

static int	singlequote_mode(t_strgen *strgen, char **s)
{
	(*s)++;
	while (*(*s) && *(*s) != '\'')
		ft_strgenchr(strgen, *(*s)++);
	if (!*(*s))
		return (-1);
	(*s)++;
	return (0);
}

static int	doublequote_mode(t_strgen *strgen, char **s)
{
	(*s)++;
	while (*(*s) && *(*s) != '"')
	{
		if (*(*s) == '\\' && ft_strchr("\\\"", *(*s + 1)))
			(*s)++;
		ft_strgenchr(strgen, *(*s)++);
	}
	if (!*(*s))
		return (-1);
	(*s)++;
	return (0);
}
