/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:10:13 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:29 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object		*ft_object_new(t_object o)
{
	t_object	*new;

	if ((new = ft_memalloc(sizeof(t_object))))
	{
		new->type = o.type;
		new->pos = o.pos;
		new->trans = o.trans;
		new->rot = o.rot;
		new->radius = o.radius;
		new->angle = o.angle;
		new->axis = o.axis;
		new->normal = o.normal;
		new->color = o.color;
		new->reflection = o.reflection;
		new->refraction = o.refraction;
		new->inside = o.inside;
		new->texture = o.texture;
		new->next = NULL;
	}
	return (new);
}

void			ft_object_push(t_object **lst, t_object *new)
{
	t_object	*p;
	if (lst == NULL || new == NULL)
		return ;
	else if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next != NULL)
		p = p->next;
	p->next = new;
}

void			ft_object_clear(t_object **lst)
{
	t_object	*p;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		p = *lst;
		if (p->next)
			*lst = p->next;
		free(p);
	}
}
