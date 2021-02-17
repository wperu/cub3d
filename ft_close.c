/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 12:12:29 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 06:18:20 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_close(t_cub *c)
{
	int i;

	i = 0;
	while (c->m->map[i])
		free(c->m->map[i++]);
	free(c->m->map);
	mlx_clear_window(c->d->mlx_ptr, c->d->mlx_win);
	mlx_destroy_window(c->d->mlx_ptr, c->d->mlx_win);
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
	free(c);
	exit(0);
	return (1);
}
