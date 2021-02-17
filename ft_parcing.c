/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:56:59 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 08:45:45 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static unsigned int	ft_color(unsigned r, unsigned g, unsigned b)
{
	t_color	coloor;

	if (r > 255 || g > 255 || b > 255)
	{
		ft_putstr("Error: incorrect color\n");
		return (0);
	}
	else
	{
		coloor.argb.a = 0;
		coloor.argb.r = (unsigned char)r;
		coloor.argb.g = (unsigned char)g;
		coloor.argb.b = (unsigned char)b;
	}
	return (coloor.color);
}

unsigned int		ft_color_fc(char *str)
{
	unsigned	red;
	unsigned	green;
	unsigned	blue;
	int			i;

	i = 0;
	while ((str[i] < '0' || str[i] > '9') && str[i])
		i++;
	red = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
		i++;
	green = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
		i++;
	blue = ft_atoi(str + i);
	return (ft_color(red, green, blue));
}

int					chrd(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}

static int			ft_parcing2(char *line, int i, t_map *maps)
{
	if (ft_strchr(line, '1'))
	{
		if ((int)ft_strlen(line) > maps->w)
			maps->w = ft_strlen(line);
		i++;
	}
	return (i);
}

int					ft_parcing(t_parse *parse, char *line, t_map *maps)
{
	static int i;

	i = 0;
	if (ft_check(parse) == 0)
	{
		if (line[0] == 'R')
			ft_resolution(parse, line);
		if (ft_strncmp(line, "NO", 2) == 0)
			parse->path_tn = ft_texture(line);
		if (ft_strncmp(line, "SO", 2) == 0)
			parse->path_ts = ft_texture(line);
		if (ft_strncmp(line, "WE", 2) == 0)
			parse->path_tw = ft_texture(line);
		if (ft_strncmp(line, "EA", 2) == 0)
			parse->path_te = ft_texture(line);
		if (ft_strncmp(line, "S ", 2) == 0)
			parse->path_sprite = ft_texture(line);
		if (line[0] == 'F')
			parse->color_f = ft_color_fc(line);
		if (line[0] == 'C')
			parse->color_c = ft_color_fc(line);
	}
	else
		i = ft_parcing2(line, i, maps);
	return (i);
}
