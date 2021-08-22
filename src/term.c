/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:21:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/22 15:40:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static double	get_coefficient(const char **ptr,
									t_side_of_equation side_of_equation,
									t_plus_minus_sign plus_minus_sign)
{
	double		coefficient;
	char		*endptr;

	coefficient = strtod(*ptr, &endptr);
	if (side_of_equation == E_RIGHT)
		coefficient *= -1;
	if (plus_minus_sign == E_MINUS)
		coefficient *= -1;
	while (*endptr == ' ')
		endptr++;
	if (*endptr != '*')
		FT_LOG_ERROR("Format of a term is not valid: %s", *ptr);
	*ptr = endptr + 1;
	return (coefficient);
}

static size_t	get_degree(const char **ptr, const char *const end_ptr)
{
	size_t		degree;
	char		*endptr;

	degree = ft_strtoi(*ptr, &endptr, 10);
	while (*endptr == ' ')
		endptr++;
	if ((*endptr && endptr != (end_ptr + 1)) || *ptr == endptr)
		FT_LOG_ERROR("Format of a term is not valid: %s", *ptr);
	*ptr = endptr;
	return (degree);
}

void	term_parse(const char *const start_ptr, const char *const end_ptr,
							t_side_of_equation side_of_equation, t_term *term, t_plus_minus_sign plus_minus_sign)
{
	double		coefficient;
	size_t		degree;
	const char	*ptr;

	ptr = (char *)start_ptr;
	coefficient = get_coefficient(&ptr, side_of_equation, plus_minus_sign);
	while (*ptr == ' ')
		ptr++;
	if (!ft_strnequ(ptr, "X^", 2))
		FT_LOG_ERROR("Format of a term is not valid: %s", ptr);
	ptr += 2;
	degree = get_degree(&ptr, end_ptr);
	if (degree > POLYNOMIAL_MAX_DEGREE)
		FT_LOG_ERROR("Biggest allowed polynomial degree is %d",
			POLYNOMIAL_MAX_DEGREE);
	term[degree].coefficient += coefficient;
	term[degree].degree = degree;
	FT_LOG_INFO("TERM: %s(%s) %f %u", start_ptr, ptr, coefficient, degree);
	return ;
}
