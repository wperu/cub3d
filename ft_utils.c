/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 13:36:27 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 10:49:54 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_resolution(t_parse *parse, char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] < '0' || str[i] > '9'))
		i++;
	parse->r_x = ft_atoi(str + i);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && (str[i] < 0 && str[i] > '9'))
		i++;
	parse->r_y = ft_atoi(str + i);
}

void	ft_init_parse_maps(t_parse *parse, t_map *maps)
{
	parse->r_x = 0;
	parse->r_y = 0;
	parse->path_tn = NULL;
	parse->path_ts = NULL;
	parse->path_tw = NULL;
	parse->path_te = NULL;
	parse->path_sprite = NULL;
	parse->color_f = 0;
	parse->color_c = 0;
	parse->index_get = 0;
	maps->nbsprite = 0;
	maps->w = 0;
	maps->h = 0;
	maps->map = NULL;
	maps->start_x = 0;
	maps->start_y = 0;
	maps->direction = 0;
}

char	*ft_texture(char *str)
{
	int i;

	i = 0;
	while (str[i] != '.' && str[i])
		i++;
	return (ft_strdup(str + i));
}

int		ft_malloc_maps(t_map *maps)
{
	int i;

	i = 0;
	if (!(maps->map = (char **)malloc(sizeof(char *) * (maps->h + 1))))
		return (-1);
	while (i < maps->h)
	{
		if (!(maps->map[i] = (char *)malloc(sizeof(char) * (maps->w + 1))))
			return (-1);
		i++;
	}
	maps->map[i] = NULL;
	return (0);
}

int		ft_check(t_parse *parse)
{
	if (parse->r_x && parse->r_y && parse->path_tn && parse->path_ts &&
			parse->path_tw && parse->path_te && parse->path_sprite &&
			parse->color_f && parse->color_c)
		return (1);
	return (0);
}
