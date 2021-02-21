/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:02:06 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:18:22 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_camera_existance_check(char **tab)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (tab[++i])
	{
		if (ft_strequ(tab[i], "camera"))
			j += 1;
	}
	if (j == 1)
		return (1);
	return (0);
}

int			ft_check_vec_cor(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i] && !ft_str_is_numeric(tab[i]))
			return (0);
	}
	return (1);
}

int			ft_special_vec_check(char **tab)
{
	if (ft_strequ(tab[0], "1") && ft_strequ(tab[1], "0")
			&& ft_strequ(tab[2], "0"))
		return (1);
	if (ft_strequ(tab[0], "0") && ft_strequ(tab[1], "1")
			&& ft_strequ(tab[2], "0"))
		return (1);
	if (ft_strequ(tab[0], "0") && ft_strequ(tab[1], "0")
			&& ft_strequ(tab[2], "1"))
		return (1);
	if (ft_strequ(tab[0], "-1") && ft_strequ(tab[1], "0")
			&& ft_strequ(tab[2], "0"))
		return (1);
	if (ft_strequ(tab[0], "0") && ft_strequ(tab[1], "-1")
			&& ft_strequ(tab[2], "0"))
		return (1);
	if (ft_strequ(tab[0], "0") && ft_strequ(tab[1], "0")
			&& ft_strequ(tab[2], "-1"))
		return (1);
	return (0);
}

int			ft_check_directional_vec(char *str)
{
	int		i;
	char	**tab;

	if (!(tab = ft_strsplit(str, ' ')))
		return (0);
	i = ft_strsplit_len(tab);
	if (i != 3)
		return (0);
	if (!ft_check_vec_cor(tab))
		return (0);
	if (!ft_special_vec_check(tab))
		return (0);
	ft_strsplit_free(&tab);
	return (1);
}

int			ft_check_vectors(char *str)
{
	int		i;
	char	**tab;

	if (!(tab = ft_strsplit(str, ' ')))
		return (0);
	i = ft_strsplit_len(tab);
	if (i != 3)
		return (0);
	if (!ft_check_vec_cor(tab))
		return (0);
	ft_strsplit_free(&tab);
	return (1);
}
