/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:41:49 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:17:27 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_destroy(t_mx *v)
{
	mlx_destroy_image(v->mptr, v->iptr);
	mlx_clear_window(v->mptr, v->wptr);
	mlx_destroy_window(v->mptr, v->wptr);
}

void		setup(t_mx *v)
{
	v->mptr = mlx_init();
	v->wptr = mlx_new_window(v->mptr, WIN_W, WIN_H, "RT");
	v->iptr = mlx_new_image(v->mptr, WIN_W, WIN_H);
	v->rt = (int *)mlx_get_data_addr(v->iptr, &v->bpp, &v->size, &v->end);
	mlx_hook(v->wptr, 2, 0, key_press, v);
	mlx_hook(v->wptr, 17, 0, red_button, v);
}

void		display(t_mx *mx)
{
	mlx_put_image_to_window(mx->mptr, mx->wptr, mx->iptr, 0, 0);
	mlx_loop(mx->mptr);
}
