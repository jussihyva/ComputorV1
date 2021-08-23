/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 18:19:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/08/23 23:02:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static t_arg_parser	*arg_parser_init(const int *argc, const char ***argv)
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

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	t_input_params			*input_params;

	input_params = (t_input_params *)(*arg_parser)->input_params;
	ft_memdel((void **)&input_params);
	ft_strdel(&(*arg_parser)->options);
	ft_memdel((void **)arg_parser);
	return ;
}

static void	main_remove(t_arg_parser **arg_parser, t_polynomial **polynomial,
					t_event_logging_data **event_logging_data)
{
	t_input_params	*input_params;
	t_bool			print_leaks;

	ft_memdel((void **)&(*polynomial)->term_array);
	ft_memdel((void **)polynomial);
	input_params = (t_input_params *)(*arg_parser)->input_params;
	ft_strdel((char **)&input_params->polynomial_string);
	print_leaks = input_params->print_leaks;
	arg_parser_remove(arg_parser);
	ft_event_logging_release(event_logging_data);
	if (print_leaks)
		ft_print_leaks("computor");
	return ;
}

static const char	*get_polynomial_string_from_stdin(void)
{
	char	*polynomial_string;

	polynomial_string = NULL;
	ft_get_next_line(0, &polynomial_string);
	return (polynomial_string);
}

int	main(const int argc, const char **argv)
{
	t_arg_parser			*arg_parser;
	t_input_params			*input_params;
	t_event_logging_data	*event_logging_data;
	t_polynomial			*polynomial;

	arg_parser = arg_parser_init(&argc, &argv);
	ft_arg_parser(arg_parser);
	input_params = (t_input_params *)arg_parser->input_params;
	event_logging_data = ft_event_logging_init(
			input_params->event_logging_level);
	if (!input_params->polynomial_string)
		input_params->polynomial_string = get_polynomial_string_from_stdin();
	polynomial = polynomial_split_to_terms(input_params->polynomial_string);
	polynomial_solve(polynomial);
	main_remove(&arg_parser, &polynomial, &event_logging_data);
	return (0);
}
