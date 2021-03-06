/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_quadratic_solve.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:06:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 15:27:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	solve_negative_discriminant(const double a, const double b,
																const double c)
{
	double		imaginary;
	double		real;
	size_t		i;

	ft_printf("Discriminant is strictly negative, the two solutions are:\n");
	imaginary = sqrt(fabs((-c / a) * 4 + pow(b / a, 2))) / 2;
	real = -b / a / 2;
	i = 0;
	while (++i <= 2)
	{
		if (fabs(real) > COEFFICIENT_ACCURACY)
		{
			ft_printf("%+0.2f ", real);
			if (i == 1)
				ft_printf("+ ");
			else
				ft_printf("- ");
		}
		else if (i == 2)
			ft_printf("-");
		ft_printf("%0.2fi\n", imaginary);
	}
	return ;
}

static void	solve_positive_discriminant(const double a, const double b,
															double discriminant)
{
	double		result1;
	double		result2;

	ft_printf("Discriminant is strictly positive, the two solutions are:\n");
	result1 = (-b - sqrt(discriminant)) / (2 * a);
	result2 = (-b + sqrt(discriminant)) / (2 * a);
	ft_printf("%+0.2f\n", result1);
	ft_printf("%+0.2f\n", result2);
	return ;
}

static void	solve_zero_discriminant(const double a, const double b,
															double discriminant)
{
	double		result1;

	ft_printf("Discriminant is zero (double root), the solution is:\n");
	result1 = (-b - sqrt(discriminant)) / (2 * a);
	ft_printf("%+0.2f\n", result1);
	return ;
}

void	polynomial_quadratic_solve(const double a, const double b,
																const double c)
{
	double		discriminant;

	ft_printf("Polynomial degree: 2\n");
	discriminant = pow(b, 2) - (4 * a * c);
	if (discriminant < 0)
		solve_negative_discriminant(a, b, c);
	else if (discriminant > 0)
		solve_positive_discriminant(a, b, discriminant);
	else
		solve_zero_discriminant(a, b, discriminant);
	return ;
}
