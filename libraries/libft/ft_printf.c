/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 13:44:11 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/01/15 17:09:01 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_converter(char c, va_list args)
{
	if (c == '%')
		return (write(1, "%", 1));
	else if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_nmbrs(va_arg(args, int), "0123456789"));
	else if (c == 'u')
		return (ft_nmbrs(va_arg(args, unsigned int), "0123456789"));
	else if (c == 'x')
		return (ft_nmbrs(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_nmbrs(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (c == 'p')
		return (ft_ptrs(va_arg(args, void *)));
	else
	{
		write(1, "%", 1);
		write(1, &c, 1);
		return (2);
	}
}

int	ft_printf(const char *str, ...)
{
	int			i;
	int			o;
	int			sum;
	va_list		args;

	va_start(args, str);
	i = 0;
	o = 0;
	while (str[i])
	{
		if (str[i] != '%')
			write(1, &str[i], 1);
		else
		{
			if (str[i + 1] == '\0')
				return (-1);
			sum = ft_converter(str[++i], args);
			o--;
			o += sum;
		}
		i++;
		o++;
	}
	va_end(args);
	return (o);
}

/*
The following main tests on most edge cases and compares
the outcomes to the original printf function.

Note to not cc with flags due to the original printf giving
warnings when testing the edge cases. The executable still
gets created and can be ran.
*/

// int	main(void)
// {
// 	char			char1 = 'q', char2 = '\t', char3 = 'string';
// 	char			str1[] = "Hello", str2[] = "", *str3 = NULL;
// 	int				int1 = 16, int2 = -2147483648, int3 = 2147483650;
// 	unsigned int	uint1 = 145, uint2 = -50, uint3 = 4294967296;
// 	int				hu1 = 14, hu2 = -5000, hu3 = 4294967296;
// 	int				hl1 = 9946843, hl2 = -2147483648, hl3 = 2147483650;
// 	int				ptr1 = 40, ptr2 = NULL, ptr3 = 'c', ptr4 = -1;
//  printf("Chars %%: %c, %c, %c\n", char1, char2, char3);
// 	ft_printf("Chars %%: %c, %c, %c\n\n", char1, char2, char3);
// 	printf("Strings: %s, %s, %s\n", str1, str2, str3);
// 	ft_printf("Strings: %s, %s, %s\n\n", str1, str2, str3);
// 	printf("Ints: %d, %i, %d\n", int1, int2, int3);
// 	ft_printf("Ints: %d, %i, %d\n\n", int1, int2, int3);
// 	printf("Unsigned: %u, %u, %u\n", uint1, uint2, uint3);
// 	ft_printf("Unsigned: %u, %u, %u\n\n", uint1, uint2, uint3);
// 	printf("Hex Upper: %X, %X, %X\n", hu1, hu2, hu3);
// 	ft_printf("Hex Upper: %X, %X, %X\n\n", hu1, hu2, hu3);
// 	printf("Hex Lower: %x, %x, %x\n", hl1, hl2, hl3);
// 	ft_printf("Hex Lower: %x, %x, %x\n\n", hl1, hl2, hl3);
// 	printf("ptrs: %p, %p, %p, %p \n", ptr1, ptr2, ptr3, ptr4);
// 	ft_printf("ptrs: %p, %p, %p, %p \n\n", ptr1, ptr2, ptr3, ptr4);
// 	printf("mix: %% %c %s %d %x\n", char1, str1, int1, hl1);
// 	ft_printf("mix: %% %c %s %d %x\n\n", char1, str1, int1, hl1);
// 	int		i;
// 	int		j;
// 	char	string1[] = "AB%sDEF";
// 	char	*string2 = "123456";
// 	ft_printf("%s", "return value check:\n");
// 	i = ft_printf(string1, string2);
// 	printf("\n%d\n", i);
// 	j = printf(string1, string2);
// 	printf("\n%d", j);
// 	if (i != j)
// 	{
// 		printf("\n\nThe value is incorrect!\ni = %d\nj = %d\n\n", i, j);
// 	}
// 	return (0);
// }
