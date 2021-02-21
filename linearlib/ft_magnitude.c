/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_magnitude.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:52:30 by babdelka          #+#    #+#             */
/*   Updated: 2021/01/29 15:29:16 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_alg.h"

float		ft_magnitude(t_vec v)
{
	t_vec	c;

	c.x = v.x * v.x;
	c.y = v.y * v.y;
	c.z = v.z * v.z;
	return (sqrt(c.x + c.y + c.z));
}
