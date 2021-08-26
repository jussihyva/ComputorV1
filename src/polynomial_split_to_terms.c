/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 15:06:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static const char	*get_start_pos_of_next_term(const char *ptr)
{
	while (ft_strchr("+-", *ptr))
		ptr++;
	while (*ptr && !ft_strchr("=+-", *ptr))
		ptr++;
	return (ptr);
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
		coefficient *= -1;
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
		if (*next_ptr == '=')
			side_of_equation = E_RIGHT;
		term.coefficient = coefficient_init(next_ptr, side_of_equation);
		ptr = next_ptr + 1;
	}
	return (polynomial);
}
