/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/22 15:37:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	print_logging_info(t_splitted_polynomial *splitted_polynomial)
{
	FT_LOG_INFO("Left side of equal to sign:  %s",
		splitted_polynomial->left_side);
	FT_LOG_INFO("Right side of equal to sign: %s",
		splitted_polynomial->right_side);
	return ;
}

char	*check_equal_to_sign(const char *polynomial)
{
	char	*equal_to_ptr;

	equal_to_ptr = ft_strchr(polynomial, '=');
	if (!equal_to_ptr)
		FT_LOG_ERROR("Polynomial (%s) is without =-char!", polynomial);
	else if (equal_to_ptr != ft_strrchr(polynomial, '='))
		FT_LOG_ERROR("Polynomial (%s) includes more than one =-char!",
			polynomial);
	return (equal_to_ptr);
}

static const char	*get_start_pos_of_next_term(const char *const ptr,
									t_side_of_equation side_of_equation,
									t_plus_minus_sign *const plus_minus_sign)
{
	static const char	*equal_to_ptr;
	const char			*next_ptr;
	const char			*ptr_plus;
	const char			*ptr_minus;

	*plus_minus_sign = E_PLUS;
	ptr_minus = ft_strchr(ptr, '-');
	ptr_plus = ft_strchr(ptr, '+');
	if (!equal_to_ptr)
		equal_to_ptr = ft_strchr(ptr, '=');
	if (ptr_plus && ptr_minus)
	{
		if (ptr_plus < ptr_minus)
			next_ptr = ptr_plus;
		else
		{
			next_ptr = ptr_minus;
			*plus_minus_sign = E_MINUS;
		}
	}
	else if (ptr_plus)
		next_ptr = ptr_plus;
	else if (ptr_minus)
	{
		next_ptr = ptr_minus;
		*plus_minus_sign = E_MINUS;
	}
	else
		next_ptr = NULL;
	if (side_of_equation == E_LEFT && ptr < equal_to_ptr)
	{
		if (!next_ptr && equal_to_ptr)
			next_ptr = equal_to_ptr;
		else if (equal_to_ptr < next_ptr)
		{
			next_ptr = equal_to_ptr;
			*plus_minus_sign = E_PLUS;
		}
	}
	return (next_ptr);
}

static t_term	*set_and_get_terms_start_pos(const char *polynomial,
													const char *const equal_to_ptr)
{
	const char			*ptr;
	const char			*next_ptr;
	const char			*end_ptr;
	t_term				*term;
	t_side_of_equation	side_of_equation;
	t_plus_minus_sign	plus_minus_sign;
	t_plus_minus_sign	next_plus_minus_sign;

	term = ft_memalloc(sizeof(*term) * 3);
	ptr = polynomial;
	plus_minus_sign = E_PLUS;
	while (ptr)
	{
		next_ptr = get_start_pos_of_next_term(ptr, side_of_equation, &next_plus_minus_sign);
		side_of_equation = E_LEFT;
		if (ptr >= equal_to_ptr)
			side_of_equation = E_RIGHT;
		end_ptr = NULL;
		if (next_ptr)
			end_ptr = next_ptr - 1;
		term_parse(ptr, end_ptr, side_of_equation, term, plus_minus_sign);
		ptr = (char *)next_ptr;
		if (ptr)
			ptr++;
		plus_minus_sign = next_plus_minus_sign;
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
			if (term[i+1].coefficient < 0)
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
	t_splitted_polynomial	splitted_polynomial;
	const char				*equal_to_ptr;
	t_term					*term;

	splitted_polynomial.left_side = ft_strtrim(polynomial);
	equal_to_ptr = check_equal_to_sign(polynomial);
	splitted_polynomial.right_side = ft_strtrim(equal_to_ptr + 1);
	term = set_and_get_terms_start_pos(polynomial, equal_to_ptr);
	print_terms(term);
	print_logging_info(&splitted_polynomial);
	ft_strdel(&splitted_polynomial.left_side);
	is_valid = E_TRUE;
	return (is_valid);
}
