# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_system.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:49:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/08/20 11:28:02 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS					=	$(shell uname -s)
CUR_DIR				=	$(abspath .)


SYSTEM_INCLUDE		=
ifeq ($(OS), Darwin)
	SYSTEM_INCLUDE	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/include
endif

