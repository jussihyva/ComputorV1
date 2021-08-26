/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:21:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 13:38:16 by jkauppi          ###   ########.fr       */
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

static double	get_coefficient(const char **ptr, const char *const end_ptr)
{
	double			coefficient;
	t_token			token;

	coefficient = 0;
	lexical_analyzer_get_next_token(ptr, &token, end_ptr);
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

	degree = 0;
	lexical_analyzer_get_next_token(ptr, &token, end_ptr);
	if (token.token == E_STAR)
		lexical_analyzer_get_next_token(ptr, &token, end_ptr);
	if (token.token != E_X)
		print_error("Format of a term is not valid: %s", *ptr);
	lexical_analyzer_get_next_token(ptr, &token, end_ptr);
	if (token.token == E_EXPONENT)
	{
		lexical_analyzer_get_next_token(ptr, &token, end_ptr);
		degree = token.value;
		if (token.token != E_DOUBLE)
			print_error("Format of a term is not valid: %s", *ptr);
	}
	else if (token.token == E_EOF)
		degree = 1;
	else
		print_error("Format of a term is not valid: %s", *ptr);
	return (degree);
}

void	term_update(const t_term *const term, t_term *const term_array)
{
	term_array[term->degree].coefficient += term->coefficient;
	term_array[term->degree].degree = term->degree;
	term_array[term->degree].is_valid = E_FALSE;
	if (fabs(term_array[term->degree].coefficient) > COEFFICIENT_ACCURACY)
		term_array[term->degree].is_valid = E_TRUE;
	return ;
}

void	term_parse(const char *const start_ptr, const char *const end_ptr,
																t_term *term)
{
	const char					*ptr;

	ptr = (char *)start_ptr;
	term->coefficient *= get_coefficient(&ptr, end_ptr);
	if (ptr == end_ptr + 1)
		term->degree = 0;
	else
		term->degree = get_degree(&ptr, end_ptr);
	if (term->degree > POLYNOMIAL_MAX_DEGREE)
		print_error("Highest supported polynomial degree is %d",
			ft_itoa(POLYNOMIAL_MAX_DEGREE));
	return ;
}
