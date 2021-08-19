# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/08/19 19:03:45 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	
SRC_H_FILES		=	computor.h
LOCAL_LIBS		=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS		=	
ifneq ($(OS), Darwin)
	GLOBAL_LIBS	+=	
endif
