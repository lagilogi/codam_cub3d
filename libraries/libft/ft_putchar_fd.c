/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 10:34:36 by wsonepou      #+#    #+#                 */
/*   Updated: 2023/10/18 11:21:26 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int main(){
// 	char c = 'c';
// 	int fd = open("eas.txt", O_RDWR);
// 	if (fd == -1)
// 		printf("Error");
// 	ft_putchar_fd(c, fd);
// 	close(fd);
// 	return 0;
// }

// Filedescriptor is an identifier for an opened file that is represented
// by an integer, like ..100, 101, 102..

//write(a, b, c);
// a = Filedescriptor
// b = Points to the buffer
// c = unsigned integer that specifies the maximum number of bytes we want
// to write from the buffer to the file