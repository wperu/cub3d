/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 10:16:19 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 09:39:56 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_texture_sprite(t_cub *c, t_sprite_rsc *srsc)
{
	int stripe;
	int y;

	stripe = srsc->drawstartx;
	while (stripe < srsc->drawendx)
	{
		srsc->texx = (int)((256 * (stripe - (-srsc->w / 2 + srsc->screenx))
		* srsc->textw / srsc->w) / 256);
		y = srsc->drawstarty;
		while (y < srsc->drawendy && srsc->transformy > 0 && srsc->transformy
		< c->buff[stripe])
		{
			srsc->d = y * 256 - c->p->r_y * 128 + srsc->h * 128;
			srsc->texy = ((srsc->d * srsc->texth) / srsc->h) / 256;
			if (c->t[4].img[srsc->texy % 64 * c->t[4].sl + srsc->texx % 64
					* c->t[4].bpp / 8] != 0)
			{
				ft_memcpy(c->im->adr + 4 * c->p->r_x * y + stripe * 4,
				&c->t[4].img[srsc->texy % 64 * c->t[4].sl + srsc->texx % 64
				* c->t[4].bpp / 8], sizeof(int));
			}
			y++;
		}
		stripe++;
	}
}

void	ft_dsprite(t_sprite_rsc *srsc, int *sp_order, t_cub *c)
{
	srsc->x = c->s[sp_order[srsc->i]].x - c->r->posx;
	srsc->y = c->s[sp_order[srsc->i]].y - c->r->posy;
	srsc->inv_det = 1.0 / (c->r->planex * c->r->diry - c->r->dirx
	* c->r->planey);
	srsc->transformx = srsc->inv_det * (c->r->diry * srsc->x - c->r->dirx
	* srsc->y);
	srsc->transformy = srsc->inv_det * (-c->r->planey * srsc->x + c->r->planex
			* srsc->y);
	srsc->screenx = (int)((c->p->r_x / 2) * (1 + srsc->transformx /
				srsc->transformy));
	srsc->h = abs((int)(c->p->r_y / srsc->transformy));
	srsc->drawstarty = -srsc->h / 2 + c->p->r_y / 2;
	if (srsc->drawstarty < 0)
		srsc->drawstarty = 0;
	srsc->drawendy = srsc->h / 2 + c->p->r_y / 2;
	if (srsc->drawendy >= c->p->r_y)
		srsc->drawendy = c->p->r_y - 1;
	srsc->w = abs((int)(c->p->r_y / srsc->transformy));
	srsc->drawstartx = -srsc->w / 2 + srsc->screenx;
	if (srsc->drawstartx < 0)
		srsc->drawstartx = 0;
	srsc->drawendx = srsc->w / 2 + srsc->screenx;
	if (srsc->drawendx >= c->p->r_x)
		srsc->drawendx = c->p->r_x - 1;
}

void	ft_sp_rk(int *sp_order, double *sp_dist, int nbsprite)
{
	int		i;
	int		tmp_order;
	double	tmp_dist;

	i = 0;
	while (i < nbsprite - 1)
	{
		if (sp_dist[i] < sp_dist[i + 1])
		{
			tmp_dist = sp_dist[i];
			sp_dist[i] = sp_dist[i + 1];
			sp_dist[i + 1] = tmp_dist;
			tmp_order = sp_order[i];
			sp_order[i] = sp_order[i + 1];
			sp_order[i + 1] = tmp_order;
			i = -1;
		}
		i++;
	}
}

void	ft_sprite(t_cub *c)
{
	int					sp_order[c->m->nbsprite];
	double				sp_dist[c->m->nbsprite];
	t_sprite_rsc		srsc;

	ft_init_sp(c, sp_order, sp_dist);
	srsc.textw = 64;
	srsc.texth = 64;
	srsc.i = 0;
	while (srsc.i < c->m->nbsprite)
	{
		ft_dsprite(&srsc, sp_order, c);
		ft_texture_sprite(c, &srsc);
		srsc.i++;
	}
}

void	ft_pos_sprite(t_cub *c)
{
	int y;
	int x;
	int n;

	y = 0;
	n = 0;
	while (c->m->map[y])
	{
		x = 0;
		while (c->m->map[y][x])
		{
			if (c->m->map[y][x] == '2')
			{
				c->m->nbsprite++;
				c->s[n].x = (double)x + 0.5;
				c->s[n].y = (double)y + 0.5;
				n++;
			}
			x++;
		}
		y++;
	}
}
