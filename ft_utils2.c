/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:31:54 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 08:50:20 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_putstr(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	write(1, s, len);
}

void	ft_check_resolution(t_cub *c)
{
	int ry;
	int rx;

	mlx_get_screen_size(c->d->mlx_ptr, &rx, &ry);
	if (c->p->r_x > rx)
		c->p->r_x = rx;
	if (c->p->r_y > ry)
		c->p->r_y = ry;
}

int		ft_atoi(const char *str)
{
	int i;
	int negative;
	int result;

	result = 0;
	negative = 1;
	i = 0;
	while (((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)) && str[i])
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			negative = -1;
		i++;
	}
	while ((str[i] >= 48 && str[i] <= 57) && str[i])
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (negative * result);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < (n - 1) && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_strchr(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return (1);
	else
		return (0);
}
