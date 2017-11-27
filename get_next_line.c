/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaunois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:35:29 by mdaunois          #+#    #+#             */
/*   Updated: 2017/11/27 17:37:50 by mdaunois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*void	stopifendl(char *tab2, char *buf)
{
	
}
*/
char	*get_file_content(int fd)
{
	char	buf[BUFF_SIZE + 1];
	static char *rest;
	int		ret;
	char	*tab1;
	char	*tab2;
	int		len;
	int		i;
	int 	j;
	int fin;

	fin = 0;
	j = 1;
	len = BUFF_SIZE;
	tab2 = 0;
	if (rest != 0)
		tab2 = ft_strdup(rest);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		i = 0;
		if (ret == -1)
			return (0);
		buf[ret] = '\0';
		if (!(tab1 = malloc(sizeof(char) * (len + 1))))
			return (0);
		if (tab2)
			tab1 = tab2;
		len += ret;
		if (!(tab2 = malloc(sizeof(char) * (len + 1))))
			return (0);
		tab2 = ft_strcpy(tab2, tab1);
		free(tab1);
		printf("ret = %d\n", ret);
		while (buf[i])
		{
			if (buf[i] == '\n' || buf[i] == '\0')
			{
				ret = ret - i;
				printf("ret apres = %d\n", ret);
				tab2 = ft_strncat(tab2, buf, (size_t)i);
				while (buf[i + j] != '\0')
				{
					if (buf[i + j] == '\n')
						return (tab2);
					j++;
				}
				if (!(rest = malloc(sizeof(char) * (len + 1))))
					return (0);
				rest = ft_strcpy(rest, &buf[i + 1]);
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
	if (fd < 0)
		return (-1);
	*line = get_file_content(fd);
	if (ft_strlen(*line) > 0)
	{
		printf("%s\n", *line);
		return (1);
	}
	else 
		return (0);
	return (-1);
}

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
}
