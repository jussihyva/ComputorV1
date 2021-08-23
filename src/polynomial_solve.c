/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_solve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:18:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 12:10:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static size_t	set_valid_flags(t_polynomial *polynomial)
{
	size_t		valid_flags;

	valid_flags = 0;
	valid_flags |= polynomial->term_array[0].is_valid << 0;
	valid_flags |= polynomial->term_array[1].is_valid << 1;
	valid_flags |= polynomial->term_array[2].is_valid << 2;
	return (valid_flags);
}

static void	solve_zero_two(const double a, const double c)
{
	double		result1;

	if ((a / c) < 0)
		ft_printf("No solution!\n");
	else
	{
		result1 = sqrt(a / c);
		ft_printf("Result1: %f\n", result1);
		ft_printf("Result1: -%f\n", result1);
	}
	return ;
}

void	polynomial_solve(t_polynomial *polynomial)
{
	double		a;
	double		b;
	double		c;
	double		result1;
	double		result2;
	size_t		valid_flags;

	a	=	polynomial->term_array[0].coefficient;
	b	=	polynomial->term_array[1].coefficient;
	c	=	polynomial->term_array[2].coefficient;
	valid_flags = set_valid_flags(polynomial);
	if (valid_flags == 5)
		solve_zero_two(-a, c);
	else if (fabs(a) < COEFFICIENT_ACCURACY && fabs(b) < COEFFICIENT_ACCURACY
		&& fabs(c) < COEFFICIENT_ACCURACY)
		ft_printf("All real numbers are valid solutions!\n");
	else if (valid_flags == 7)
	{
		if (pow(b, 2) - 4 * c * a < 0)
			FT_LOG_FATAL("No solution for complex values");
		result1 = (-b - sqrt(pow(b, 2) - 4 * c * a)) / (2 * c);
		result2 = (-b + sqrt(pow(b, 2) - 4 * c * a)) / (2 * c);
		ft_printf("Result1: %f\n", result1);
		if (result1 != result2)
			ft_printf("Result2: %f\n", result2);
	}
	else if (valid_flags == 3)
	{
		result1 = -a / b;
		ft_printf("Result1: %f\n", result1);
	}
	else
		ft_printf("Don't know how to calculate!\n");
	return ;
}
