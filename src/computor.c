/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:19:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/20 17:58:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

t_arg_parser	*arg_parser_init(const int *argc, const char ***argv)
{
	t_arg_parser	*arg_parser;

	arg_parser = (t_arg_parser *)ft_memalloc(sizeof(*arg_parser));
	arg_parser->argc_argv.argc = argc;
	arg_parser->argc_argv.argv = argv;
	arg_parser->fn_initialize_cmd_args = cmd_args_init;
	arg_parser->fn_save_cmd_argument = cmd_arg_save;
	arg_parser->fn_usage = usage_print;
	arg_parser->options = ft_strdup("L:hl");
	return (arg_parser);
}

int	main(const int argc, const char **argv)
{
	t_arg_parser			*arg_parser;
	t_input_params			*input_params;
	t_event_logging_data	*event_logging_data;

	arg_parser = arg_parser_init(&argc, &argv);
	ft_arg_parser(arg_parser);
	input_params = (t_input_params *)arg_parser->input_params;
	event_logging_data = ft_event_logging_init(
			input_params->event_logging_level);
	if (input_params->polynomial)
		polynomial_split_to_terms(input_params->polynomial);
	else
		usage_print();
	if (input_params->print_leaks)
		ft_print_leaks("computor");
	return (0);
}
