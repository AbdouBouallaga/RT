/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:29:53 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:10 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				ft_check_positive_floats(char *str)
{
	double		to_check;

	if (str && !ft_str_is_numeric(str))
		return (0);
	to_check = ft_atof(str);
	if (to_check <= 0.0)
		return (0);
	return (1);
}

int				ft_check_floats(char *str)
{
	if (str && !ft_str_is_numeric(str))
		return (0);
	return (1);
}

int				ft_check_camera_fov(char *str)
{
	double		fov;

	fov = 0.0;
	if (str && ft_check_floats(str))
	{
		fov = ft_atof(str);
		if (fov <= 120.0 && fov >= 30.0)
			return (1);
	}
	return (0);
}
