/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 12:58:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/26 13:48:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static void	examples_print(void)
{
	ft_printf("\n\n Examples:\n");
	ft_printf("\n   1:\n");
	ft_printf("    ./computor\n");
	ft_printf("    1 * X^0 + 2 * X^2 = 5\n");
	ft_printf("\n   2:\n");
	ft_printf("    ./computor \"1 * X^0 + 2 * X^2 = 5\"\n");
	return ;
}

void	usage_print(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./computor\n");
	examples_print();
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  None\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -h                            Help printout\n");
	ft_printf("  -l                            %s\n",
		"Print leaks. Only in MAC-OS");
	exit(42);
}
