/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_quadratic_solve.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:06:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 18:07:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	solve_negative_discriminant(const double a, const double b,
																const double c)
{
	(void)a;
	(void)b;
	(void)c;
	return ;
}

void	polynomial_quadratic_solve(const double a, const double b,
																const double c)
{
	double		discriminant;
	double		result1;
	double		result2;

	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
	{
		solve_negative_discriminant(a, b, c);
	}
	else
	{
		result1 = (-b - sqrt(discriminant)) / (2 * a);
		result2 = (-b + sqrt(discriminant)) / (2 * a);
		ft_printf("Result1: %f\n", result1);
		if (result1 != result2)
			ft_printf("Result2: %f\n", result2);
	}
}
