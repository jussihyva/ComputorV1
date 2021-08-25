/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:21:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/25 10:50:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

void	print_error(const char *const string1, const char *const string2)
{
	ft_printf(string1, string2);
	ft_printf("\n");
	exit(42);
	return ;
}

static double	get_coefficient(const char **ptr,
						t_side_of_equation side_of_equation, t_bool first_term)
{
	double		coefficient;
	char		*endptr;
	const char	*start_ptr;

	start_ptr = *ptr;
	if (first_term == E_FALSE && (**ptr == '+' || **ptr == '-' || **ptr == '='))
		(*ptr)++;
	coefficient = strtod(*ptr, &endptr);
	if (*ptr == endptr)
		coefficient = 1;
	else if (first_term == E_FALSE
		&& (side_of_equation == E_RIGHT ^ *start_ptr == '-'))
		coefficient *= -1;
	while (*endptr == ' ')
		endptr++;
	*ptr = endptr;
	return (coefficient);
}

static t_bool	is_star_char(const char **ptr)
{
	t_bool	is_star_char;

	is_star_char = E_FALSE;
	while (**ptr == ' ')
		(*ptr)++;
	if (**ptr == '*')
	{
		is_star_char = E_TRUE;
		(*ptr)++;
	}
	while (**ptr == ' ')
		(*ptr)++;
	return (is_star_char);
}

static size_t	get_degree(const char **ptr, const char *const end_ptr)
{
	size_t		degree;
	char		*endptr;

	degree = 0;
	while (**ptr == ' ' && *ptr < end_ptr)
		(*ptr)++;
	if (!is_star_char(ptr))
		degree = 0;
	else if (ft_strnequ(*ptr, "X^", 2))
	{
		*ptr += 2;
		degree = ft_strtoi(*ptr, &endptr, 10);
		while (*endptr == ' ')
			endptr++;
		if ((*endptr && endptr != (end_ptr + 1)) || *ptr == endptr)
			print_error("Format of a term is not valid: %s", *ptr);
		*ptr = endptr;
	}
	else if (ft_strnequ(*ptr, "X", 1))
	{
		*ptr += 1;
		degree = 1;
	}
	else
		print_error("Format of a term is not valid: %s", *ptr);
	return (degree);
}

void	term_parse(const char *const start_ptr, const char *const end_ptr,
										t_term *term_array, t_bool first_term)
{
	static t_side_of_equation	side_of_equation = E_LEFT;
	double						coefficient;
	size_t						degree;
	const char					*ptr;
	t_token						token;

	ptr = (char *)start_ptr;
	if (side_of_equation == E_LEFT && *ptr == '=')
		side_of_equation = E_RIGHT;
	lexical_analyzer_get_next_token(&ptr, &token);
	coefficient = get_coefficient(&ptr, side_of_equation, first_term);
	degree = get_degree(&ptr, end_ptr);
	if (degree > POLYNOMIAL_MAX_DEGREE)
		print_error("Highest supported polynomial degree is %d",
			ft_itoa(POLYNOMIAL_MAX_DEGREE));
	term_array[degree].coefficient += coefficient;
	term_array[degree].degree = degree;
	term_array[degree].is_valid = E_FALSE;
	if (fabs(term_array[degree].coefficient) > COEFFICIENT_ACCURACY)
		term_array[degree].is_valid = E_TRUE;
	ft_printf("%-70s%-50s %10.2f %10u\n", start_ptr, ptr, coefficient, degree);
	return ;
}
