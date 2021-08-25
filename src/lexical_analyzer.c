/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 10:25:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/25 10:55:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

void	lexical_analyzer_get_next_token(const char **ptr, t_token *token)
{
	const char	*endptr;

	if (ft_strchr("+-0123456789", **ptr))
	{
		token->token = E_DOUBLE;
		token->value = strtod(*ptr, (char **)&endptr);
		if (*ptr == endptr)
			print_error("Format of a term is not valid: %s", *ptr);
	}
	else
		token->token = E_TOKEN_UNKNOWN;
	return ;
}
