/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_solve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:18:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 10:59:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

void	polynomial_solve(t_polynomial *polynomial)
{
	double		a;
	double		b;
	double		c;
	double		result1;
	double		result2;

	a	=	polynomial->term_array[0].coefficient;
	b	=	polynomial->term_array[1].coefficient;
	c	=	polynomial->term_array[2].coefficient;
	if (fabs(a) < COEFFICIENT_ACCURACY && fabs(b) < COEFFICIENT_ACCURACY
		&& fabs(c) < COEFFICIENT_ACCURACY)
		ft_printf("All real numbers are valid solutions!\n");
	else if (fabs(c) > COEFFICIENT_ACCURACY)
	{
		result1 = (-b - sqrt(pow(b, 2) - 4 * c * a)) / (2 * c);
		result2 = (-b + sqrt(pow(b, 2) - 4 * c * a)) / (2 * c);
		ft_printf("Result1: %f\n", result1);
		if (result1 != result2)
			ft_printf("Result2: %f\n", result2);
	}
	else
	{
		result1 = -a / b;
		ft_printf("Result1: %f\n", result1);
	}
	return ;
}
