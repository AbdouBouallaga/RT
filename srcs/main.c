/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:42:11 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/24 17:06:39 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	ft_lgt_computing(t_light *lgt, t_vec lgt_dir, t_hit *hit, t_ray *ray)
{
	t_vec	ambient;
	t_vec	color;
	t_vec	phong_dir;

	color = (t_vec){0.0f, 0.0f, 0.0f};
	lgt->ambient_strenght = 0.15f;
	ambient = ft_vectormulti(lgt->color, lgt->ambient_strenght);
	color.x = ambient.x * hit->object->color.x;
	color.y = ambient.y * hit->object->color.y;
	color.z = ambient.z * hit->object->color.z;
	lgt->lambert = fmax(0.0f, ft_dotproduct(lgt_dir, hit->n));
	color = ft_vectoradd(color, ft_vectormulti(hit->object->color,\
	lgt->lambert));
	lgt->reflect = 2.0f * (ft_dotproduct(lgt_dir, hit->n));
	phong_dir = ft_vectorsub(lgt_dir, ft_vectormulti(hit->n, lgt->reflect));
	lgt->phong_term = fmax(ft_dotproduct(phong_dir, ray->direction), 0.0f);
	lgt->phong_term = 0.5f * powf(lgt->phong_term, 40.0f) * 0.5f;
	color = ft_vectoradd(color, ft_vectormulti(lgt->color, lgt->phong_term));
	color.x = color.x * lgt->color.x * (lgt->intensity - 0.75f);
	color.y = color.y * lgt->color.y * (lgt->intensity - 0.75f);
	color.z = color.z * lgt->color.z * (lgt->intensity - 0.75f);
	return (color);
}

void	shade(t_vec *color, t_hit *hit, t_light *light)
{
	t_vec		ambient;

	ambient = ft_vectormulti(light->color, 0.04f);
	color->x = color->x + ambient.x * (hit->object->color.x - 0.04f);
	color->y = color->y + ambient.y * (hit->object->color.y - 0.04f);
	color->z = color->z + ambient.z * (hit->object->color.z - 0.04f);
}

t_vec		ft_shade_object(t_hit *hit, t_light *lights, t_object *lst, t_ray *ray)
{
	t_light		*light;
	t_vec		color;
	t_vec		light_dir;
	t_ray		shadow_ray;
	float		t;
	
	// if (hit->object->type == PLANE){
	// 	gettexture(hit);
	// 	}
	color = ft_vectormulti(hit->object->color, 0.12f);
	shadow_ray.source = hit->p;
	light = lights;
	while (light)
	{
		light_dir = ft_normalize(ft_vectorsub(light->pos, hit->p));
		shadow_ray.direction = light_dir;
		t = ft_magnitude(ft_vectorsub(light->pos, hit->p));
		if (!shadow_cast(lst, &shadow_ray, &t))
			if (hit->object->inside == MIRROR)
				color = ft_vectorsub(color,  color);
			else
				color = ft_vectoradd(color, ft_lgt_computing(light, light_dir,\
			hit, ray));
		else
			shade(&color, hit, light);
		light = light->next;
	}
	return (color);
}

t_vec		ft_reflect(t_hit hit, t_mx *mx, t_ray ray)
{
	t_vec		color;
	int			refle = 0;
	float		var = 0.20f;

	if (hit.object->reflection)
		refle = 25;
	else{
		var = 0.25;
		refle = 15;
		}
	while (refle-- > 0 && var>0)
	{
		ft_compute_normals(&hit, &ray);
		ray.direction = ft_vectoradd(ft_vectormulti(ft_vectormulti(hit.n, ft_dotproduct(ray.direction, hit.n)), -2.0f), hit.n);
		ray.source = hit.p;
		if (raycast(mx->objects, &ray, &hit))
		{
			if (hit.object->inside == MIRROR){
				color = ft_vectormulti(color, 0.0f);
				color = hit.object->color;}
			else
				color = ft_vectormulti(color, 0.95f - var);
				color = ft_vectoradd(color, ft_vectormulti(hit.object->color, var));
		}
		else
			refle = 0;
		var -= 0.03;
	}
	color = shadowinside(mx , color, hit);
	return (color);
}

// t_vec		ft_reflect(t_hit hit, t_object *lst, t_ray ray)
// {
// 	t_vec		color;
// 	int			refle = 0;
// 	float		var = 0.25f;

// 	if (hit.object->reflection)
// 		refle = 50;
// 	while (refle-- > 0 && var>0)
// 	{
// 		ft_compute_normals(&hit, &ray);
// 		ray.direction =  ft_vectoradd(ray.direction ,ft_vectormulti(ray.direction ,(-2.0f * ft_dotproduct(ray.direction, hit.n))));
// 		ray.source = hit.p;
// 		if (raycast(lst, &ray, &hit))
// 		{
// 			color = ft_vectormulti(color, 0.95f - var);
// 			color = ft_vectoradd(color, ft_vectormulti(hit.object->color, var));
// 		}
// 		else
// 			refle = 0;
// 		var -= 0.04;
// 	}
// 	return (color);
// }

t_vec		ft_refract(t_hit hit, t_mx *mx, t_ray ray)
{
	t_vec		color;
	int			refra = 0;
	int			refle = 0;
	float		var = 0.25f;
	float		fCosThetaI = fabsf(90.0f);

	if (hit.object->refraction){
		refra = 2;
		refle = 50;
		}
	float opp;
	if (hit.object->inside == AIR)
		opp = 0.11f;
	if (hit.object->inside == GLASS)
		opp = 0.11f;
	if (hit.object->inside == mNONE || hit.object->inside == MIRROR)
		return(hit.object->color);
	ft_compute_normals(&hit, &ray);
	ray.source = hit.p;
	ray.direction = ft_vectoradd(ray.direction, ft_vectormulti(ray.direction, fCosThetaI));
	ray.direction = ft_vectoradd(hit.n, ft_vectormulti(ray.direction, opp));
	if (raycast(mx->objects, &ray, &hit))
		ft_compute_normals(&hit, &ray);
		ray.source = hit.p;
		ray.direction = ft_vectoradd(ray.direction, ft_vectormulti(ray.direction, fCosThetaI));
		ray.direction = ft_vectoradd(hit.n, ft_vectormulti(ray.direction, opp));
	if (raycast(mx->objects, &ray, &hit))
	{
		color = ft_vectormulti(hit.object->color, 0.95f - var);
		color = ft_vectoradd(color, ft_vectormulti(hit.object->color, var));
		while (refle-- > 0 && var>0)
	{
		ft_compute_normals(&hit, &ray);
		ray.direction = ft_vectoradd(ft_vectormulti(ft_vectormulti(hit.n, ft_dotproduct(ray.direction, hit.n)), -2.0f), hit.n);
		ray.source = hit.p;
		if (raycast(mx->objects, &ray, &hit))
		{
			color = ft_vectormulti(color, 0.95f - 0.15);
			color = ft_vectoradd(color, ft_vectormulti(hit.object->color, 0.15));
		}
		else
			refle = 0;
		var -= 0.04;
	}
	}
	else
		refra = 0;
	color = shadowinside(mx, color, hit);
	return (color);
}

// t_vec		ft_refract(t_hit hit, t_mx *mx, t_ray ray)
// {
// 	t_vec		color;
// 	int			refra = 0;
// 	// int			refle = 0;
// 	float		var = 0.25f;
// 	float		fCosThetaI = fabsf(60.0f);

// 	if (hit.object->refraction){
// 		refra = 2;
// 		// refle = 1;
// 		}
// 	float eta;
// 	if (hit.object->inside == AIR)
// 		eta = 1.0f;
// 	if (hit.object->inside == GLASS)
// 		eta = 0.50f;
// 	if (hit.object->inside == mNONE)
// 		return(hit.object->color);
// 	ft_compute_normals(&hit, &ray);
// 	float ndot = ft_dotproduct(hit.n, hit.p);
// 	float k = 1.0f - eta * eta * (1.0f - ndot * ndot);
// 		ray.direction = ft_vectorsub(ft_vectormulti(hit.p, eta), ft_vectormulti(hit.n, (eta * ndot + sqrtf(k))));
// 	ray.source = hit.p;
// 	// if (raycast(mx->objects, &ray, &hit))
// 	// 	ft_compute_normals(&hit, &ray);
// 	// 	ndot = ft_dotproduct(hit.n, hit.p);
// 	// 	k = 1.0f - eta * eta * (1.0f - ndot * ndot);
// 	// 	ray.source = hit.p;
// 	// 	ray.direction = ft_vectorsub(ft_vectormulti(hit.p, eta), ft_vectormulti(hit.n, (eta * ndot + sqrtf(k))));
// 	if (raycast(mx->objects, &ray, &hit))
// 	{
// 		color = ft_vectormulti(color, 0.95f - var);
// 		color = ft_vectoradd(color, ft_vectormulti(hit.object->color, var));
// 	}
// 	return (color);
// }

void	update(t_mx *mx)
{
	t_ray	ray;
	t_hit	hit;
	int		y;
	int		x;
	t_vec	color;
	float	var;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = camera_ray(&mx->cam, x, y);
			hit.t = INFINITY;
			if (raycast(mx->objects, &ray, &hit))
			{
				color = ft_shade_object(&hit, mx->lights, mx->objects, &ray);
				if (hit.object->inside == MIRROR)
					var = 4;
				else
					var = 0.32;
				color = ft_vectoradd(color, ft_vectormulti(ft_reflect(hit, mx, ray), var));
				color = ft_vectoradd(color, ft_vectormulti(ft_refract(hit, mx, ray), 0.32));
				mx->rt[(WIN_H - 1 - y) * WIN_W + x] = rgb_to_int(clamp_vect(color));
			}
			x+=1;
		}
		y+=1;
	}
}

int		main(int ac, char **av)
{
	t_mx	v;
	t_object	*p;

	if (ac == 2)
	{
		if (av[1])
		{
			ft_bzero(&v, sizeof(t_mx));
			if (!ft_open(av[1], &v))
			{
				ft_putstr("error! please try a valid configuration file.\n");
				exit(0);
			}
			else{
				p = v.objects;
				while(p)
				{
					printf("------ %d\n", p->reflection);
					if (p->type == SPHERE)
						printf("------ %d\n", p->reflection);
					p = p->next;				
				}
				run(&v);}
		}
	}
	else
		ft_usage();
	return (0);
}
