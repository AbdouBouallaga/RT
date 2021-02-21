/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:54:28 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:18:09 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void materialinside(char *token, t_object *object)
{
	if (ft_strequ(token, "air"))
		object->inside = AIR;
	else if (ft_strequ(token, "glass"))
		object->inside = GLASS;
	else if (ft_strequ(token, "none"))
		object->inside = mNONE;
	else if (ft_strequ(token, "mirror")){
		object->inside = MIRROR;
		object->color = vector3(0,0,0);}

}

void	tokenfill_sphere(char **token, t_object *object)
{
	if (token[1])
		object->pos = string_to_vect(token[1]);
	if (token[2])
		object->radius = ft_atof(token[2]);
	if (token[3])
		object->rot = string_to_vect(token[3]);
	if (token[4])
		object->trans = string_to_vect(token[4]);
	if (token[5])
		object->color = vect_from_hexa(ft_special_atoi_base(token[5]));
	if (token[6])
		object->reflection = atoi(token[6]);
	if (token[7])
		object->refraction = atoi(token[7]);
	if (token[8])
		materialinside(token[8], object);
}

void	tokenfill_plane(char **token, t_object *object)
{
	t_texture t;
	if (token[1])
		object->pos = string_to_vect(token[1]);
	if (token[2])
		object->normal = string_to_vect(token[2]);
	if (token[3])
		object->rot = string_to_vect(token[3]);
	if (token[4])
		object->trans = string_to_vect(token[4]);
	if (token[5])
		object->color = vect_from_hexa(ft_special_atoi_base(token[5]));
	if (token[6])
		object->reflection = atoi(token[6]);
	if (token[7])
		object->refraction = atoi(token[7]);
	if (token[8])
		materialinside(token[8], object);
}

void	tokenfill_cone(char **token, t_object *object)
{
	if (token[1])
		object->pos = string_to_vect(token[1]);
	if (token[2])
		object->angle = ft_atof(token[2]);
	if (token[3])
		object->axis = string_to_vect(token[3]);
	if (token[4])
		object->rot = string_to_vect(token[4]);
	if (token[5])
		object->trans = string_to_vect(token[5]);
	if (token[6])
		object->color = vect_from_hexa(ft_special_atoi_base(token[6]));
	if (token[7])
		object->reflection = atoi(token[7]);
	if (token[8])
		object->refraction = atoi(token[8]);
	if (token[9])
		materialinside(token[9],object);
}

void	tokenfill_cylinder(char **token, t_object *object)
{
	if (token[1])
		object->pos = string_to_vect(token[1]);
	if (token[2])
		object->radius = ft_atof(token[2]);
	if (token[3])
		object->axis = string_to_vect(token[3]);
	if (token[4])
		object->rot = string_to_vect(token[4]);
	if (token[5])
		object->trans = string_to_vect(token[5]);
	if (token[6])
		object->color = vect_from_hexa(ft_special_atoi_base(token[6]));
	if (token[7])
		object->reflection = atoi(token[7]);
	if (token[8])
		object->refraction = atoi(token[8]);
	if (token[9])
		materialinside(token[9],object);
}
