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
	char	buf[BUF_SIZE + 1];
	static char *rest;
	int		ret;
	char	*tab1;
	char	*tab2;
	int		len;
	int		i;
	int 	j;

	j = 1;
	len = BUF_SIZE;
	tab2 = 0;
	if (rest != 0)
	{	
	//	printf("le rest est %s\n", rest);
		tab2 = ft_strdup(rest);
	}
	while ((ret = read(fd, buf, BUF_SIZE)))
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
		while (buf[i])
		{
			if (buf[i] == '\n')
			{
				tab2 = ft_strncat(tab2, buf, (size_t)i);
				if (!(rest = malloc(sizeof(char) * (len + 1))))
					return (0);
			//	while (buf[i + j] != '\0' || buf[i + j] != '\n')
			//		j++;
				rest = ft_strcpy(rest, &buf[i + 1]);
			//	printf("1er rest :%s\n", rest);
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
