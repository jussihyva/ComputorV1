/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/20 19:00:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

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

void	set_and_get_terms_start_pos(char *polynomial)
{
	char	*split_ptr;
	char	*split_ptr_minus;
	char	*split_ptr_plus;

	split_ptr_minus = polynomial;
	while (split_ptr_minus)
	{
		split_ptr = ft_strchr(split_ptr_minus, '-');
		split_ptr_plus = ft_strchr(split_ptr_minus, '+');
		split_ptr_minus = split_ptr;
		while (split_ptr_plus
			&& (split_ptr_plus < split_ptr_minus || !split_ptr_minus))
		{
			*split_ptr_plus++ = '\0';
			split_ptr_plus = ft_strchr(split_ptr_plus, '+');
		}
		if (split_ptr_minus)
			*split_ptr_minus++ = '\0';
	}
	return ;
}

t_bool	polynomial_split_to_terms(const char *polynomial)
{
	t_bool					is_valid;
	t_splitted_polynomial	splitted_polynomial;
	char					*equal_to_ptr;

	splitted_polynomial.left_side_of_equal_to_sign = ft_strdup(polynomial);
	equal_to_ptr
		= check_equal_to_sign(splitted_polynomial.left_side_of_equal_to_sign);
	*equal_to_ptr = '\0';
	splitted_polynomial.right_side_of_equal_to_sign = equal_to_ptr + 1;
	set_and_get_terms_start_pos(splitted_polynomial.left_side_of_equal_to_sign);
	set_and_get_terms_start_pos(
		splitted_polynomial.right_side_of_equal_to_sign);
	FT_LOG_INFO("Left side of equal to sign: %s",
		splitted_polynomial.left_side_of_equal_to_sign);
	FT_LOG_INFO("Right side of equal to sign: %s",
		splitted_polynomial.right_side_of_equal_to_sign);
	ft_strdel(&splitted_polynomial.left_side_of_equal_to_sign);
	is_valid = E_TRUE;
	return (is_valid);
}
