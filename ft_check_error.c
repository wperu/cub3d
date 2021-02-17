/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:59:54 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 14:39:24 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_info(t_cub *c)
{
	int i;

	i = 0;
	if (c->p->r_y || c->p->r_x)
		i++;
	if (c->m->w || c->m->h)
		i++;
	if (c->p->path_tn)
		i++;
	if (c->p->path_ts)
		i++;
	if (c->p->path_tw)
		i++;
	if (c->p->path_te)
		i++;
	if (c->p->path_sprite)
		i++;
	if (c->p->color_f)
		i++;
	if (c->p->color_c)
		i++;
	if (i != 9)
		return (ft_main_error(3, "", c));
	return (1);
}

int	check_around(char **map, int i, int j, int h)
{
	int ret;

	ret = 0;
	if (i < h)
		if (map[i + 1][j] == ' ')
			ret++;
	if (i > 0)
		if (map[i - 1][j] == ' ')
			ret++;
	if (j < (int)ft_strlen(map[i]))
		if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
			ret++;
	if (j > 0)
		if (map[i][j - 1] == ' ')
			ret++;
	return (ret);
}

int	ft_check_error_map_v2(char **map, t_cub *c)
{
	int i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || i == c->m->h - 1) && (map[i][j] == '0' ||
			map[i][j] == '2'))
				return (ft_main_error(8, "", c));
			if ((j == 0 || j == (int)ft_strlen(map[i]) - 1) && (map[i][j] == '0'
			|| map[i][j] == '2'))
				return (ft_main_error(8, "", c));
			if ((map[i][j] == '0' || map[i][j] == '2') &&
			(check_around(map, i, j, c->m->h) != 0))
				return (ft_main_error(8, "", c));
			j++;
		}
		i++;
	}
	if (ft_position_player(c) == 0)
		return (ft_main_error(8, "", c));
	return (-1);
}
