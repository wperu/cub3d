/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 14:49:56 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 11:06:05 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_cubed(t_cub *cube)
{
	t_text	text[6];

	ft_affiche_map(cube->m);
	cube->d->mlx_ptr = mlx_init();
	if (cube->d->mlx_ptr == NULL)
		return (0);
	ft_check_resolution(cube);
	cube->d->mlx_win = mlx_new_window(cube->d->mlx_ptr, cube->p->r_x,
	cube->p->r_y, "Cub3d");
	if (cube->d->mlx_win == NULL)
		return (0);
	ft_pos_sprite(cube);
	ft_init_ray(cube);
	ft_init_dir_pos(cube);
	ft_init_event(cube);
	ft_init_image(cube);
	if ((ft_init_text(cube, text, 64, 64) == 0))
		return (0);
	mlx_hook(cube->d->mlx_win, 2, 1, ft_press, cube);
	mlx_hook(cube->d->mlx_win, 3, 2, ft_staypress, cube);
	mlx_hook(cube->d->mlx_win, 33, 17, ft_close, cube);
	mlx_loop_hook(cube->d->mlx_ptr, ft_screen, cube);
	mlx_loop(cube->d->mlx_ptr);
	return (0);
}

void	ft_gnl_cub2(t_cub *cube, char *av)
{
	int		i;
	int		fd;
	char	*line;
	int		ret;

	fd = open(av, O_RDONLY);
	i = 0;
	ret = 0;
	while (i < cube->p->index_get && ((ret = get_next_line(fd, &line)) > 0))
	{
		free(line);
		line = NULL;
		i++;
	}
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_get_map(cube->m, line, i, cube);
		free(line);
		line = NULL;
		i++;
	}
	free(line);
	line = NULL;
	fd = close(fd);
}

void	ft_gnl_cub(t_cub *cube, char *av)
{
	int		fd;
	char	*line;
	int		ret;

	if ((fd = open(av, O_RDONLY)) == -1)
		ft_main_error(2, "", cube);
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_check(cube->p) == 0)
			cube->p->index_get++;
		if (ft_check(cube->p) && !ft_strchr(line, '1'))
			cube->p->index_get++;
		cube->m->h = cube->m->h + ft_parcing(cube->p, line, cube->m);
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	fd = close(fd);
	ft_malloc_maps(cube->m);
	ft_gnl_cub2(cube, av);
}

int		ft_init_cub(t_cub *cube, char **av)
{
	if (!(cube->p = malloc(sizeof(*cube->p))))
		return (-1);
	if (!(cube->m = malloc(sizeof(*cube->m))))
		return (-1);
	if (!(cube->e = malloc(sizeof(*cube->e))))
		return (-1);
	if (!(cube->d = malloc(sizeof(*cube->d))))
		return (-1);
	if (!(cube->im = malloc(sizeof(*cube->im))))
		return (-1);
	if (!(cube->cam = malloc(sizeof(*cube->cam))))
		return (-1);
	if (!(cube->r = malloc(sizeof(*cube->r))))
		return (-1);
	ft_init_parse_maps(cube->p, cube->m);
	ft_gnl_cub(cube, av[1]);
	if (check_info(cube) == 0)
		return (0);
	if (ft_check_error_map_v2(cube->m->map, cube) == 0)
		return (0);
	if (cube->save == 1)
		ft_save(cube);
	else
		ft_cubed(cube);
	return (0);
}

int		main(int ac, char **av)
{
	t_cub	*cube;

	if (!(cube = malloc(sizeof(*cube))))
		return (-1);
	cube->save = 0;
	if (ac < 2)
		ft_main_error(-1, "", cube);
	else if (ac > 3)
		ft_main_error(0, "", cube);
	else if (ac == 3)
	{
		if ((ft_strncmp(av[2], "--save", 7) != 0))
			return (ft_main_error(1, "", cube));
		else
			cube->save = 1;
	}
	if (ft_check_extend(av[1]) == 0)
		return (ft_main_error(-1, "", cube));
	if (ac == 2 || (ac == 3 && cube->save == 1))
		ft_init_cub(cube, av);
	return (0);
}
