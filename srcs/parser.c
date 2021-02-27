/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babdelka <babdelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 21:42:36 by babdelka          #+#    #+#             */
/*   Updated: 2021/02/27 18:15:58 by babdelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_token_handle(t_mx *v, char **token)
{
	if (token[0] && ft_strequ(token[0], "light"))
		if (!ft_parse_light(v, token))
			return (0);
	if (token[0] && ft_strequ(token[0], "spotlight"))
		if (!ft_parse_spotlight(v, token))
			return (0);
	if (token[0] && ft_strequ(token[0], "sphere"))
		if (!ft_parse_sphere(v, token))
			return (0);
	if (token[0] && ft_strequ(token[0], "plane"))
		if (!ft_parse_plane(v, token))
			return (0);
	if (token[0] && ft_strequ(token[0], "cone"))
		if (!ft_parse_cone(v, token))
			return (0);
	if (token[0] && ft_strequ(token[0], "cylinder"))
		if (!ft_parse_cylinder(v, token))
			return (0);
	if (token[0] && ft_strequ(token[0], "camera"))
		if (!ft_parse_camera(v, token))
			return (0);
	return (1);
}

int			ft_blocks(t_mx *v, char *line)
{
	char	**blocks;
	char	**tokens;
	int		i;

	if (!ft_split_check(line))
		return (0);
	if (!(blocks = ft_strsplit(line, ';')))
		return (0);
	i = -1;
	tokens = NULL;
	while (blocks[++i])
	{
		if (!(tokens = ft_strsplit(blocks[i], '\n')))
		{
			ft_strsplit_free(&blocks);
			return (0);
		}
		if (!ft_token_handle(v, tokens))
			return (0);
		ft_strsplit_free(&tokens);
	}
	ft_strsplit_free(&blocks);
	return (1);
}

int			ft_open(char *str, t_mx *v)
{
	
	char	buff[BUFF_SIZE + 1];

	if (!(v->fd = open(str, O_RDONLY)) || (v->fd < 1 || v->fd > 4096))
	{
		close(v->fd);
		return (0);
	}
	v->line = ft_strnew(0);
	while ((v->rd = read(v->fd, buff, BUFF_SIZE)) > 0)
	{
		if (buff[0] != '\0' && !ft_isalnum(buff[0]))
			break ;
		buff[v->rd] = '\0';
		v->tmp = v->line;
		v->line = ft_strjoin(v->line, buff);
		free(v->tmp);
	}
	if (!ft_blocks(v, v->line) && !v->objects)
	{
		free(v->line);
		return (0);
	}
	free(v->line);
	close(v->fd);
	return (1);
}
