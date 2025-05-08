/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:56:55 by ulfernan          #+#    #+#             */
/*   Updated: 2024/11/13 15:57:19 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(args, int));
	else if (specifier == 's')
		count += print_str(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += print_digit((long)(va_arg(args, int)), 10);
	else if (specifier == 'u')
		count += print_un((unsigned long)(va_arg(args, unsigned int)), 10);
	else if (specifier == 'x')
		count += print_digit((long)(va_arg(args, unsigned int)), 16);
	else if (specifier == 'X')
		count += print_uphex((long)(va_arg(args, unsigned int)), 16);
	else if (specifier == 'p')
		count += print_ptr(va_arg(args, void *));
	else
		count += write(1, &specifier, 1);
	return (count);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && *((format + 1)) == '%')
		{
			count += write(1, "%", 1);
			format++;
		}
		else if (*format == '%')
			count += print_format(*(++format), args);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}

/*

1. We initialize the list of arguments using va_list and va_start. 
    l-> "va_start" takes a va_list argument and whatever is right 
		before the start of our list of arguments.
        l-> Now, you need to know how many arguments there are!

2.  We execute "print_format" for each argument, that is, each 
	time we see a "%".
    l-> The expression "*(++format)" passes the value stored NEXT 
		to the current pointer we are traversing. 
		l-> That will be whatever is after "%".
    l-> The expression "+=" increments the value to the left by 
		the return value of the right function, AND executes
        the function itself.

3. "print_format" executes a write function depending on the specifier 
	it finds and returns the number of bytes read
	so we can increment our "count" based on the size of each one of 
	the arguments we are writting.
	l-> Each function is expecting a value as an argument, 
		given to us by what's stored in the pointer "va_arg", 
		which contains a list with all the arguments from our 
		"va_list"; that pointer moves to the next argument
		each time is called.
	l-> A variadic function promotes certain types to another types. 
		Specifically, "char" arguments are converted to
		"int" arguments. "va_arg" expects us to feed it with the 
		proper type of the argument we are passing it,
		so even though after a "%c" specifier we will get a 
		character, the variadic functionality is going to 
		interpret it as an int. That means we have to specify the 
		type of that argument as an "int" when managing it.

4.  We feed each "print_" with the next value stored in "va_list" 
	thanks to "va_arg".
	l-> Each write function returns the number of bytes written.
	l-> "print_digit" accomodates for both base 10 and 16 numbers. 
		We use a "base" argument to manage each case, and the negatives as well. 
		If the number is smaller than the base (which will be 10 or 16), 
		you just print the number (n) by finding the "n" position of a 
		string where every posible symbol is stored; the "n" position will be
		the "n" number. 
		If the number is bigger than base, we need to find a way to print each 
		symbol of the number.
		l-> With recursion, we call the function dividing 
			the number by the base. This will occur everytime the 
			number is bigger than base.
		l-> Eventually, the number will be smaller than the base, in 
			which case it will be printed using the previous method.
		l-> Each recursive call will then advance to (n % base, base), 
			which will print the next number calculating the modulo.
		l-> All of this operations will update the value of the previous 
			"count" by one.
	l-> "print_ptr" just has to convert the adress given into a long 
		before feeding it to "print_digit".
	l-> For the unsigneds, we just copy the "print_digit" and change 
		the arguments so it can hold larger values.

X.  The final "count" will be the sum of the bytes of each 
	argument + the bytes of the literal string they are into.

*/

/*

V 0.2

Created a separate helper function for printing pointers, because I need to 
treat them as "unsigned long".

*/