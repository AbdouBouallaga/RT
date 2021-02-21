/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:08:53 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:01 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam		ft_camera_create(t_vec pos, t_vec at, t_vec vup, float vfov)
{
	t_cam	cam;
	float	theta;
	float	half_height;
	float	half_width;

	pos.z += 0.01;
	cam.pos = pos;
	cam.fov = vfov;
	theta = vfov * M_PI / 180.0;
	half_height = tanf(theta / 2.0);
	half_width = ((float)WIN_W / (float)WIN_H) * half_height;
	cam.forward = ft_normalize(ft_vectorsub(pos, at));
	cam.u = ft_normalize(ft_crossproduct(vup, cam.forward));
	cam.v = ft_crossproduct(cam.forward, cam.u);
	cam.lower_left_corner = ft_vectoradd(ft_vectormulti(cam.u, half_width),\
	ft_vectormulti(cam.v, half_height));
	cam.lower_left_corner = ft_vectoradd(cam.lower_left_corner, cam.forward);
	cam.lower_left_corner = ft_vectorsub(cam.pos, cam.lower_left_corner);
	cam.horizontal = ft_vectormulti(cam.u, 2.0 * half_width);
	cam.vertical = ft_vectormulti(cam.v, 2.0 * half_height);
	return (cam);
}

t_ray		camera_ray(t_cam *cam, int x, int y)
{
	t_ray	ray;
	t_vec	tmp;
	float	s;
	float	t;

	s = (float)x / (WIN_W);
	t = (float)y / (WIN_H);
	tmp = ft_vectoradd(ft_vectormulti(cam->horizontal, s),\
	ft_vectormulti(cam->vertical, t));
	tmp = ft_vectoradd(cam->lower_left_corner, tmp);
	ray.source = cam->pos;
	ray.direction = ft_normalize(ft_vectorsub(tmp, cam->pos));
	return (ray);
}
