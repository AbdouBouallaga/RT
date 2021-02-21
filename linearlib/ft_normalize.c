/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:53:01 by babdelka          #+#    #+#             */
/*   Updated: 2021/01/29 15:29:19 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_alg.h"

t_vec		ft_normalize(t_vec v)
{
	float	magnitude;

	magnitude = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	v.x /= magnitude;
	v.y /= magnitude;
	v.z /= magnitude;
	return (v);
}
