# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_cmd_variables.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:50:47 by jkauppi           #+#    #+#              #
#    Updated: 2021/08/19 14:56:42 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef P
	POLYNOMIAL			=	$(P)
else
	POLYNOMIAL			=	"dsfdsfds"
endif
