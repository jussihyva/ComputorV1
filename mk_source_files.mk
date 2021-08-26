# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/08/26 12:18:28 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	cmd_args.c usage_print.c polynomial_split_to_terms.c \
					term.c polynomial_solve.c polynomial_linear_solve.c \
					polynomial_quadratic_solve.c lexical_analyzer.c \
					polynomial_init.c
SRC_H_FILES		=	computor.h
LOCAL_LIBS		=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS		=	
ifeq ($(OS), Darwin)
	GLOBAL_LIBS	+=	
else
	GLOBAL_LIBS	+=	libm.a
endif
