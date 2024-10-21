/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 10:45:04 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/01/16 16:13:58 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rem(char *rem, char **line_address)
{
	char			*new;
	unsigned long	i;
	unsigned long	i2;

	i = 0;
	i2 = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] == '\n')
		i++;
	if (rem[i] == '\0')
		return (ft_free2(&rem));
	new = malloc(ft_strlen(rem) - i + 1);
	if (!new)
	{
		ft_free2(&rem);
		return (ft_free2(line_address));
	}
	while (rem[i])
		new[i2++] = rem[i++];
	new[i2] = '\0';
	ft_free2(&rem);
	return (new);
}

char	*ft_line(char *rem)
{
	char			*line;
	unsigned long	i;
	unsigned long	o;

	i = 0;
	o = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (o < i)
	{
		line[o] = rem [o];
		o++;
	}
	line[o] = '\0';
	return (line);
}

char	*ft_read(int fd, char *rem)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(GNLBUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free2(&rem));
	bytes_read = 1;
	while (ft_nlcheck(rem) == -1 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, GNLBUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			rem = ft_strjoin2(rem, buffer);
			if (!rem)
				return (ft_free2(&buffer));
		}
	}
	ft_free2 (&buffer);
	if (bytes_read < 0)
		return (ft_free2(&rem));
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*rem = 0;
	char		*line;

	if (fd < 0 || GNLBUFFER_SIZE < 0)
		return (NULL);
	rem = ft_read(fd, rem);
	if (rem == NULL)
		return (NULL);
	line = ft_line(rem);
	if (!line)
		return (ft_free2(&rem));
	rem = ft_rem(rem, &line);
	return (line);
}

// int main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = 1;
// 	fd = open("textfile.txt", O_RDONLY);
// 	if (fd == -1)
// 		printf("Opening file failed");
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("call %d: %s", i, line);
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
