/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:13:28 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:18:17 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		ft_rotate_object(t_vec to_rot, t_vec rot, int invert)
{
	if (invert)
	{
		to_rot = z_rotation(to_rot, -rot.z);
		to_rot = y_rotation(to_rot, -rot.y);
		to_rot = x_rotation(to_rot, -rot.x);
	}
	else
	{
		to_rot = x_rotation(to_rot, rot.x);
		to_rot = y_rotation(to_rot, rot.y);
		to_rot = z_rotation(to_rot, rot.z);
	}
	return (to_rot);
}

t_vec		ft_translate_object(t_vec to_trans, t_vec trans, int invert)
{
	t_vec	result;

	if (invert)
	{
		result.x = to_trans.x - trans.x;
		result.y = to_trans.y - trans.y;
		result.z = to_trans.z - trans.z;
	}
	else
	{
		result.x = to_trans.x + trans.x;
		result.y = to_trans.y + trans.y;
		result.z = to_trans.z + trans.z;
	}
	return (result);
}

t_ray		ft_transform_ray(t_object *obj, t_ray *raw, int invert)
{
	t_ray	result;

	result = *raw;
	result.source = ft_rotate_object(raw->source, obj->rot, invert);
	result.source = ft_translate_object(result.source, obj->trans, invert);
	result.direction = ft_rotate_object(raw->direction, obj->rot, invert);
	return (result);
}

float		clamp(float value, float min, float max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}
	return (value);
}

t_vec		clamp_vect(t_vec v)
{
	v.x = clamp(v.x * 255, 0.0f, 255.0f);
	v.y = clamp(v.y * 255, 0.0f, 255.0f);
	v.z = clamp(v.z * 255, 0.0f, 255.0f);
	return (v);
}

t_vec		vector3(float x, float y, float z)
{
	t_vec v;
	v.x = x;
	v.y = y;
	v.z = z;
	return(v);
}

int			vec3equ(t_vec v1, t_vec v2)
{
	if (v1.x == v2.x)
		if (v1.y == v2.y)
			if (v1.z == v2.z)
				return(1);
	return(0);
}
