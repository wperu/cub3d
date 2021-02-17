/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 10:19:30 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 08:08:12 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_init_text2(t_text *text, t_cub *c)
{
	text[0].img = mlx_get_data_addr(text[0].ptr, &text[0].bpp, &text[0].sl,
	&text[0].end);
	if (text[0].img == NULL)
		return (ft_main_error(11, "Error : corruption texture north\n", c));
	text[1].img = mlx_get_data_addr(text[1].ptr, &text[1].bpp, &text[1].sl,
	&text[1].end);
	if (text[1].img == NULL)
		return (ft_main_error(11, "Error : corruption texture south\n", c));
	text[2].img = mlx_get_data_addr(text[2].ptr, &text[2].bpp, &text[2].sl,
	&text[2].end);
	if (text[2].img == NULL)
		return (ft_main_error(11, "Error : corruption texture west\n", c));
	text[3].img = mlx_get_data_addr(text[3].ptr, &text[3].bpp, &text[3].sl,
	&text[3].end);
	if (text[3].img == NULL)
		return (ft_main_error(11, "Error : corruption texture east\n", c));
	text[4].img = mlx_get_data_addr(text[4].ptr, &text[4].bpp, &text[4].sl,
	&text[4].end);
	if (text[4].img == NULL)
		return (ft_main_error(11, "Error : corruption texture sprite\n", c));
	return (1);
}

int		ft_init_text(t_cub *c, t_text *text, int w, int h)
{
	if ((text[0].ptr = mlx_xpm_file_to_image(c->d->mlx_ptr, c->p->path_tn, &w,
	&h)) == NULL)
		return (ft_main_error(11, "Error : corruption texture north\n", c));
	if ((text[1].ptr = mlx_xpm_file_to_image(c->d->mlx_ptr, c->p->path_ts, &w,
	&h)) == NULL)
		return (ft_main_error(11, "Error : corruption texture south\n", c));
	if ((text[2].ptr = mlx_xpm_file_to_image(c->d->mlx_ptr, c->p->path_te, &w,
	&h)) == NULL)
		return (ft_main_error(11, "Error : corruption texture west\n", c));
	if ((text[3].ptr = mlx_xpm_file_to_image(c->d->mlx_ptr, c->p->path_tw, &w,
	&h)) == NULL)
		return (ft_main_error(11, "Error : corruption texture east\n", c));
	if ((text[4].ptr = mlx_xpm_file_to_image(c->d->mlx_ptr, c->p->path_sprite,
	&w, &h)) == NULL)
		return (ft_main_error(11, "Error : corruption texture sprite\n", c));
	text[5].ptr = NULL;
	ft_init_text2(text, c);
	c->t = text;
	return (1);
}

void	ft_initvaltext(t_cub *c, t_text_rsc *trsc)
{
	trsc->w = 64;
	trsc->h = 64;
	trsc->lineheight = (int)(c->p->r_y / c->r->perwalldist);
	trsc->drawstart = -trsc->lineheight / 2 + c->p->r_y / 2;
	if (trsc->drawstart < 0)
		trsc->drawstart = 0;
	trsc->drawend = trsc->lineheight / 2 + c->p->r_y / 2;
	if (trsc->drawend >= c->p->r_y)
		trsc->drawend = c->p->r_y - 1;
	if (c->r->side == 0)
		trsc->wallx = c->r->posy + c->r->perwalldist * c->r->raydiry;
	else
		trsc->wallx = c->r->posx + c->r->perwalldist * c->r->raydirx;
	trsc->wallx -= floor(trsc->wallx);
	trsc->x = (int)(trsc->wallx * (double)trsc->w);
	if (c->r->side == 0 && c->r->raydirx > 0)
		trsc->x = trsc->w - trsc->x - 1;
	if (c->r->side == 1 && c->r->raydiry < 0)
		trsc->x = trsc->w - trsc->x - 1;
}

void	ft_wall_texture(t_cub *c, int x)
{
	t_text_rsc	trsc;

	ft_initvaltext(c, &trsc);
	if (c->r->side == 1)
		ft_wall_text_ns(c, &trsc, x);
	else
		ft_wall_text_we(c, &trsc, x);
}
