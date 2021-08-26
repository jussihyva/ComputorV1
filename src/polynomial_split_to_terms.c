/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 12:22:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static const char	*get_next_ptr(const char *ptr)
{
	const char			*ptr_plus;
	const char			*ptr_minus;
	const char			*next_ptr;

	while (*ptr == '+')
		ptr++;
	if (*ptr == '-')
		ptr++;
	ptr_minus = ft_strchr(ptr, '-');
	ptr_plus = ft_strchr(ptr, '+');
	if (ptr_plus && ptr_minus)
	{
		if (ptr_plus < ptr_minus)
			next_ptr = ptr_plus;
		else
			next_ptr = ptr_minus;
	}
	else if (ptr_plus)
		next_ptr = ptr_plus;
	else if (ptr_minus)
		next_ptr = ptr_minus;
	else
		next_ptr = ft_strchr(ptr, '\0');
	return (next_ptr);
}

static const char	*get_start_pos_of_next_term(const char *const ptr)
{
	static const char	*equal_to_ptr;
	const char			*next_ptr;
	t_side_of_equation	side_of_equation;

	if (!equal_to_ptr)
		equal_to_ptr = ft_strchr(ptr + 1, '=');
	next_ptr = get_next_ptr(ptr);
	side_of_equation = E_LEFT;
	if (!next_ptr || equal_to_ptr < next_ptr)
		side_of_equation = E_RIGHT;
	if (side_of_equation == E_RIGHT && ptr < equal_to_ptr)
	{
		if (!next_ptr && equal_to_ptr)
			next_ptr = equal_to_ptr;
		else if (equal_to_ptr < next_ptr)
			next_ptr = equal_to_ptr;
	}
	return (next_ptr);
}

static double	coefficient_init(const char *next_ptr,
									const t_side_of_equation side_of_equation)
{
	double		coefficient;

	if (side_of_equation == E_LEFT)
		coefficient = 1;
	else
		coefficient = -1;
	if (*next_ptr == '-')
		coefficient = -1;
	return (coefficient);
}

t_polynomial	*polynomial_split_to_terms(const char *const polynomial_string)
{
	t_polynomial			*polynomial;
	const char				*ptr;
	const char				*next_ptr;
	t_term					term;
	t_side_of_equation		side_of_equation;

	polynomial = polynomial_init(polynomial_string);
	ptr = polynomial->polynomial_string_no_spaces;
	term.coefficient = 1;
	side_of_equation = E_LEFT;
	while (*ptr)
	{
		next_ptr = get_start_pos_of_next_term(ptr);
		term_parse(ptr, next_ptr - 1, &term);
		term_update(&term, polynomial->term_array);
		ft_printf("%-70s%-50s %10.2f %10u\n", ptr, next_ptr, term.coefficient,
			term.degree);
		if (*next_ptr == '=')
			side_of_equation = E_RIGHT;
		term.coefficient = coefficient_init(next_ptr, side_of_equation);
		ptr = next_ptr + 1;
	}
	return (polynomial);
}
