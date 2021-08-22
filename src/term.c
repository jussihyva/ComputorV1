/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:21:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/22 13:16:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static double	get_coefficient(const char **ptr,
											t_side_of_equation side_of_equation)
{
	double		coefficient;
	char		*endptr;

	coefficient = strtod(*ptr, &endptr);
	if (side_of_equation == E_RIGHT)
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
	if (*endptr && endptr != (end_ptr + 1))
		FT_LOG_ERROR("Format of a term is not valid: %s", *ptr);
	*ptr = endptr;
	return (degree);
}

void	term_parse(const char *const start_ptr, const char *const end_ptr,
											t_side_of_equation side_of_equation)
{
	double		coefficient;
	size_t		degree;
	const char	*ptr;

	(void)end_ptr;
	ptr = (char *)start_ptr;
	coefficient = get_coefficient(&ptr, side_of_equation);
	while (*ptr == ' ')
		ptr++;
	if (!ft_strnequ(ptr, "X^", 2))
		FT_LOG_ERROR("Format of a term is not valid: %s", ptr);
	ptr += 2;
	degree = get_degree(&ptr, end_ptr);
	FT_LOG_INFO("TERM: %s(%s) %f %u", start_ptr, ptr, coefficient, degree);
	return ;
}
