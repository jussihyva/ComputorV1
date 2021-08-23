/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_quadratic_solve.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:06:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 18:25:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	solve_negative_discriminant(const double a, const double b,
											const double c, double discriminant)
{
	(void)a;
	(void)b;
	(void)c;
	(void)discriminant;
	return ;
}

static void	solve_positive_discriminant(const double a, const double b,
															double discriminant)
{
	double		result1;
	double		result2;

	result1 = (-b - sqrt(discriminant)) / (2 * a);
	result2 = (-b + sqrt(discriminant)) / (2 * a);
	ft_printf("Result1: %f\n", result1);
	ft_printf("Result2: %f\n", result2);
	return ;
}

static void	solve_zero_discriminant(const double a, const double b,
															double discriminant)
{
	double		result1;

	result1 = (-b - sqrt(discriminant)) / (2 * a);
	ft_printf("Result1: %f\n", result1);
	return ;
}

void	polynomial_quadratic_solve(const double a, const double b,
																const double c)
{
	double		discriminant;

	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		solve_negative_discriminant(a, b, c, discriminant);
	else if (discriminant > 0)
		solve_positive_discriminant(a, b, discriminant);
	else
		solve_zero_discriminant(a, b, discriminant);
}
