/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:28:35 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:14 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_min_ray(float t1, float t2, float *t)
{
	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	else
		return (0);
}

int			sphere_intersect(t_object *sphere, t_ray *ray, float *tmin)
{
	t_vec x;

	x = ft_vectorsub(ray->source, sphere->pos);
	sphere->sp.a = ft_dotproduct(ray->direction, ray->direction);
	sphere->sp.b = 2.0 * ft_dotproduct(ray->direction, x);
	sphere->sp.c = ft_dotproduct(x, x) - sphere->radius * sphere->radius;
	sphere->sp.delta = (sphere->sp.b * sphere->sp.b) -\
	(4.0 * sphere->sp.a * sphere->sp.c);
	if (sphere->sp.delta < 0)
		return (0);
	sphere->sp.delta = sqrtf(sphere->sp.delta);
	sphere->sp.t1 = (-sphere->sp.b + sphere->sp.delta) / (2 * sphere->sp.a);
	sphere->sp.t2 = (-sphere->sp.b - sphere->sp.delta) / (2 * sphere->sp.a);
	return (ft_min_ray(sphere->sp.t1, sphere->sp.t2, tmin));
}

int			plane_intersect(t_object *plane, t_ray *ray, float *tmin)
{
	t_vec	x;
	float	a;
	float	b;
	float	t;

	x = ft_vectorsub(ray->source, plane->pos);
	a = -1.0 * ft_dotproduct(x, plane->normal);
	b = ft_dotproduct(ray->direction, plane->normal);
	if (fabs(b) <= 1e-6)
		return (0);
	t = a / b;
	if (t > 1e-2 && t < *tmin)
	{
		*tmin = t;
		return (1);
	}
	return (0);
}

int			cylinder_intersect(t_object *cylinder, t_ray *ray, float *tmin)
{
	t_vec	x;

	x = ft_vectorsub(ray->source, cylinder->pos);
	cylinder->cy.a = ft_dotproduct(ray->direction, ray->direction) -\
	powf(ft_dotproduct(ray->direction, cylinder->axis), 2.0);
	cylinder->cy.b = 2.0 * (ft_dotproduct(ray->direction, x) -\
	(ft_dotproduct(ray->direction, cylinder->axis) *\
	ft_dotproduct(x, cylinder->axis)));
	cylinder->cy.c = ft_dotproduct(x, x) -\
	powf(ft_dotproduct(x, cylinder->axis), 2.0) -\
	(cylinder->radius * cylinder->radius);
	cylinder->cy.delta = (cylinder->cy.b * cylinder->cy.b) -\
	(4.0 * cylinder->cy.a * cylinder->cy.c);
	if (cylinder->cy.delta < 0)
		return (0);
	cylinder->cy.delta = sqrtf(cylinder->cy.delta);
	cylinder->cy.t1 = (-cylinder->cy.b + cylinder->cy.delta) /\
	(2 * cylinder->cy.a);
	cylinder->cy.t2 = (-cylinder->cy.b - cylinder->cy.delta) /\
	(2 * cylinder->cy.a);
	return (ft_min_ray(cylinder->cy.t1, cylinder->cy.t2, tmin));
}

int			cone_intersect(t_object *cone, t_ray *ray, float *tmin)
{
	t_vec	x;

	x = ft_vectorsub(ray->source, cone->pos);
	cone->cn.k = tanf(deg_to_rad(cone->angle) / 2.0);
	cone->cn.a = ft_dotproduct(ray->direction, ray->direction) -\
	(1.0 + (cone->cn.k * cone->cn.k)) *\
	powf(ft_dotproduct(ray->direction, cone->axis), 2.0);
	cone->cn.b = 2.0 * (ft_dotproduct(ray->direction, x) -\
	((1.0 + (cone->cn.k * cone->cn.k)) *\
	ft_dotproduct(ray->direction, cone->axis) * ft_dotproduct(x, cone->axis)));
	cone->cn.c = ft_dotproduct(x, x) -\
	(1.0 + (cone->cn.k * cone->cn.k)) * powf(ft_dotproduct(x, cone->axis), 2.0);
	cone->cn.delta = (cone->cn.b * cone->cn.b) -\
	(4.0 * cone->cn.a * cone->cn.c);
	if (cone->cn.delta < 0)
		return (0);
	cone->cn.delta = sqrtf(cone->cn.delta);
	cone->cn.t1 = (-cone->cn.b + cone->cn.delta) / (2 * cone->cn.a);
	cone->cn.t2 = (-cone->cn.b - cone->cn.delta) / (2 * cone->cn.a);
	return (ft_min_ray(cone->cn.t1, cone->cn.t2, tmin));
}
