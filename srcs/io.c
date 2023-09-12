/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshimizu <hshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:45:43 by hshimizu          #+#    #+#             */
/*   Updated: 2023/09/12 22:20:33 by hshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

void	setstdio(int input, int output)
{
	if (STDIN_FILENO != input)
	{
		close(STDIN_FILENO);
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (STDOUT_FILENO != output)
	{
		close(STDOUT_FILENO);
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}

void	initstdio(void)
{
	int	input;
	int	output;

	input = open("/dev/stdin", O_RDONLY);
	output = open("/dev/stdout", O_WRONLY);
	setstdio(input, output);
}
