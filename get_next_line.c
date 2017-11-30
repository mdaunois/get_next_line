/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaunois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:35:29 by mdaunois          #+#    #+#             */
/*   Updated: 2017/11/30 17:07:01 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *s1, int size)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (s1[len])
	{
		len++;
	}
	if (size > len)
		return (0);
	if (!(ret = (char*)malloc(sizeof(char) * (size))))
		return (0);
	while (i < size)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
//	printf("dans strlen = %s\n", ret);
	return (ret);
}

int		get_file_content(int fd, char **tab2, char **rest)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*tab1;
	int		len;
	int		i;

	len = BUFF_SIZE;
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		i = 0;
		if (ret == -1 || !(tab1 = malloc(sizeof(char) * (len + 1))))
			return (-1);
		buf[ret] = '\0';
		if (*rest && !*tab2)
			*tab2 = ft_strdup(*rest);
		if (*tab2)
			tab1 = *tab2;
		len += ret;
		if (!(*tab2 = malloc(sizeof(char) * (len + 1))))
			return (-1);
		*tab2 = ft_strcpy(*tab2, tab1);
		free(tab1);
		while (buf[i])
		{
			if (buf[i] == '\n')
			{
				*tab2 = ft_strncat(*tab2, buf, (size_t)i);
//				if (buf[i + 1])
					*rest = ft_strdup(&buf[i + 1]);
//				printf("-%s\n", *tab2);
				return (1);
			}
			i++;
		}
		*tab2 = ft_strcat(*tab2, buf);
	}
//	printf("---%s\n", *tab2);
	if (*tab2)
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char	*rest;
	int			i;
	//char 		*temp;

	if (fd < 0 || fd == 1 || fd == 2 || line == NULL)
		return (-1);
	*line = NULL;
	if (ft_strlen(rest))
	{
		i = 0;
		while (rest[i])
		{
			if (rest[i] == '\n')
			{
//				printf("--%s\n", *line);
				*line = ft_strndup(rest, i);
//				printf("--%s\n", *line);
				rest = ft_strdup(&rest[i + 1]);
//				printf("--%s\n", *line);
				return (1);
			}
			i++;
		}
		if (rest && !(*line))
		{
			*line = ft_strdup(rest);
			rest = NULL;
		}
	}
	return (get_file_content(fd, line, &rest));
}
/*
int main(int argc, char *argv[])
{
	int fd;
	int val;
	char *content;

	val = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd > -1)
	{
		val = get_next_line(fd, &content);
		printf("%d\n", val);
		val = get_next_line(fd, &content);
		printf("%d\n", val);
		val = get_next_line(fd, &content);
		printf("%d\n", val);
		val = get_next_line(fd, &content);
		printf("%d\n", val);
		val = get_next_line(fd, &content);
		printf("%d\n", val);
		val = get_next_line(fd, &content);
		printf("%d\n", val);
		val = get_next_line(fd, &content);
		printf("%d\n", val);
		val = get_next_line(fd, &content);
		printf("%d\n", val);

	}
	else
		printf("erreur");
	return (0);
}*/
