/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_alg.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:08:06 by babdelka          #+#    #+#             */
/*   Updated: 2021/01/29 15:29:32 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINEAR_ALG_H
# define LINEAR_ALG_H

# include <math.h>

typedef struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

float			ft_magnitude(t_vec v);
t_vec			ft_normalize(t_vec v);
t_vec			ft_negative(t_vec v);
float			ft_dotproduct(t_vec a, t_vec b);
t_vec			ft_crossproduct(t_vec a, t_vec b);
t_vec			ft_vectoradd(t_vec a, t_vec b);
t_vec			ft_vectorsub(t_vec a, t_vec b);
t_vec			ft_vectormulti(t_vec c, float scalar);

#endif
