/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:21:42 by babdelka          #+#    #+#             */
/*   Updated: 2021/01/29 15:43:37 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_atod(const char *str)
{
	int				i;
	double			j;
	int				sign;

	i = 0;
	j = 0;
	sign = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i] == '\t' || str[i] == '\n' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r' ||
			str[i] == ' ')
		i++;
	if (str[i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] >= 48 && str[i] <= 57)
		j = (j * 10) + (str[i++] - '0');
	return (j * sign);
}
