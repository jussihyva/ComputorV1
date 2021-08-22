/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/22 09:28:39 by jkauppi          ###   ########.fr       */
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

static const char	*get_start_pos_of_next_term(const char *const ptr)
{
	const char		*next_ptr;
	const char		*ptr_plus;
	const char		*ptr_minus;

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

static t_term	*set_and_get_terms_start_pos(char *polynomial)
{
	char		*ptr;
	const char	*next_ptr;
	t_term		*term;

	term = ft_memalloc(sizeof(*term) * 3);
	ptr = polynomial;
	while (ptr)
	{
		next_ptr = get_start_pos_of_next_term(ptr);
		if (next_ptr)
		{
			term_parse(ptr);
			ptr = (char *)next_ptr;
			*ptr++ = '\0';
		}
		else
			ptr = (char *)next_ptr;
	}
	return (term);
}

t_bool	polynomial_split_to_terms(const char *polynomial)
{
	t_bool					is_valid;
	t_splitted_polynomial	splitted_polynomial;
	char					*equal_to_ptr;
	t_term					*term_left;
	t_term					*term_right;

	splitted_polynomial.left_side = ft_strtrim(polynomial);
	equal_to_ptr = check_equal_to_sign(splitted_polynomial.left_side);
	*equal_to_ptr = '\0';
	splitted_polynomial.right_side = ft_strtrim(equal_to_ptr + 1);
	term_left = set_and_get_terms_start_pos(splitted_polynomial.left_side);
	term_right = set_and_get_terms_start_pos(splitted_polynomial.right_side);
	print_logging_info(&splitted_polynomial);
	ft_strdel(&splitted_polynomial.left_side);
	is_valid = E_TRUE;
	return (is_valid);
}
