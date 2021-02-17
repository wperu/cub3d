/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:12:26 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 07:54:21 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_wall_ns(t_cub *c, int x)
{
	if (c->r->raydiry >= 0)
	{
		while (c->cam->drawstart < c->cam->drawend)
		{
			*(int *)(&c->im->adr[((c->cam->drawstart * c->im->sl / 4) + x) *
			c->im->bpp]) = 13434726;
			c->cam->drawstart++;
		}
	}
	else
	{
		while (c->cam->drawstart < c->cam->drawend)
		{
			*(int *)(&c->im->adr[((c->cam->drawstart * c->im->sl / 4) + x) *
			c->im->bpp]) = 13369344;
			c->cam->drawstart++;
		}
	}
}

void	ft_wall_we(t_cub *c, int x)
{
	if (c->r->raydirx >= 0)
	{
		while (c->cam->drawstart < c->cam->drawend)
		{
			*(int *)(&c->im->adr[((c->cam->drawstart * c->im->sl / 4) + x) *
					c->im->bpp]) = 52224;
			c->cam->drawstart++;
		}
	}
	else
	{
		while (c->cam->drawstart < c->cam->drawend)
		{
			*(int *)(&c->im->adr[((c->cam->drawstart * c->im->sl / 4) + x) *
			c->im->bpp]) = 16776960;
			c->cam->drawstart++;
		}
	}
}

void	ft_wall(t_cub *c, int x)
{
	c->cam->lineheight = (int)(c->p->r_y / c->r->perwalldist);
	c->cam->drawstart = -c->cam->lineheight / 2 + c->p->r_y / 2;
	if (c->cam->drawstart < 0)
		c->cam->drawstart = 0;
	c->cam->drawend = c->cam->lineheight / 2 + c->p->r_y / 2;
	if (c->cam->drawend >= c->p->r_y)
		c->cam->drawend = c->p->r_y - 1;
	if (c->r->side == 1)
		ft_wall_ns(c, x);
	else
		ft_wall_we(c, x);
}

void	ft_wall_text_ns(t_cub *c, t_text_rsc *trsc, int x)
{
	if (c->r->raydiry >= 0)
	{
		while (trsc->drawstart < trsc->drawend)
		{
			trsc->y = abs((((trsc->drawstart * 256 - c->p->r_y * 128 +
			trsc->lineheight * 128) * 64) / trsc->lineheight) / 256);
			ft_memcpy(c->im->adr + 4 * c->p->r_x * trsc->drawstart
			+ x * 4, &c->t[1].img[trsc->y % 64 * c->t[1].sl + trsc->x % 64
			* c->t[1].bpp / 8], sizeof(int));
			trsc->drawstart++;
		}
	}
	else
	{
		while (trsc->drawstart < trsc->drawend)
		{
			trsc->y = abs((((trsc->drawstart * 256 - c->p->r_y * 128 +
			trsc->lineheight * 128) * 64) / trsc->lineheight) / 256);
			ft_memcpy(c->im->adr + 4 * c->p->r_x * trsc->drawstart
			+ x * 4, &c->t[0].img[trsc->y % 64 * c->t[0].sl + trsc->x % 64
			* c->t[0].bpp / 8], sizeof(int));
			trsc->drawstart++;
		}
	}
}

void	ft_wall_text_we(t_cub *c, t_text_rsc *trsc, int x)
{
	if (c->r->raydirx >= 0)
	{
		while (trsc->drawstart < trsc->drawend)
		{
			trsc->y = abs((((trsc->drawstart * 256 - c->p->r_y * 128 +
			trsc->lineheight * 128) * 64) / trsc->lineheight) / 256);
			ft_memcpy(c->im->adr + 4 * c->p->r_x * trsc->drawstart
			+ x * 4, &c->t[3].img[trsc->y % 64 * c->t[3].sl + trsc->x % 64
			* c->t[3].bpp / 8], sizeof(int));
			trsc->drawstart++;
		}
	}
	else
	{
		while (trsc->drawstart < trsc->drawend)
		{
			trsc->y = abs((((trsc->drawstart * 256 - c->p->r_y * 128 +
			trsc->lineheight * 128) * 64) / trsc->lineheight) / 256);
			ft_memcpy(c->im->adr + 4 * c->p->r_x * trsc->drawstart
			+ x * 4, &c->t[2].img[trsc->y % 64 * c->t[2].sl + trsc->x % 64
			* c->t[2].bpp / 8], sizeof(int));
			trsc->drawstart++;
		}
	}
}
