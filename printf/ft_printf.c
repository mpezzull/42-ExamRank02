/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezzull <mpezzull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:16:04 by mpezzull          #+#    #+#             */
/*   Updated: 2021/02/23 18:33:03 by mpezzull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 	ft_counter(int restart, int add)
{
	static int count;
	if (restart)
		count = 0;
	if (add)
		count += add;
	return (count);
}

void	ft_putchar(int c)
{
	write(1, &c, 1);
	ft_counter(FALSE, 1);
}

int		ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9') ? TRUE : FALSE);
}

int 	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

long 	ft_exp10(int exp)
{
	if (!exp)
		return (1);
	return 10 * ft_exp10(exp - 1);
}

long 	ft_exp16(int exp)
{
	if (!exp)
		return (1);
	return 16 * ft_exp16(exp - 1);
}

void	ft_putnbr_base(unsigned int num, int base)
{
	if (num > base - 1)
	{
		ft_putnbr_base(num / base, base);
		ft_putchar("0123456789abcdef"[num % base]);
	}
	else
		ft_putchar("0123456789abcdef"[num]);
}

int		ft_parse_flag(const char *input, int i, va_list *list, t_field *field)
{
	if (input[i] == '-')
		i++;
	if (ft_isdigit(input[i]))
	{
		while (ft_isdigit(input[i]))
			field->width = field->width * 10 + (input[i++] - '0');
	}
	if (input[i] == '.')
	{
		field->precision = 0;
		while (ft_isdigit(input[++i]))
			field->precision = field->precision * 10 + input[i] - '0';
	}
	if (input[i] == 's' || input[i] == 'd' || input[i] == 'x')
		return (i);
	return (ERROR);
}

void	print_str(char *str, t_field fields)
{
	int len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (len > fields.precision && fields.precision >= 0)
		len = fields.precision;
	while (fields.width-- > len)
		ft_putchar(' ');
	while (len-- > 0)
		ft_putchar(*str++);
}

void	print_int(long num, t_field fields, int hexa)
{
	int len = 0, len_tot = 0;
	int i = 0, neg = 0;

	if (num < 0)
		neg = TRUE;
	if (num == 0 && fields.precision != 0)
		len = 1;
	while (num / (hexa ? (ft_exp16(i++)) : (ft_exp10(i++))))
		len++;
	len_tot = len;
	if (fields.precision > len)
		len_tot = fields.precision;
	while (fields.width-- > len_tot + neg)
		ft_putchar(' ');
	if (neg)
		ft_putchar('-');
	while (len_tot-- > len)
		ft_putchar('0');
	if (num != 0 || fields.precision != 0)
	{
		if (neg)
			ft_putnbr_base(-num, hexa ? 16 : 10);
		else
			ft_putnbr_base(num, hexa ? 16 : 10);
	}
}

void	ft_print(const char *input, int i, va_list *list, t_field *field)
{
	if (input[i] == 's')
		print_str(va_arg(*list, char *), *field);
	else if (input[i] == 'd')
		print_int(va_arg(*list, int), *field, FALSE);
	else if (input[i] == 'x')
		print_int(va_arg(*list, unsigned int), *field, TRUE);
}

void	ft_print_input(const char *input, va_list *list)
{
	int i = 0;
	t_field fields;

	while (input[i])
	{
		fields.precision = -1;
		fields.width = 0;
		if (input[i] == '%' && input[i + 1])
			if ((i = ft_parse_flag(input, ++i, list, &fields)) != ERROR)
				ft_print(input, i++, list, &fields);
			else
				break ;
		else
			ft_putchar(input[i++]);
	}
}

int		ft_printf(const char *input, ...)
{
	va_list list;

	ft_counter(TRUE, 0);
	va_start(list, input);
	ft_print_input(input, &list);
	va_end(list);
	return (ft_counter(FALSE, 0));
}