/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 11:19:10 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 07:40:26 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	ft_rota(t_cub *c)
{
	double olddirx;
	double oldplanex;

	if (c->e->turn_l == 1)
	{
		olddirx = c->r->dirx;
		c->r->dirx = c->r->dirx * cos(-c->e->rt) - c->r->diry * sin(-c->e->rt);
		c->r->diry = olddirx * sin(-c->e->rt) + c->r->diry * cos(-c->e->rt);
		oldplanex = c->r->planey;
		c->r->planey = c->r->planey * cos(c->e->rt) - c->r->planex
			* sin(c->e->rt);
		c->r->planex = oldplanex * sin(c->e->rt) + c->r->planex
		* cos(c->e->rt);
	}
	if (c->e->turn_r == 1)
	{
		olddirx = c->r->dirx;
		c->r->dirx = c->r->dirx * cos(c->e->rt) - c->r->diry * sin(c->e->rt);
		c->r->diry = olddirx * sin(c->e->rt) + c->r->diry * cos(c->e->rt);
		oldplanex = c->r->planey;
		c->r->planey = c->r->planey * cos(-c->e->rt) - c->r->planex
		* sin(-c->e->rt);
		c->r->planex = oldplanex * sin(-c->e->rt) + c->r->planex
		* cos(-c->e->rt);
	}
}

void	ft_move(t_cub *c)
{
	if (c->e->forward == 1)
	{
		if (c->m->map[(int)(c->r->posy)]
				[(int)(c->r->posx + c->r->dirx * c->e->ms)] != '1')
			c->r->posx += c->r->dirx * c->e->ms;
		if (c->m->map[(int)(c->r->posy + c->r->diry * c->e->ms)]
				[(int)(c->r->posx)] != '1')
			c->r->posy += c->r->diry * c->e->ms;
	}
	if (c->e->back == 1)
	{
		if (c->m->map[(int)(c->r->posy)][(int)(c->r->posx - c->r->dirx
					* c->e->ms)] != '1')
			c->r->posx -= c->r->dirx * c->e->ms;
		if (c->m->map[(int)(c->r->posy - c->r->diry * c->e->ms)]
				[(int)(c->r->posx)] != '1')
			c->r->posy -= c->r->diry * c->e->ms;
	}
	ft_move2(c);
	ft_rota(c);
}

void	ft_move2(t_cub *c)
{
	if (c->e->left == 1)
	{
		if (c->m->map[(int)(c->r->posy)]
				[(int)(c->r->posx - c->r->planex * c->e->ms)] != '1')
			c->r->posx = c->r->posx - c->r->planex * c->e->ms;
		if (c->m->map[(int)(c->r->posy - c->r->planey * c->e->ms)]
				[(int)(c->r->posx)] != '1')
			c->r->posy = c->r->posy - c->r->planey * c->e->ms;
	}
	if (c->e->right == 1)
	{
		if (c->m->map[(int)(c->r->posy)][(int)(c->r->posx + c->r->planex
					* c->e->ms)] != '1')
			c->r->posx = c->r->posx + c->r->planex * c->e->ms;
		if (c->m->map[(int)(c->r->posy + c->r->planey * c->e->ms)]
				[(int)(c->r->posx)] != '1')
			c->r->posy = c->r->posy + c->r->planey * c->e->ms;
	}
}

int		ft_staypress(int key, t_cub *c)
{
	if (key == 65307)
		c->e->esc = 0;
	else if (key == 119)
		c->e->forward = 0;
	else if (key == 115)
		c->e->back = 0;
	else if (key == 97)
		c->e->left = 0;
	else if (key == 100)
		c->e->right = 0;
	else if (key == 65361)
		c->e->turn_l = 0;
	else if (key == 65363)
		c->e->turn_r = 0;
	return (0);
}

int		ft_press(int key, t_cub *c)
{
	if (key == 65307)
		c->e->esc = 1;
	else if (key == 119)
		c->e->forward = 1;
	else if (key == 115)
		c->e->back = 1;
	else if (key == 97)
		c->e->left = 1;
	else if (key == 100)
		c->e->right = 1;
	else if (key == 65361)
		c->e->turn_l = 1;
	else if (key == 65363)
		c->e->turn_r = 1;
	return (0);
}
