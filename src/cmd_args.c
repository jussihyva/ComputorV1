/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 11:28:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 10:05:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

void	*cmd_args_init(t_argc_argv *argc_argv)
{
	t_input_params			*input_params;

	input_params = (t_input_params *)ft_memalloc(sizeof(*input_params));
	input_params->argc_argv = argc_argv;
	input_params->event_logging_level = LOG_WARN;
	return ((void *)input_params);
}

static void	cmd_arg_save_short(void *input_params, char opt,
														t_argc_argv *argc_argv)
{
	t_input_params		*params;
	const char			*arg;

	params = (t_input_params *)input_params;
	if (opt == 'L')
	{
		arg = (*argc_argv->argv)[argc_argv->i];
		params->event_logging_level = ft_logging_level_param_validate(arg);
	}
	else if (opt == 'l')
		params->print_leaks = E_TRUE;
	else if (opt == 'h')
		usage_print();
	return ;
}

static void	cmd_arg_save_mandatory(void *input_params, char opt,
														t_argc_argv *argc_argv)
{
	t_input_params		*params;
	const char			*arg;

	(void)opt;
	arg = (*argc_argv->argv)[argc_argv->i];
	params = (t_input_params *)input_params;
	if (((*argc_argv->argc) - argc_argv->i) == 1)
		params->polynomial_string = arg;
	else
		usage_print();
	return ;
}

void	cmd_arg_save(void *input_params, char opt, t_argc_argv *argc_argv,
												t_cmd_param_type cmd_param_type)
{
	if (cmd_param_type == E_OPTIONAL_SHORT)
		cmd_arg_save_short(input_params, opt, argc_argv);
	else
		cmd_arg_save_mandatory(input_params, opt, argc_argv);
	return ;
}
