/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 10:25:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/25 17:53:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

void	lexical_analyzer_get_next_token(const char **ptr, t_token *token,
													const char *const end_ptr)
{
	const char	*endptr;

	if (*ptr == end_ptr + 1)
		token->token = E_EOF;
	else if (ft_strchr("+-0123456789", **ptr))
	{
		token->token = E_DOUBLE;
		errno = 0;
		token->value = strtod(*ptr, (char **)&endptr);
		if (*ptr == endptr || errno || token->value > INT_MAX)
			print_error("Format of a term is not valid: %s", *ptr);
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
