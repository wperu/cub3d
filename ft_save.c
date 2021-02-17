/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 09:22:26 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 10:57:15 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_init_save(t_cub *c, t_save *sv)
{
	sv->size = 54 + 4 * c->p->r_x * c->p->r_y;
	sv->unused = 0;
	sv->offset_begin = 54;
	sv->head_bytes = 40;
	sv->plane = 1;
	sv->bpp = 32;
	sv->fd = open("cub3d.bmp", O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	if (sv->fd == -1)
		ft_main_error(11, "Error: open file .bmp\n", c);
}

void	ft_write_text_bmp_file(t_cub *c, int fd)
{
	int	y;
	int	x;
	int	line;

	y = 0;
	while (y < c->p->r_y)
	{
		x = 0;
		line = c->p->r_x * (c->p->r_y - y);
		while (x < c->p->r_x)
		{
			write(fd, &c->im->adr[line * 4], 4);
			line++;
			x++;
		}
		y++;
	}
}

void	ft_wrt_bmp_file(t_cub *c)
{
	t_save sv;

	ft_init_save(c, &sv);
	write(sv.fd, "BM", 2);
	write(sv.fd, &sv.size, sizeof(int));
	write(sv.fd, &sv.unused, sizeof(int));
	write(sv.fd, &sv.offset_begin, sizeof(int));
	write(sv.fd, &sv.head_bytes, sizeof(int));
	write(sv.fd, &c->p->r_x, sizeof(int));
	write(sv.fd, &c->p->r_y, sizeof(int));
	write(sv.fd, &sv.plane, sizeof(short int));
	write(sv.fd, &sv.bpp, sizeof(short int));
	write(sv.fd, &sv.unused, sizeof(int));
	write(sv.fd, &sv.unused, sizeof(int));
	write(sv.fd, &sv.unused, sizeof(int));
	write(sv.fd, &sv.unused, sizeof(int));
	write(sv.fd, &sv.unused, sizeof(int));
	write(sv.fd, &sv.unused, sizeof(int));
	ft_write_text_bmp_file(c, sv.fd);
	close(sv.fd);
}

void	ft_save(t_cub *c)
{
	t_text t[6];

	ft_pos_sprite(c);
	ft_init_ray(c);
	ft_init_dir_pos(c);
	ft_init_event(c);
	ft_init_image(c);
	c->d->mlx_ptr = mlx_init();
	if (c->d->mlx_ptr == NULL)
		ft_main_error(11, "Error: init mlx fail\n", c);
	ft_check_resolution(c);
	c->d->mlx_win = mlx_new_window(c->d->mlx_ptr, c->p->r_x, c->p->r_y,
	"save");
	if (c->d->mlx_win == NULL)
		ft_main_error(11, "Error: Windows fail\n", c);
	ft_init_text(c, t, 64, 64);
	ft_screen(c);
	ft_wrt_bmp_file(c);
	ft_close(c);
}
