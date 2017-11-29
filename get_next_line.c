/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaunois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:35:29 by mdaunois          #+#    #+#             */
/*   Updated: 2017/11/29 15:17:45 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*void	stopifendl(char *tab2, char *buf)
{
	
}
*/
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
	return (ret);
}

char	*get_file_content(int fd)
{
	char	buf[BUFF_SIZE + 1];
	static char *rest;
	int		ret;
	char	*tab1;
	char	*tab2;
	int		len;
	int		i;

	i = 0;
	len = BUFF_SIZE;
	tab2 = 0;
	if (ft_strlen(rest))
	{
//	printf("Le rest est = %s\n", rest);
		while (rest[i])
		{
			//i++;
			if (rest[i] == '\n')// || rest[i] == '\0')
			{
				tab2 = ft_strndup(rest, i);
			//	if (rest[i] != '\0')
			//	if (rest[i + 1] != '\n')
					rest = ft_strdup(&rest[i + 1]);
				return (tab2);
			}
			i++;
		}
		if (rest && !tab2)
		{
			tab2 = ft_strdup(rest);
			rest = NULL;
		}
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		i = 0;
		if (ret == -1)
			return (0);
		buf[ret] = '\0';
		if (!(tab1 = malloc(sizeof(char) * (len + 1))))
			return (0);
		if (rest && !tab2)
			tab2 = ft_strdup(rest);
		if (tab2)
			tab1 = tab2;
		len += ret;
		if (!(tab2 = malloc(sizeof(char) * (len + 1))))
			return (0);
		tab2 = ft_strcpy(tab2, tab1);
		free(tab1);
//		printf("le BUF est = %s\n", buf);
		while (buf[i])
		{
			if (/*buf[i] == '\0' ||*/ buf[i] == '\n')
			{
				tab2 = ft_strncat(tab2, buf, (size_t)i);
				if (buf[i + 1])
					rest = ft_strdup(&buf[i + 1]);
//				printf("le rest est = %s\n", rest);
				return (tab2);
			}
			i++;
		}
		tab2 = ft_strcat(tab2, buf);	
	}
	return (tab2);
}

int get_next_line(const int fd, char **line)
{
	if (fd < 0 || fd == 1 || fd == 2)
		return (-1);
	*line = get_file_content(fd);
	if (*line != 0)
	{
//		printf("----\n%s\n----\n", *line);
		return (1);
	}
	else 
		return (0);
	return (-1);
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

	}
	else
		printf("erreur");
	return (0);
}*/
