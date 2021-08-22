# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_cmd_variables.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:50:47 by jkauppi           #+#    #+#              #
#    Updated: 2021/08/22 07:37:21 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef P
	POLYNOMIAL			=	$(P)
else
	POLYNOMIAL			=	"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
endif

ifdef L
	LEVEL			=	-L $(L)
else
	LEVEL			=	
endif
