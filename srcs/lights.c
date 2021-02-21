/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:09:26 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:20 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light			*ft_light_new(t_vec pos, t_vec color, float intensity)
{
	t_light		*new;

	if ((new = ft_memalloc(sizeof(t_light))))
	{
		new->pos = pos;
		new->color = color;
		new->intensity = intensity;
		new->next = NULL;
	}
	return (new);
}

void			ft_light_push(t_light **lst, t_light *new)
{
	t_light		*ptr;

	if (lst == NULL || new == NULL)
		return ;
	else if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		ptr = *lst;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

void			ft_light_clear(t_light **lst)
{
	t_light		*ptr;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		ptr = *lst;
		if (ptr->next)
			*lst = ptr->next;
		free(ptr);
	}
}
