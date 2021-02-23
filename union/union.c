/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezzull <mpezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:59:19 by mpezzull          #+#    #+#             */
/*   Updated: 2021/02/19 16:09:15 by mpezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

int 	ft_contains_char(char c, char *str)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);	
}

int main(int argc, char **argv)
{
	char 	already_print[256] = {0};
	int 	i;

	i = 0;
	if (argc == 3)
	{
		while (*argv[1])
		{
			if (!ft_contains_char(*argv[1], already_print))
			{
				ft_putchar(*argv[1]);
				already_print[i++] = *argv[1];		
			}
			argv[1]++;
		}
		while (*argv[2])
		{
			if (!ft_contains_char(*argv[2], already_print))
			{
				ft_putchar(*argv[2]);
				already_print[i++] = *argv[2];		
			}
			argv[2]++;
		}
	}
	ft_putchar('\n');
}