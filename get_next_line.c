/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaunois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:35:29 by mdaunois          #+#    #+#             */
/*   Updated: 2017/12/06 16:16:03 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *s1, size_t size)
{
	size_t		i;
	size_t		len;
	char		*ret;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	if (size > len)
		return (0);
	if (!(ret = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (i < size)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int		loop(char *buf, char **tab2, char **rest)
{
	int i;

	i = -1;
	while (buf[++i])
		if (buf[i] == '\n')
		{
			*tab2 = ft_strncat(*tab2, buf, i);
			*rest = ft_strdup(&buf[i + 1]);
			return (1);
		}
	return (0);
}

int		get_file_content(int fd, char **tab2, char **rest)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*tab1;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1 || !(tab1 = ft_strnew(ft_strlen(*tab2) + 1)))
			return (-1);
		buf[ret] = '\0';
		if (*tab2)
		{
			ft_strcpy(tab1, *tab2);
			free(*tab2);
		}
		if (!(*tab2 = ft_strnew((ft_strlen(tab1) + ft_strlen(buf) + 1))))
			return (-1);
		ft_strcpy(*tab2, tab1);
		free(tab1);
		if (loop(buf, tab2, rest))
			return (1);
		ft_strcat(*tab2, buf);
	}
	if (*tab2)
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*rest = NULL;
	int			i;

	if (fd < 0 || fd == 1 || fd == 2 || line == NULL)
		return (-1);
	*line = 0;
	if (ft_strlen(rest) > 0)
	{
		i = -1;
		while (rest[++i])
			if (rest[i] == '\n')
			{
				*line = ft_strndup(rest, i);
				rest = ft_strdup(&rest[i + 1]);
				return (1);
			}
		if (rest && !(*line))
		{
			*line = ft_strdup(rest);
			rest = NULL;
		}
	}
	return (get_file_content(fd, line, &rest));
}
