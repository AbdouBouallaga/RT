/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 00:31:07 by ahkhilad          #+#    #+#             */
/*   Updated: 2021/03/06 17:35:31 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define BUFF_SIZE 100000

# define WIN_W 1280
# define WIN_H 720

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <time.h>
# include "../libft/libft.h"
# include "../linearlib/linear_alg.h"

// typedef struct			s_opncl
// {
// 	cl_kernel			kl;
// 	cl_command_queue	cmdqu;
// 	cl_context			cxt;
// 	cl_int				err;
// 	cl_uint				ndvs;
// 	cl_device_id		dvs;
// 	const char			*fl;
// 	size_t				rtsz;
// 	size_t				bfsz;
// 	cl_mem				img;
// 	cl_mem				inpts;
// 	cl_program			program;
// 	cl_kernel			kernel;
// 	char				*program_source;
// }						t_opncl;

typedef struct			s_uv
{
	float				u;
	float				v;
}						t_uv;

typedef struct			s_intersect
{
	float				k;
	float				a;
	float				b;
	float				c;
	float				delta;
	float				t1;
	float				t2;
}						t_intersect;

typedef struct			s_texture
{
	char				*type;
	int					width;
	int					height;
	t_vec				*data;
}						t_texture;

typedef struct			s_base
{
	int					i;
	int					p;
	int					rt;
	int					n;
	int					somme;
}						t_base;

typedef struct			s_cam
{
	t_vec				pos;
	t_vec				forward;
	t_vec				u;
	t_vec				v;
	t_vec				lower_left_corner;
	t_vec				horizontal;
	t_vec				vertical;
	float				fov;
}						t_cam;

typedef struct			s_ray
{
	t_vec				source;
	t_vec				direction;
}						t_ray;

typedef enum			e_type
{
	NONE,
	SPHERE = 10,
	PLANE,
	CONE,
	CYLINDER
}						t_type;

typedef enum			e_inside
{
	AIR,
	GLASS,
	MIRROR,
	mNONE
}						t_inside;

typedef struct			s_object
{
	int					reflection;
	int					refraction;
	t_inside			inside;
	t_type				type;
	t_vec				pos;
	t_vec				trans;
	t_vec				rot;
	t_vec				color;
	float				radius;
	float				angle;
	t_vec				normal;
	t_vec				axis;
	t_texture			texture;
	struct s_object		*next;
	

	t_intersect			sp;
	t_intersect			cy;
	t_intersect			cn;
}						t_object;

typedef struct			s_light
{
	t_vec				pos;
	t_vec				plus;
	t_vec				color;
	float				intensity;
	struct s_light		*next;
	float				lambert;
	float				ambient_strenght;
	float				reflect;
	float				phong_term;
}						t_light;

typedef struct			s_hit
{
	t_vec				n;
	t_vec				p;
	t_object			*object;
	float				t;
}						t_hit;

typedef struct			s_mx
{
	void				*mptr;
	void				*wptr;
	void				*iptr;
	int					*rt;
	int					bpp;
	int					size;
	int					end;
	t_object			*objects;
	t_light				*lights;
	t_cam				cam;
	int					len;
	float				vfov;
	int					fd;
	int					rd;
	char				*tmp;
	char				*line;
}						t_mx;

int						ft_open(char *str, t_mx *v);
void					ft_usage(void);
void					ft_destroy(t_mx *v);
int						key_press(int keycode, void *p);
int						red_button(void *p);
void					setup(t_mx *v);
void					update(t_mx *mx);
void					display(t_mx *mx);
void					update2(t_mx *mx);
void					run(t_mx *mx);
float					clamp(float value, float min, float max);
t_vec					clamp_vect(t_vec v);
int						rgb_to_int(t_vec v);
int						shadow_cast(t_object *lst, t_ray *ray, float *tmin);
t_object				*ft_object_new(t_object o);
void					ft_object_push(t_object **lst, t_object *nw);
void					ft_object_clear(t_object **lst);
t_light					*ft_light_new(t_vec pos, t_vec color, float intensity);
void					ft_light_push(t_light **lst, t_light *nw);
void					ft_light_clear(t_light **lst);
void					ft_strsplit_free(char ***tab);
int						ft_strsplit_len(char **tab);
int						ft_special_atoi_base(char *str);
t_vec					vect_from_hexa(int rgb);
t_vec					string_to_vect(char *str);
float					deg_to_rad(float angle);
t_vec					x_rotation(t_vec v, float theta);
t_vec					y_rotation(t_vec v, float theta);
t_vec					z_rotation(t_vec v, float theta);
int						ft_parse_sphere(t_mx *v, char **token);
int						ft_parse_plane(t_mx *v, char **token);
int						ft_parse_cone(t_mx *v, char **token);
int						ft_parse_cylinder(t_mx *v, char **token);
int						ft_parse_light(t_mx *v, char **token);
int						ft_parse_camera(t_mx *v, char **token);
t_cam					ft_camera_create(t_vec pos, t_vec at, t_vec vup, \
						float vfov);
t_ray					camera_ray(t_cam *cam, int x, int y);
int						sphere_intersect(t_object *sphere, \
						t_ray *ray, float *tmin);
int						plane_intersect(t_object *plane, \
						t_ray *ray, float *tmin);
int						cylinder_intersect(t_object *cylinder, \
						t_ray *ray, float *tmin);
int						cone_intersect(t_object *cone, t_ray *ray, float *tmin);
int						raycast(t_object *lst, t_ray *raw, t_hit *hit);
t_vec					ft_rotate_object(t_vec to_rot, t_vec rot, int invert);
t_vec					ft_translate_object(t_vec to_trans, \
						t_vec trans, int invert);
t_ray					ft_transform_ray(t_object *obj, t_ray *raw, int invert);
void					ft_compute_normals(t_hit *hit, t_ray *ray);
int						shadow_cast(t_object *lst, t_ray *ray, float *tmin);
void					tokenfill_sphere(char **token, t_object *object);
void					tokenfill_plane(char **token, t_object *object);
void					tokenfill_cone(char **token, t_object *object);
void					tokenfill_cylinder(char **token, t_object *object);

int						ft_split_check(char *line);
int						ft_check_vectors(char *str);
int						ft_check_directional_vec(char *str);
int						ft_check_floats(char *str);
int						ft_check_positive_floats(char *str);
int						ft_check_camera_fov(char *str);
int						ft_check_hex_color(char *str);
int						ft_camera_existance_check(char **tab);
int						ft_check_vec_cor(char **tab);
int						ft_special_vec_check(char **tab);
char					*ft_strcmptable(const char *str, char **tab);
int						ft_parse_camera(t_mx *v, char **token);
int						ft_check_int(char *str);
int						ft_parse_spot(t_mx *v, char **token);
void					uv_chek(t_object *obj, int width, int height,int size);
t_vec					vector3(float x, float y, float z);
int						vec3equ(t_vec v1, t_vec v2);
void					gettexture(t_hit *hit);
t_vec					shadowinside(t_mx *mx, t_vec color, t_hit hit);
int						ft_parse_spotlight(t_mx *v, char **token);
t_ray					raycastloop(t_object *p, t_hit *hit, t_ray *raw, float t);
t_object				*shadow_l(t_object *lst, t_ray *ray, float *tmin);
#endif
