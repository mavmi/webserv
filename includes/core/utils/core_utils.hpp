/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:23:10 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 19:32:01 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "../sockets.hpp"
#include "../server.hpp"
#include "../managed_fds.hpp"
#include "../../utils/utils.hpp"
#include "../../http_request_parser/http_request.hpp"
#include "../../http_response_generator/http_response.hpp"


namespace CORE {

/*
 * Fills masterread set with all listening sockets
 *
 * Return:	the highest socket fd
 */
int sockets_to_masterread(Sockets& sockets, ManagedFds& masterread);

/*
 * Create sockets for every server from config
 */
void create_sockets(const wsrv::Configuration& servers, Sockets& sockets_array);

/*
 * Generate the response for current fd
 */
void response_generator(wsrv::FdReferencePair& current_fd_pair);

/*
 * Throw exceptions if there is some problem in Server::RecvRequest_()
 */
void recv_throw(int is_fd_in_set);

}
