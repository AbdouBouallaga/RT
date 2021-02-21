/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:12:21 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:39 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				ft_check_semicolon(char *line)
{
	int			i;

	if (line[0] == ';')
		return (0);
	i = -1;
	while (line[++i])
	{
		if (line[i] && line[i] == ';')
		{
			if (!line[i + 1] || line[i + 1] != '\n')
				return (0);
		}
	}
	return (1);
}

int				ft_check_whitespaces(char *line)
{
	int			i;

	if (line[0] == ' ' || line[0] == '\t')
		return (0);
	i = -1;
	while (line[++i])
	{
		if (line[i] && line[i] == ' ')
		{
			if (!line[i + 1] || line[i + 1] == ' '
					|| line[i + 1] == '\t' || line[i + 1] == '\n')
				return (0);
		}
	}
	return (1);
}

int				ft_check_empty_lines(char *line)
{
	int			i;

	if (line[0] == '\n')
		return (0);
	i = -1;
	while (line[++i])
	{
		if (line[i] && line[i] == '\n')
		{
			if (!line[i + 1] || line[i + 1] == '\n')
				return (0);
		}
	}
	if (!ft_check_semicolon(line))
		return (0);
	if (!ft_check_whitespaces(line))
		return (0);
	return (1);
}

int				ft_split_check(char *line)
{
	char		**tab;
	int			i;
	static char	*elements[] = \
	{"camera", "light", "sphere", "plane", "cone", "cylinder"};

	if (!ft_check_empty_lines(line))
		return (0);
	if (!(tab = ft_strsplit(line, '\n')))
		return (0);
	if (!ft_camera_existance_check(tab))
		return (0);
	if (!ft_strcmptable(tab[0], elements))
		return (0);
	i = -1;
	while (tab[++i])
	{
		if (tab[i] && ft_strequ(tab[i], ";"))
		{
			if (!tab[i + 1] || \
					!ft_strcmptable(tab[i + 1], elements))
				return (0);
		}
	}
	ft_strsplit_free(&tab);
	return (1);
}

t_vec			string_to_vect(char *str)
{
	t_vec		v;
	char		**split;

	ft_bzero(&v, sizeof(t_vec));
	if ((split = ft_strsplit(str, ' ')) && ft_strsplit_len(split) == 3)
	{
		v.x = ft_atof(split[0]);
		v.y = ft_atof(split[1]);
		v.z = ft_atof(split[2]);
		ft_strsplit_free(&split);
	}
	return (v);
}

int		ft_check_int(char *str)
{
	int nbr;
	printf(">>>>>> %s <<<<<<<\n", str);
	nbr = atoi(str);
	if (nbr == 0 || nbr == 1)
		return (1);
	else
		return (0);
}