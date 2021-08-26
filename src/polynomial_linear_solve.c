/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial_linear_solve.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 18:03:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 15:08:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

void	polynomial_linear_solve(const double b, const double c)
{
	double		result1;

	ft_printf("Polynomial degree: 1\n");
	result1 = -c / b;
	ft_printf("The solution is:\n%f\n", result1);
	return ;
}
