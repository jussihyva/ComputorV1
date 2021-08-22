/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:51:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/22 09:27:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_H
# define COMPUTOR_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

# define VALID_CHARACTERS	=	"0123456789 X^.=+-"

typedef enum e_plus_minus_sign
{
	E_PLUS,
	E_MINUS
}				t_plus_minus_sign;

typedef struct s_input_params
{
	t_argc_argv			*argc_argv;
	const char			*polynomial;
	t_loging_level		event_logging_level;
	t_bool				print_leaks;
}				t_input_params;

typedef struct s_term
{
	double				coifficient;
	size_t				exponent;
	t_plus_minus_sign	sign;
}				t_term;

typedef struct s_splitted_polynomial
{
	char	*left_side;
	char	*right_side;
}				t_splitted_polynomial;

void	*cmd_args_init(t_argc_argv *argc_argv);
void	cmd_arg_save(void *input_params, char opt, t_argc_argv *argc_argv,
			t_cmd_param_type cmd_param_type);
void	usage_print(void);
t_bool	polynomial_split_to_terms(const char *polynomial);
void	term_parse(const char *const term_string);

#endif
