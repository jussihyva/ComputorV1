/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 07:18:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static const char	*get_next_ptr(const char *ptr)
{
	const char			*ptr_plus;
	const char			*ptr_minus;
	const char			*next_ptr;

	while (*ptr == ' ')
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

static const char	*get_start_pos_of_next_term(const char *const ptr,
															t_bool first_term)
{
	static const char	*equal_to_ptr;
	const char			*next_ptr;
	t_side_of_equation	side_of_equation;

	if (!equal_to_ptr)
		equal_to_ptr = ft_strchr(ptr + 1, '=');
	if (first_term == E_TRUE)
		next_ptr = get_next_ptr(ptr);
	else
		next_ptr = get_next_ptr(ptr + 1);
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

static const char	*precheck_polynomial_string(
											const char *const polynomial_string)
{
	char			*polynomial_string_no_spaces;
	const char		*ptr;
	size_t			i;

	polynomial_string_no_spaces
		= ft_memalloc(sizeof(*polynomial_string_no_spaces)
			* (ft_strlen(polynomial_string) + 1));
	i = 0;
	ptr = (const char *)polynomial_string;
	while (*ptr)
	{
		if (*ptr != ' ')
			polynomial_string_no_spaces[i++] = *ptr;
		ptr++;
	}
	return (polynomial_string_no_spaces);
}

t_polynomial	*polynomial_split_to_terms(const char *const polynomial_string)
{
	t_polynomial		*polynomial;
	const char			*ptr;
	const char			*next_ptr;
	t_bool				first_term;
	t_term				term;

	first_term = E_TRUE;
	polynomial = ft_memalloc(sizeof(*polynomial));
	polynomial->term_array = ft_memalloc(sizeof(*polynomial->term_array) * 3);
	polynomial->polynomial_string_no_spaces
		= precheck_polynomial_string(polynomial_string);
	ptr = polynomial->polynomial_string_no_spaces;
	while (*ptr)
	{
		next_ptr = get_start_pos_of_next_term(ptr, first_term);
		term_parse(ptr, next_ptr - 1, &term, first_term);
		term_update(&term, polynomial->term_array);
		ft_printf("%-70s%-50s %10.2f %10u\n", ptr, ptr, term.coefficient,
			term.degree);
		ptr = (char *)next_ptr;
		first_term = E_FALSE;
	}
	return (polynomial);
}
