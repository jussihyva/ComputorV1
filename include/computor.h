/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:51:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 11:13:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_H
# define COMPUTOR_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

# define VALID_CHARACTERS		"0123456789 X^.=+-"
# define POLYNOMIAL_MAX_DEGREE	2
# define COEFFICIENT_ACCURACY	0.001

typedef enum e_side_of_equation
{
	E_LEFT,
	E_RIGHT
}				t_side_of_equation;

typedef struct s_input_params
{
	t_argc_argv			*argc_argv;
	const char			*polynomial_string;
	t_loging_level		event_logging_level;
	t_bool				print_leaks;
}				t_input_params;

typedef struct s_term
{
	double				coefficient;
	size_t				degree;
	t_bool				is_valid;
}				t_term;

typedef struct s_polynomial
{
	t_term	*term_array;
}				t_polynomial;

void			*cmd_args_init(t_argc_argv *argc_argv);
void			cmd_arg_save(void *input_params, char opt, t_argc_argv *argc_argv,
					t_cmd_param_type cmd_param_type);
void			usage_print(void);
t_polynomial	*polynomial_split_to_terms(const char *const polynomial_string);
void			term_parse(const char *const start_ptr, const char *const end_ptr,
					t_term *term);
void			polynomial_solve(t_polynomial *polynomial);

#endif
