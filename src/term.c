/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:21:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 22:22:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

void	print_error(const char *const string1, const char *const string2)
{
	ft_printf(string1, string2);
	ft_printf("\n");
	exit(42);
	return ;
}

static double	get_coefficient(const char **ptr, const char *const end_ptr)
{
	double			coefficient;
	t_token			token;

	coefficient = 0;
	lexical_analyzer_get_next_token(ptr, &token, end_ptr);
	if (token.token == E_DOUBLE)
		coefficient = token.value;
	else if (token.token == E_X)
	{
		coefficient = 1;
		(*ptr)--;
	}
	return (coefficient);
}

static size_t	get_degree(const char **ptr, const char *const end_ptr)
{
	size_t			degree;
	t_token			token;

	degree = 0;
	lexical_analyzer_get_next_token(ptr, &token, end_ptr);
	if (token.token == E_STAR)
		lexical_analyzer_get_next_token(ptr, &token, end_ptr);
	if (token.token != E_X)
		print_error("Format of a term is not valid: %s", *ptr);
	lexical_analyzer_get_next_token(ptr, &token, end_ptr);
	if (token.token == E_EXPONENT)
	{
		lexical_analyzer_get_next_token(ptr, &token, end_ptr);
		degree = token.value;
		if (token.token != E_DOUBLE || token.value - (int)token.value
			|| degree > INT_MAX)
			print_error("Format of a term is not valid: %s", *ptr);
	}
	else if (token.token == E_EOF)
		degree = 1;
	else
		print_error("Format of a term is not valid: %s", *ptr);
	return (degree);
}

void	term_add_to_queue(t_bt_node **degree_prio_queue, t_term *term,
															t_list **term_lst)
{
	t_list				*new_elem;

	term->is_valid = E_FALSE;
	if (fabs(term->coefficient) > COEFFICIENT_ACCURACY)
		term->is_valid = E_TRUE;
	term->degree_key = htonl(term->degree);
	new_elem = ft_lstnew(term, sizeof(*term));
	ft_lstadd(term_lst, new_elem);
	ft_prio_enqueue(degree_prio_queue,
		&((t_term *)new_elem->content)->degree_key, new_elem->content);
}

void	term_parse(const char *const start_ptr, const char *const end_ptr,
																t_term *term)
{
	const char					*ptr;

	ptr = (char *)start_ptr;
	term->coefficient *= get_coefficient(&ptr, end_ptr);
	if (ptr == end_ptr + 1)
		term->degree = 0;
	else
		term->degree = get_degree(&ptr, end_ptr);
	return ;
}
