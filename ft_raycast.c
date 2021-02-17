/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 19:12:36 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 14:51:44 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_init_dir_pos(t_cub *cube)
{
	if (cube->m->direction == 'N')
	{
		cube->r->dirx = 0;
		cube->r->diry = -1;
	}
	if (cube->m->direction == 'S')
	{
		cube->r->dirx = 0;
		cube->r->diry = 1;
		cube->r->planex = -0.66;
	}
	if (cube->m->direction == 'W')
	{
		cube->r->dirx = -1;
		cube->r->diry = 0;
		cube->r->planex = 0;
		cube->r->planey = -0.66;
	}
	if (cube->m->direction == 'E')
	{
		cube->r->dirx = 1;
		cube->r->diry = 0;
		cube->r->planex = 0;
		cube->r->planey = 0.66;
	}
}

void	ft_side_step(t_cub *c)
{
	if (c->r->raydirx < 0)
	{
		c->r->stepx = -1;
		c->r->sidedistx = (c->r->posx - c->r->mapx) * c->r->deltadistx;
	}
	else
	{
		c->r->stepx = 1;
		c->r->sidedistx = (c->r->mapx + 1.0 - c->r->posx) * c->r->deltadistx;
	}
	if (c->r->raydiry < 0)
	{
		c->r->stepy = -1;
		c->r->sidedisty = (c->r->posy - c->r->mapy) * c->r->deltadisty;
	}
	else
	{
		c->r->stepy = 1;
		c->r->sidedisty = (c->r->mapy + 1.0 - c->r->posy) * c->r->deltadisty;
	}
}

void	ft_dda(t_cub *c, int x)
{
	while (c->r->hit == 0)
	{
		if (c->r->sidedistx < c->r->sidedisty)
		{
			c->r->sidedistx += c->r->deltadistx;
			c->r->mapx += c->r->stepx;
			c->r->side = 0;
		}
		else
		{
			c->r->sidedisty += c->r->deltadisty;
			c->r->mapy += c->r->stepy;
			c->r->side = 1;
		}
		if (c->m->map[c->r->mapy][c->r->mapx] == '1')
			c->r->hit = 1;
	}
	if (c->r->side == 0)
		c->r->perwalldist = (c->r->mapx - c->r->posx +
		(1 - c->r->stepx) / 2) / c->r->raydirx;
	else
		c->r->perwalldist = (c->r->mapy - c->r->posy +
		(1 - c->r->stepy) / 2) / c->r->raydiry;
	c->buff[x] = c->r->perwalldist;
}

void	ft_ray(t_cub *c)
{
	int x;

	x = 0;
	c->buff = malloc(sizeof(double) * c->p->r_x);
	while (x < c->p->r_x)
	{
		c->r->camerax = 2 * x / (double)c->p-> r_x - 1;
		c->r->raydirx = c->r->dirx + c->r->planex * c->r->camerax;
		c->r->raydiry = c->r->diry + c->r->planey * c->r->camerax;
		c->r->mapx = (int)c->r->posx;
		c->r->mapy = (int)c->r->posy;
		c->r->deltadistx = fabs(1 / c->r->raydirx);
		c->r->deltadisty = fabs(1 / c->r->raydiry);
		ft_side_step(c);
		ft_dda(c, x);
		if (c->text == 1)
			ft_wall_texture(c, x);
		else
			ft_wall(c, x);
		c->r->hit = 0;
		x++;
	}
}

int		ft_screen(t_cub *c)
{
	int	i;

	i = 0;
	c->im->ptr = mlx_new_image(c->d->mlx_ptr, c->p->r_x, c->p->r_y);
	c->im->adr = mlx_get_data_addr(c->im->ptr,
	&c->im->bpp, &c->im->sl, &c->im->end);
	c->im->bpp = c->im->bpp / 8;
	while (i < c->p->r_x * (c->p->r_y / 2))
		*(int *)&c->im->adr[i++ * c->im->bpp] = c->p->color_c;
	while (i < c->p->r_x * (c->p->r_y))
		*(int *)&c->im->adr[i++ * c->im->bpp] = c->p->color_f;
	ft_ray(c);
	ft_sprite(c);
	free(c->buff);
	ft_move(c);
	mlx_put_image_to_window(c->d->mlx_ptr, c->d->mlx_win, c->im->ptr, 0, 0);
	if (c->save == 0)
		mlx_destroy_image(c->d->mlx_ptr, c->im->ptr);
	if (c->e->esc == 1)
		ft_close(c);
	return (0);
}
