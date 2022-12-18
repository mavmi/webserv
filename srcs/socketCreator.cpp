/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketCreator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:42:25 by msalena           #+#    #+#             */
/*   Updated: 2022/12/18 22:16:48 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SocketCreator.hpp"

namespace MAIN_NAMESPACE{


SocketCreator::SocketCreator(const SocketInfomation &socket_inform){
	struct_addrinfo	hints, *ai;
	
	try {
		createInfoStructure_(hints, ai, socket_inform);
		created_socket = bindingSocket_(hints, ai, socket_inform);
		freeaddrinfo(ai);
		listeningSocket_();
	} catch (except& e) {
		throw except(e.whatMsg(), e.whatCode());
	}
}


SocketCreator::~SocketCreator(void){ }


int SocketCreator::getSocket(void) const{ return (created_socket); }


void SocketCreator::createInfoStructure_(struct_addrinfo& hints, struct_addrinfo* ai,
											const SocketInfomation& socket_inform){
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = socket_inform.ai_family;
	hints.ai_socktype = socket_inform.ai_socktype;
	hints.ai_flags = socket_inform.ai_flags;
	if (getaddrinfo(socket_inform.host, socket_inform.port, &hints, &ai) != 0){
		throw CoreException("Failed creating socket_info_struct", CRT_SOCK_ERR);
	}
}


int SocketCreator::bindingSocket_(struct_addrinfo& hints, struct_addrinfo* ai,
									const SocketInfomation& socket_inform){
	struct_addrinfo	*iterable;
	int				socket_fd, yes;
 
	yes = 1; // flag for setting setsockopt parameters
	for (iterable = ai; 
			iterable != NULL; 
			iterable->ai_next){
		socket_fd = socket(
						iterable->ai_family, 
						iterable->ai_socktype, 
						iterable->ai_protocol
						);
		if (socket_fd < 0) { continue; }
		if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0
			|| bind(socket_fd, iterable->ai_addr, iterable->ai_addrlen) < 0){
			close(socket_fd);
			continue;
		}
		break ;
	}
	if (iterable == NULL) { 
		throw CoreException("Failed binding", CRT_SOCK_ERR);
	}
	return socket_fd;
}


void SocketCreator::listeningSocket_(void){
	if (listen(created_socket, 32) < 0){
		close(created_socket);
		throw CoreException("Failed listening", CRT_SOCK_ERR);
	}
}

}