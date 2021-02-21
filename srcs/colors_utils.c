/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:21:33 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:05 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		converting_base(char *str, t_base *v)
{
	if (str[v->i + 1] >= 48 && str[v->i + 1] <= 57)
		v->somme = v->somme + (str[v->i + 1] - 48) * pow(16, v->n);
	else if (str[v->i + 1] >= 97 && str[v->i + 1] <= 102)
		v->somme = v->somme + (str[v->i + 1] - 87) * pow(16, v->n);
	else if (str[v->i + 1] >= 65 && str[v->i + 1] <= 70)
		v->somme = v->somme + (str[v->i + 1] - 55) * pow(16, v->n);
}

int				ft_special_atoi_base(char *str)
{
	t_base		v;

	v.i = 0;
	v.n = 0;
	v.somme = 0;
	v.p = 0;
	v.rt = 0;
	while (str[v.i] != 'x' && str[v.i])
		v.i++;
	if (str[v.i] != '\0')
		v.rt = ft_strlen(str);
	while (str[v.rt - 1] != 'x' && str[v.rt - 1])
	{
		v.p++;
		v.rt--;
	}
	v.n = v.p - 1;
	while (str[v.i + 1] != '\0' && v.n >= 0)
	{
		converting_base(str, &v);
		v.i++;
		v.n--;
	}
	return (v.somme);
}

t_vec			vect_from_hexa(int rgb)
{
	t_vec		v;
	int			red;
	int			green;
	int			blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = rgb & 0xFF;
	v.x = (float)red / 255.0f;
	v.y = (float)green / 255.0f;
	v.z = (float)blue / 255.0f;
	return (v);
}

int				ft_check_hex_color(char *str)
{
	int			i;

	if (ft_strlen(str) != 8)
		return (0);
	i = 1;
	if (str && str[0] == '0')
	{
		if (str && str[1] == 'x')
			while (str[++i])
			{
				if ((str[i] < 65 || str[i] > 70) && \
				(str[i] < 97 || str[i] > 102)
						&& (str[i] < 48 || str[i] > 57))
					return (0);
			}
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int				rgb_to_int(t_vec v)
{
	int			red;
	int			green;
	int			blue;
	int			rgb;

	red = (int)v.x;
	green = (int)v.y;
	blue = (int)v.z;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}
