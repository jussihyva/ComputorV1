/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/22 21:49:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static const char	*get_next_ptr(const char *const ptr)
{
	const char			*ptr_plus;
	const char			*ptr_minus;
	const char			*next_ptr;

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
		next_ptr = NULL;
	return (next_ptr);
}

static const char	*get_start_pos_of_next_term(const char *const ptr)
{
	static const char	*equal_to_ptr;
	const char			*next_ptr;
	t_side_of_equation	side_of_equation;

	if (!equal_to_ptr)
		equal_to_ptr = ft_strchr(ptr + 1, '=');
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

static t_term	*set_and_get_terms_start_pos(const char *polynomial)
{
	const char			*ptr;
	const char			*next_ptr;
	const char			*end_ptr;
	t_term				*term;

	term = ft_memalloc(sizeof(*term) * 3);
	ptr = polynomial;
	while (ptr)
	{
		next_ptr = get_start_pos_of_next_term(ptr);
		end_ptr = NULL;
		if (next_ptr)
			end_ptr = next_ptr - 1;
		term_parse(ptr, end_ptr, term);
		ptr = (char *)next_ptr;
	}
	return (term);
}

static void	print_terms(t_term *term)
{
	size_t	i;

	i = -1;
	while (++i <= POLYNOMIAL_MAX_DEGREE)
	{
		if (i)
			ft_printf("%0.1f * X^%d", term[i].degree, fabs(term[i].coefficient),
				term[i].degree);
		else
			ft_printf("%0.1f * X^%d", term[i].degree, term[i].coefficient,
				term[i].degree);
		if (i != POLYNOMIAL_MAX_DEGREE)
		{
			if (term[i + 1].coefficient < 0)
				ft_printf(" - ");
			else
				ft_printf(" + ");
		}
	}
	ft_printf(" = 0\n");
	return ;
}

t_bool	polynomial_split_to_terms(const char *polynomial)
{
	t_bool					is_valid;
	t_term					*term;

	term = set_and_get_terms_start_pos(polynomial);
	print_terms(term);
	ft_memdel((void **)&term);
	is_valid = E_TRUE;
	return (is_valid);
}
