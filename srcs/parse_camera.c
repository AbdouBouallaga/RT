/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:10:58 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:32 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				ft_parse_camera(t_mx *v, char **token)
{
	t_vec		pos;
	t_vec		at;

	v->len = ft_strsplit_len(token);
	pos = (t_vec){0, 0, 0};
	at = (t_vec){0, 0, 0};
	v->vfov = 0.0f;
	if (v->len == 4 && token)
		if (ft_check_vectors(token[1]) && ft_check_vectors(token[2])
				&& ft_check_camera_fov(token[3]))
		{
			if (token[1])
				pos = string_to_vect(token[1]);
			if (token[2])
				at = string_to_vect(token[2]);
			if (token[3])
				v->vfov = ft_atof(token[3]);
			v->cam = ft_camera_create(pos, at,\
			(t_vec){0, 1, 0}, v->vfov);
		}
		else
			return (0);
	else
		return (0);
	return (1);
}
