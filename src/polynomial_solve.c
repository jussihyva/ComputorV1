/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_solve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:18:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 23:06:42 by jkauppi          ###   ########.fr       */
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

static void	print_reduced_form(t_term *term_array)
{
	size_t		i;
	t_term		*term;
	size_t		print_cnt;

	print_cnt = 0;
	i = -1;
	ft_printf("Reduced form: ");
	while (++i <= POLYNOMIAL_MAX_DEGREE)
	{
		term = &term_array[i];
		if (fabs(term->coefficient) > COEFFICIENT_ACCURACY)
		{
			print_plus_minus_sign(term->coefficient);
			ft_printf("%0.1f * X^%d", term->degree, fabs(term->coefficient),
				term->degree);
			print_cnt++;
		}
	}
	if (!print_cnt)
		ft_printf("0");
	ft_printf(" = 0\n");
	return ;
}

void	polynomial_solve(t_polynomial *polynomial)
{
	double		c;
	double		b;
	double		a;

	print_reduced_form(polynomial->term_array);
	a = polynomial->term_array[2].coefficient;
	b = polynomial->term_array[1].coefficient;
	c = polynomial->term_array[0].coefficient;
	if (!polynomial->valid_terms)
		ft_printf("All real numbers are valid solutions!\n");
	else if (polynomial->valid_terms == 7
		|| polynomial->valid_terms == 5)
		polynomial_quadratic_solve(a, b, c);
	else if (polynomial->valid_terms == 3)
		polynomial_linear_solve(b, c);
	else
		ft_printf("%s %s\n", "Don't know how to calculate!",
			"Any possible solution? Maybe not.");
	return ;
}
