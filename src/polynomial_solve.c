/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_solve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:18:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/27 00:23:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	print_plus_minus_sign(const double coefficient)
{
	static t_bool	is_first = E_TRUE;

	if (is_first == E_FALSE)
		ft_printf(" ");
	if (coefficient < 0)
		ft_printf("-");
	else if (coefficient >= 0 && is_first == E_FALSE)
		ft_printf("+");
	if (is_first == E_FALSE)
		ft_printf(" ");
	if (is_first == E_TRUE)
		is_first = E_FALSE;
	return ;
}

static void	check_degree_of_polynomial(const size_t degree_of_polynomial)
{
	if (degree_of_polynomial > POLYNOMIAL_MAX_DEGREE)
	{
		ft_printf("Polynomial degree: %u\n", degree_of_polynomial);
		ft_printf("%s%s\n", "The polynomial degree is stricly greater than 2, ",
			"I can't solve.");
		exit(42);
	}
}

static void	print_reduced_form(t_bt_node **degree_prio_queue,
													t_term *const term_array)
{
	t_term		*term;
	int			degree_of_polynomial;

	degree_of_polynomial = -1;
	ft_printf("Reduced form: ");
	while (*degree_prio_queue)
	{
		term = (t_term *)ft_prio_dequeue(degree_prio_queue);
		if (term->degree <= POLYNOMIAL_MAX_DEGREE)
			ft_memcpy(&term_array[term->degree], term, sizeof(*term));
		if (fabs(term->coefficient) > COEFFICIENT_ACCURACY)
		{
			print_plus_minus_sign(term->coefficient);
			ft_printf("%0.1f * X^%d", term->degree, fabs(term->coefficient),
				term->degree);
			degree_of_polynomial
				= ft_max_int(degree_of_polynomial, term->degree);
		}
	}
	if (degree_of_polynomial == -1)
	{
		degree_of_polynomial = 0;
		ft_printf("0");
	}
	ft_printf(" = 0\n");
	check_degree_of_polynomial(degree_of_polynomial);
	return ;
}

static size_t	set_valid_flags(t_term *term_array)
{
	size_t		valid_flags;
	size_t		i;

	valid_flags = 0;
	i = -1;
	while (++i <= POLYNOMIAL_MAX_DEGREE)
		valid_flags |= term_array[i].is_valid << i;
	return (valid_flags);
}

void	polynomial_solve(t_polynomial *polynomial)
{
	double		c;
	double		b;
	double		a;
	size_t		valid_terms;
	t_term		*term_array;

	term_array = ft_memalloc(sizeof(*term_array) * 3);
	print_reduced_form(&polynomial->degree_prio_queue, term_array);
	valid_terms = set_valid_flags(term_array);
	a = term_array[2].coefficient;
	b = term_array[1].coefficient;
	c = term_array[0].coefficient;
	if (!valid_terms)
		ft_printf("All real numbers are valid solutions!\n");
	else if (valid_terms == 7 || valid_terms == 6
		|| valid_terms == 5 || valid_terms == 4)
		polynomial_quadratic_solve(a, b, c);
	else if (valid_terms == 3 || valid_terms == 2)
		polynomial_linear_solve(b, c);
	else
		ft_printf("%s %s\n", "Don't know how to calculate!",
			"Any possible solution? Maybe not.");
	ft_memdel((void **)&term_array);
	return ;
}
