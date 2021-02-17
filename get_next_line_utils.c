/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 06:48:39 by wperu             #+#    #+#             */
/*   Updated: 2020/10/24 09:46:59 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_checkerror(int fd, char **line, char **str)
{
	if (fd == -1 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!*str)
	{
		if (!(*str = malloc(sizeof(char*) * (1))))
			return (-1);
		*str[0] = '\0';
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	size_t	i;
	size_t	len;
	char	*dest;
	char	*temp;

	i = 0;
	temp = (char *)s;
	len = ft_strlen(s);
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		dest[i] = temp[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (!(sub = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = NULL;
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + (ft_strlen(s2) + 1)))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
