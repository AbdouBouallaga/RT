/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_normals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:48:06 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:07 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_compute_normals(t_hit *hit, t_ray *ray)
{
	t_vec	x;
	float	m;
	float	k;

	if (hit->object->type == SPHERE)
		hit->n = ft_normalize(ft_vectorsub(hit->p, hit->object->pos));
	else if (hit->object->type == PLANE)
		hit->n = hit->object->normal;
	else if (hit->object->type == CYLINDER)
	{
		x = ft_vectorsub(ray->source, hit->object->pos);
		m = ft_dotproduct(ray->direction, ft_vectormulti(hit->object->axis,\
		hit->t)) + ft_dotproduct(x, hit->object->axis);
		hit->n = ft_normalize(ft_vectorsub(ft_vectorsub(hit->p,\
		hit->object->pos), ft_vectormulti(hit->object->axis, m)));
	}
	else if (hit->object->type == CONE)
	{
		x = ft_vectorsub(ray->source, hit->object->pos);
		m = ft_dotproduct(ray->direction, ft_vectormulti(hit->object->axis,\
		hit->t)) + ft_dotproduct(x, hit->object->axis);
		k = tanf(deg_to_rad(hit->object->angle) / 2.0);
		hit->n = ft_normalize(ft_vectorsub(ft_vectorsub(hit->p, hit->object->\
		pos), ft_vectormulti(hit->object->axis, ((1.0 + (k * k)) * m))));
	}
}
