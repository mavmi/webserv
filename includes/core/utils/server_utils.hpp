/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:23:10 by msalena           #+#    #+#             */
/*   Updated: 2023/02/23 15:26:52 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "../sockets.hpp"
#include "../server.hpp"
#include "../managed_fds.hpp"
#include "../../utils/utils.hpp"


namespace CORE {

/*
 * Fills masterread set with all listening sockets
 *
 * Return:	the highest socket fd
 */
int sockets_to_masterread(Sockets& sockets, ManagedFds& masterread);

void close_delete_fd(RequestsReader::managed_fds_array_iter it,
				RequestsReader::managed_fds_sets_reference fds_sets);

}
