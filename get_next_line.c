/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaunois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:35:29 by mdaunois          #+#    #+#             */
/*   Updated: 2017/11/29 12:27:24 by mdaunois         ###   ########.fr       */
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
	if (rest)
	{
	printf("Le rest est = %s\n", rest);
		while (rest[i])
		{
			i++;
			if (rest[i] == '\0' || rest[i] == '\n')
			{
				tab2 = ft_strndup(rest, i);
			//	if (rest[i] != '\0')
				rest = ft_strdup(&rest[i + 1]);
				return (tab2);
			}
			//i++;
		}
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
//		printf("TOTO\n");
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
		//printf("le rest est = %s\n", rest);
		while (buf[i])
		{
			if (buf[i] == '\0' || buf[i] == '\n')
			{
				tab2 = ft_strncat(tab2, buf, (size_t)i);
				if(rest && rest[0] != '\n')
					tab2 = ft_strcat(rest, tab2);
				rest = ft_strdup(&buf[i + 1]);
				printf("le rest est = %s\n", rest);
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
	else
		printf("erreur");
	return (0);
}
