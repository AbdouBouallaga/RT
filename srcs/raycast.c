/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:14:20 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/27 18:27:47 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray			raycastloop(t_object *p, t_hit *hit, t_ray *raw, float t)
{
	t_ray		save;
	t_ray		ray;

	while (p)
	{
		ray = ft_transform_ray(p, raw, 1);
		if (p->type == SPHERE){
			sphere_intersect(p, &ray, &t);}
		else if (p->type == PLANE){
			plane_intersect(p, &ray, &t);
			}
		else if (p->type == CYLINDER)
			cylinder_intersect(p, &ray, &t);
		else if (p->type == CONE)
			cone_intersect(p, &ray, &t);
		if (hit->t > t)
		{
			hit->t = t;
			hit->object = p;
			save = ray;
		}
		p = p->next;
	}
	return (save);
}

int				raycast(t_object *lst, t_ray *raw, t_hit *hit)
{
	t_object	*p;
	t_hit		*last;
	float		t;
	t_ray		save;

	t = INFINITY;
	hit->object = NULL;
	hit->t = INFINITY;
	last = hit;
	p = lst;
	save = raycastloop(p, hit, raw, t);
	if (hit->object == NULL)
		return (0);
	hit->p = ft_vectoradd(save.source, ft_vectormulti(save.direction, hit->t));
	ft_compute_normals(hit, raw);
	hit->p = ft_translate_object(hit->p, hit->object->trans, 0);
	hit->p = ft_rotate_object(hit->p, hit->object->rot, 0);
	hit->n = ft_rotate_object(hit->n, hit->object->rot, 0);
	hit->n = ft_normalize(hit->n);
	return (1);
}

int				shadow_cast(t_object *lst, t_ray *ray, float *tmin)
{
	t_object	*p;
	float		t;
	t_ray		ra;

	t = INFINITY;
	p = lst;
	while (p)
	{
		ra = ft_transform_ray(p, ray, 1);
		if (p->type == SPHERE)
			sphere_intersect(p, &ra, &t);
		else if (p->type == PLANE)
			plane_intersect(p, &ra, &t);
		else if (p->type == CYLINDER)
			cylinder_intersect(p, &ra, &t);
		else if (p->type == CONE)
			cone_intersect(p, &ra, &t);
		if (t < *tmin)
			return (1);
		p = p->next;
	}
	return (0);
}

t_vec	shadowinside(t_mx *mx, t_vec color, t_hit hit)
{
	t_vec		light_dir;
	t_ray		shadow_ray;
	t_light		*light;
	float		t;

	shadow_ray.source = hit.p;
	light = mx->lights;
	while (light)
	{
		light_dir = ft_normalize(ft_vectorsub(light->pos, hit.p));
		shadow_ray.direction = light_dir;
		t = ft_magnitude(ft_vectorsub(light->pos, hit.p));
		if (!shadow_cast(mx->objects, &shadow_ray, &t)){
			color = color;
		}
		else
			color = ft_vectormulti(color, 0.85f);
		light = light->next;
	}
	return(color);
}
