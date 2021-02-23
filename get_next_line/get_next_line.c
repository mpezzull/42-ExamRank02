/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezzull <mpezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:28:46 by mpezzull          #+#    #+#             */
/*   Updated: 2021/02/23 18:29:47 by mpezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int     get_next_line(char **line)
{
	char 	buffer;
	int 	ret;
	char 	*str, *temp;
	int 	len = 0;

	if (!line || !(temp = (char *)malloc(sizeof(char) * 4096)))
		return (-1);
	temp[0] = '\0';
	while ((ret = read(0, &buffer, 1)) > 0)
	{
		if (buffer == '\n' || buffer == '\0')
			break ;
		temp[len] = buffer;
		temp[len++ + 1] = '\0';
	}
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (-1);
    str[len] = '\0';
    while (len-- >= 0)
        str[len] = temp[len];
    free(temp);
    *line = str;
	return ret;
}