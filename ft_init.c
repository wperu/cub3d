/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 18:41:18 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 09:40:29 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_init_event(t_cub *c)
{
	c->e->esc = 0;
	c->e->forward = 0;
	c->e->back = 0;
	c->e->left = 0;
	c->e->right = 0;
	c->e->turn_l = 0;
	c->e->turn_r = 0;
	c->e->ms = 0.05;
	c->e->rt = 0.05;
}

void	ft_init_ray(t_cub *c)
{
	c->r->posy = c->m->start_x + 0.5;
	c->r->posx = c->m->start_y + 0.5;
	c->r->planex = 0.66;
	c->r->planey = 0;
	c->r->camerax = 0;
	c->r->raydirx = 0;
	c->r->raydiry = 0;
	c->r->sidedistx = 0;
	c->r->sidedisty = 0;
	c->r->side = 0;
	c->r->deltadistx = 0;
	c->r->deltadisty = 0;
	c->r->mapx = 0;
	c->r->mapy = 0;
	c->r->stepx = 0;
	c->r->stepy = 0;
	c->r->perwalldist = 0;
	c->r->hit = 0;
	c->text = 1;
}

void	ft_init_image(t_cub *c)
{
	c->im->adr = NULL;
	c->im->ptr = NULL;
	c->im->bpp = 0;
	c->im->sl = 0;
	c->im->end = 0;
}

void	ft_init_sp(t_cub *c, int *sp_order, double *sp_dist)
{
	int i;

	i = 0;
	while (i < c->m->nbsprite)
	{
		sp_dist[i] = ((c->r->posx - c->s[i].x) * (c->r->posx - c->s[i].x) +
		(c->r->posy - c->s[i].y) * (c->r->posy - c->s[i].y));
		sp_order[i] = i;
		i++;
	}
	ft_sp_rk(sp_order, sp_dist, c->m->nbsprite);
}
