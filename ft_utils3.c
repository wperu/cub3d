/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 07:05:29 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 14:48:11 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	i = 0;
	if ((dest == src) || n == 0)
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	ft_affiche_map(t_map *maps)
{
	int i;

	i = 0;
	while (maps->map[i])
	{
		ft_putstr(maps->map[i]);
		ft_putstr("\n");
		i++;
	}
}

void	ft_get_map(t_map *maps, char *line, int i, t_cub *c)
{
	int j;
	int len;

	j = 0;
	len = ft_strlen(line);
	while (j < len)
	{
		if (maps->direction && chrd(line[j]))
		{
			ft_main_error(7, "", c);
			exit(0);
		}
		if (line[j] == 'N' || line[j] == 'E' || line[j] == 'W'
		|| line[j] == 'S')
		{
			maps->start_x = i;
			maps->start_y = j;
			maps->direction = line[j];
			maps->map[i][j] = '0';
			j++;
		}
		maps->map[i][j] = line[j];
		j++;
	}
	maps->map[i][j] = '\0';
}

int		ft_check_extend(char *str)
{
	int		i;
	int		n;
	char	*cub;

	i = 0;
	cub = ".cub";
	while (str[i])
	{
		n = 0;
		while (str[i + n] == cub[n] && cub[n])
		{
			if (str[i + n + 1] == '\0' && cub[n + 1] == '\0')
				return (1);
			n++;
		}
		i++;
	}
	return (0);
}

int		ft_position_player(t_cub *c)
{
	if (c->m->start_x == 0 || c->m->start_y == 0 ||
	c->m->start_x == c->m->h - 1)
		return (0);
	if (c->m->start_y == (int)ft_strlen(c->m->map[c->m->start_x] - 1))
		return (0);
	return (1);
}
