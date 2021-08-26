/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:19:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 12:23:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

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

t_polynomial	*polynomial_init(const char *const polynomial_string)
{
	t_polynomial			*polynomial;

	polynomial = ft_memalloc(sizeof(*polynomial));
	polynomial->term_array = ft_memalloc(sizeof(*polynomial->term_array) * 3);
	polynomial->polynomial_string_no_spaces
		= precheck_polynomial_string(polynomial_string);
	return (polynomial);
}