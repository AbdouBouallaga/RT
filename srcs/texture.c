/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:28:11 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/21 17:18:05 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_uv maptexture(t_hit *hit)
{
    t_vec e1;
    t_vec e2;
    t_uv uv;
    e1 = ft_normalize(ft_crossproduct(hit->n, vector3(1,0,0)));
    if (vec3equ(e1, vector3(0,0,0)))
    {
        e1 = ft_normalize(ft_crossproduct(hit->n, vector3(0,0,1)));
    }
    e2 = ft_normalize(ft_crossproduct(hit->n, e1));
    uv.v = ft_dotproduct(e1, hit->p);
    uv.u = ft_dotproduct(e2, hit->p);
    return (uv);
}

void    gettexture(t_hit *hit)
{
    t_uv uv;
    uv = maptexture(hit);
    // printf("u = %f\n", uv.u);
    // printf("v = %f\n", uv.v);
    // printf("width %d\n", hit->object->texture.width);
    // printf("height %d\n", hit->object->texture.height);
    // printf("v = %f\n", uv.v);
    // printf("u = %f\n", uv.u);
    if (uv.u < 0)
        uv.u *= -2.0f;
    else
        uv.u *= 1.0f;
    if (uv.v < 0)
        uv.v *= -2.0f;
    else
        uv.v *= 1.0;
    float x = ft_fmap(uv.u, 0.0f, 999999.0f, 0.0f, hit->object->texture.width);
    float y = ft_fmap(uv.v, 0.0f, 999999.0f, 0.0f, hit->object->texture.height);
    // printf("x = %f\n", x);
    // printf("y = %f\n", y);
    // printf("float<<<< %f >>>>\n", (x*y));
    // printf("int<<<< %d >>>>\n", (int)(x*y));
    int tx = (int)fabs(x*y);
    int max = hit->object->texture.width * hit->object->texture.height;
    hit->object->color = hit->object->texture.data[tx%max];
}

void tinit(t_object *obj, int x, int y)
{
    obj->texture.height = (int)y;
    obj->texture.width = (int)x;
    int total = y * x;
    obj->texture.data = (t_vec *)malloc(sizeof(t_vec) * total);
}

void uv_chek(t_object *obj, int width, int height,int size)
{
    int i = 0;
    int one = 0;
    int two = 0;
    int three = 0;
    size*=10;
    height *=size;
    width *=size;
    int total = height * width;
    tinit(obj, width, height);

    while(i < total)
    {
        if(one < size){
            obj->texture.data[i].x = 255.0f;
            obj->texture.data[i].y = 255.0f;
            obj->texture.data[i].z = 255.0f;
            one++;
            }
        else if (two < size*3){
            obj->texture.data[i].x = 0.0f;
            obj->texture.data[i].y = 0.0f;
            obj->texture.data[i].z = 0.0f;
            two++;
        }
        else if (one == size && two == size){
            one = 1;
            two = 0;
            obj->texture.data[i].x = 255.0f;
            obj->texture.data[i].y = 255.0f;
            obj->texture.data[i].z = 255.0f;
        }
        // printf("%d x %f\n", i,t->data[i].x);
        // printf("%d y %f\n", i,t->data[i].y);
        // printf("%d z %f\n", i,t->data[i].z);
        i++;
    }
}