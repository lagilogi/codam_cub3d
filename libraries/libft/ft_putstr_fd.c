/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 12:30:51 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/18 11:21:32 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, sizeof(char));
		s++;
	}
}

// int main(){
// 	char str[] = "bbhbhbhgv hg";
// 	int fd = open("easy.txt", O_RDWR);
// 	if (fd == -1)
// 		printf("Error opening file");
// 	ft_putstr_fd(str, fd);
// 	close(fd);

// 	return 0;
// }