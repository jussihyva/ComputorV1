/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:21:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 17:12:34 by jkauppi          ###   ########.fr       */
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
		if (token.token != E_DOUBLE || token.value - (int)token.value)
			print_error("Format of a term is not valid: %s", *ptr);
	}
	else if (token.token == E_EOF)
		degree = 1;
	else
		print_error("Format of a term is not valid: %s", *ptr);
	return (degree);
}

void	term_update(t_term *const term, t_term *const term_array,
				const t_list **const term_lst, t_bt_node **degree_prio_queue)
{
	const t_list		*elem;
	t_list				*new_elem;
	t_term				*term_to_update;

	if (term->degree <= POLYNOMIAL_MAX_DEGREE)
	{
		term_array[term->degree].coefficient += term->coefficient;
		term_array[term->degree].degree = term->degree;
		term_array[term->degree].is_valid = E_FALSE;
		term->is_valid = E_FALSE;
		if (fabs(term_array[term->degree].coefficient) > COEFFICIENT_ACCURACY)
		{
			term_array[term->degree].is_valid = E_TRUE;
			term->is_valid = E_TRUE;
		}
	}
	elem = *term_lst;
	while (elem)
	{
		term_to_update = (t_term *)elem->content;
		if (term_to_update->degree == term->degree)
			break ;
		elem = elem->next;
	}
	if (elem)
	{
		term_to_update->coefficient += term->coefficient;
		term_to_update->is_valid = E_FALSE;
		if (fabs(term_to_update->coefficient) > COEFFICIENT_ACCURACY)
			term_to_update->is_valid = E_TRUE;
	}
	else
	{
		new_elem = ft_lstnew(term, sizeof(*term));
		ft_lstadd((t_list **)term_lst, new_elem);
		ft_prio_enqueue(degree_prio_queue,
			(int *)&((t_term *)new_elem->content)->degree, new_elem->content);
	}
	return ;
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
