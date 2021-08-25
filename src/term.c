/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:21:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/25 14:11:35 by jkauppi          ###   ########.fr       */
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

static double	get_coefficient(const char **ptr)
{
	double			coefficient;
	t_token			token;

	coefficient = 0;
	lexical_analyzer_get_next_token(ptr, &token);
	if (token.token == E_DOUBLE)
		coefficient = token.value;
	else if (token.token == E_X)
	{
		coefficient = 1;
		(*ptr)--;
	}
	return (coefficient);
}

static size_t	get_degree(const char **ptr, const char *const end_ptr)
{
	size_t			degree;
	t_token			token;

	if (*ptr == end_ptr + 1 || !end_ptr)
		degree = 0;
	else
	{
		degree = 0;
		lexical_analyzer_get_next_token(ptr, &token);
		if (token.token == E_STAR)
			lexical_analyzer_get_next_token(ptr, &token);
		if (token.token != E_X)
			print_error("Format of a term is not valid: %s", *ptr);
		lexical_analyzer_get_next_token(ptr, &token);
		if (token.token == E_EXPONENT)
		{
			lexical_analyzer_get_next_token(ptr, &token);
			if (token.token == E_DOUBLE)
				degree = token.value;
			else
				print_error("Format of a term is not valid: %s", *ptr);
		}
		else if (token.token == E_EOF)
			degree = 0;
		else
			print_error("Format of a term is not valid: %s", *ptr);
	}
	return (degree);
}

void	term_parse(const char *const start_ptr, const char *const end_ptr,
										t_term *term_array, t_bool first_term)
{
	static t_side_of_equation	side_of_equation = E_LEFT;
	double						coefficient;
	size_t						degree;
	const char					*ptr;

	ptr = (char *)start_ptr;
	if (side_of_equation == E_LEFT && *ptr == '=')
		side_of_equation = E_RIGHT;
	if (first_term == E_FALSE && (*ptr == '+' || *ptr == '-' || *ptr == '='))
		ptr++;
	coefficient = get_coefficient(&ptr);
	if (first_term == E_FALSE
		&& (side_of_equation == E_RIGHT ^ *start_ptr == '-'))
		coefficient *= -1;
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
