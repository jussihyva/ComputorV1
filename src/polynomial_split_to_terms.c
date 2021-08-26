/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_split_to_terms.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:08:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 19:28:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	term_update(t_term *const term, t_list **const term_lst,
												t_bt_node **degree_prio_queue)
{
	const t_list		*elem;
	t_term				*term_to_update;

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
		term_add_to_queue(degree_prio_queue, term, term_lst);
	return ;
}

static const char	*get_start_pos_of_next_term(const char *ptr)
{
	while (ft_strchr("+-", *ptr))
		ptr++;
	while (*ptr && !ft_strchr("=+-", *ptr))
		ptr++;
	return (ptr);
}

static void	term_init(t_term *const term, const char *next_ptr,
									const t_side_of_equation side_of_equation)
{
	if (side_of_equation == E_LEFT)
		term->coefficient = 1;
	else
		term->coefficient = -1;
	if (*next_ptr == '-')
		term->coefficient *= -1;
	return ;
}

t_polynomial	*polynomial_split_to_terms(const char *const polynomial_string)
{
	t_polynomial			*polynomial;
	const char				*ptr;
	const char				*next_ptr;
	t_term					term;
	t_side_of_equation		side_of_equation;

	polynomial = polynomial_init(polynomial_string);
	ptr = polynomial->polynomial_string_no_spaces;
	term.coefficient = 1;
	side_of_equation = E_LEFT;
	while (*ptr)
	{
		next_ptr = get_start_pos_of_next_term(ptr);
		term_parse(ptr, next_ptr - 1, &term);
		term_update(&term, &polynomial->term_lst,
			&polynomial->degree_prio_queue);
		if (*next_ptr == '=')
			side_of_equation = E_RIGHT;
		term_init(&term, next_ptr, side_of_equation);
		ptr = next_ptr + 1;
	}
	return (polynomial);
}
