/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:24:07 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/14 18:27:10 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float ft_fmap(float x, float inmin, float inmax, float outmin, float outmax)
{
    return (x - inmin) * (outmax - outmin) / (inmax - inmin) + outmin;
}