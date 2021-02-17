/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 10:45:24 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 14:29:01 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_info_begin(int id)
{
	if (id == -1)
		ft_putstr("Error: file *.cub missing\n");
	if (id == 0)
		ft_putstr("Error: too much argument\n");
	if (id == 1)
		ft_putstr("Error: option no correct, require --save");
}

void	ft_error_parse_map(int id)
{
	if (id == 2)
		ft_putstr("Error: open file *.cub failed\n");
	if (id == 3)
		ft_putstr("Error: information missing in parcing\n");
	if (id == 4)
		ft_putstr("Error: probleme resolution\n");
	if (id == 5)
		ft_putstr("Error: color ceil or floor not correct\n");
	if (id == 7)
		ft_putstr("Error: multiple player position\n");
	if (id == 8)
		ft_putstr("Error: map no valid\n");
	if (id == 9)
		ft_putstr("Error: wrong caractere in map\n");
	if (id == 10)
		ft_putstr("Error: no start position\n");
}

int		ft_main_error(int id, char *str, t_cub *c)
{
	if (id >= -1 && id <= 1)
	{
		ft_info_begin(id);
		ft_free_error(c, 1);
	}
	if (id >= 2 && id <= 10)
	{
		ft_error_parse_map(id);
		ft_free_error(c, 2);
	}
	if (id == 11)
	{
		ft_putstr(str);
		mlx_clear_window(c->d->mlx_ptr, c->d->mlx_win);
		mlx_destroy_window(c->d->mlx_ptr, c->d->mlx_win);
		ft_free_error(c, 2);
	}
	return (0);
}

void	ft_free_error(t_cub *c, int id)
{
	int i;

	i = 0;
	if (id == 2)
	{
		while (c->m->map[i])
			free(c->m->map[i++]);
		free(c->m->map);
		free(c->d);
		free(c->e);
		free(c->im);
		free(c->m);
		free(c->cam);
		free(c->r);
		free(c->p->path_sprite);
		free(c->p->path_te);
		free(c->p->path_tw);
		free(c->p->path_ts);
		free(c->p->path_tn);
		free(c->p);
	}
	if (id != 0)
		free(c);
}
