/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 10:25:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 12:15:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static double	ft_strtod(const char *ptr, const char **endptr)
{
	double	value;

	errno = 0;
	value = strtod(ptr, (char **)endptr);
	if (errno || value > INT_MAX)
		print_error("Format of a term is not valid: %s", ptr);
	if (ptr == *endptr)
	{
		if (*ptr == '+')
			value = 1;
		else if (*ptr == '-')
			value = -1;
		(*endptr)++;
	}
	return (value);
}

void	lexical_analyzer_get_next_token(const char **ptr, t_token *token,
													const char *const end_ptr)
{
	const char	*endptr;

	if (*ptr == end_ptr + 1)
		token->token = E_EOF;
	else if (ft_strchr("+-0123456789", **ptr))
	{
		token->token = E_DOUBLE;
		token->value = ft_strtod(*ptr, &endptr);
		*ptr = endptr;
	}
	else
	{
		if (**ptr == 'X')
			token->token = E_X;
		else if (**ptr == '*')
			token->token = E_STAR;
		else if (**ptr == '^')
			token->token = E_EXPONENT;
		else
			print_error("Format of a term is not valid: %s", *ptr);
		(*ptr)++;
	}
	return ;
}
