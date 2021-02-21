/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectormulti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:53:24 by babdelka          #+#    #+#             */
/*   Updated: 2021/01/29 15:29:24 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_alg.h"

t_vec		ft_vectormulti(t_vec c, float scalar)
{
	c.x *= scalar;
	c.y *= scalar;
	c.z *= scalar;
	return (c);
}
