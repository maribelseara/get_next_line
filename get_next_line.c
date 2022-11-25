/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseara <mseara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:22:12 by mseara            #+#    #+#             */
/*   Updated: 2022/11/21 15:11:42 by mseara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_locate_new_line(char *auxstr)
{
	int	i;
	int	len;

	i = 0;
	len = -1;
	if (!auxstr || auxstr == NULL)
		return (len);
	while (auxstr[i] != '\0')
	{
		if (auxstr[i] == '\n')
		{
			len = i + 1;
			break ;
		}
		i++;
	}
	return (len);
}

static char	*ft_read_from_file(char *auxstr, int fd)
{
	int		readed;
	char	*tmp;

	readed = 1;
	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (ft_free_static(&auxstr));
	while (ft_locate_new_line(auxstr) == -1 && readed > 0)
	{
		readed = read(fd, tmp, BUFFER_SIZE);
		if (readed < 0)
		{
			free(tmp);
			return (ft_free_static(&auxstr));
		}
		else if (readed > 0)
		{
			tmp[readed] = '\0';
			auxstr = ft_strjoin(auxstr, tmp);
			if (!auxstr)
				return (ft_free_static(&tmp));
		}
	}
	free(tmp);
	return (auxstr);
}

static char	*ft_make_line(char *auxstr)
{
	char	*line;
	int		len;

	if (!auxstr || auxstr == NULL || auxstr[0] == '\0')
		return (NULL);
	len = ft_locate_new_line(auxstr);
	if (len == -1)
		len = ft_strlen(auxstr);
	line = ft_substr(auxstr, 0, len);
	return (line);
}

static char	*ft_remove_line(char *auxstr)
{
	int		len;
	char	*tmp;

	len = ft_locate_new_line(auxstr);
	if (len == -1)
		return (ft_free_static(&auxstr));
	tmp = ft_substr(auxstr, len, ft_strlen(auxstr));
	if (!tmp)
		return (ft_free_static(&auxstr));
	ft_free_static(&auxstr);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*auxstr;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	auxstr = ft_read_from_file(auxstr, fd);
	if (!auxstr)
		return (NULL);
	line = ft_make_line(auxstr);
	if (line == NULL)
		return (ft_free_static(&auxstr));
	auxstr = ft_remove_line(auxstr);
	return (line);
}
