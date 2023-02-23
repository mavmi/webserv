/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_creator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:42:25 by msalena           #+#    #+#             */
/*   Updated: 2023/02/23 18:50:14 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core/socket_creator.hpp"

namespace CORE{

int SocketFdCreator::CreateSocketFd(SocketFdCreator::const_server_type_reference socket_inform){
	struct_addrinfo			hints; 
	struct_addrinfo_pointer	ai;
	int 					created_socket;

	FillingInfoStruct_(hints, &ai, socket_inform);
	/*
	struct addrinfo {
		int	ai_flags;
		int	ai_family;
		int	ai_socktype;
		int	ai_protocol;
		socklen_t ai_addrlen;
		char	*ai_canonname;
		struct	sockaddr *ai_addr;
		struct	addrinfo *ai_next;
		};
	*/
	std::cout << "ai_flag: " << ai->ai_flags << std::endl
		<< "ai_family: " << ai->ai_family << std::endl
		<< "ai_socktype: " << ai->ai_socktype << std::endl
		<< "ai_protocol: " << ai->ai_protocol << std::endl
		<< "ai_protocol: " << ai->ai_next << std::endl;
		
	created_socket = BindingSocket_(ai);
	freeaddrinfo(ai);
	DoSocketListening_(created_socket);
	return (created_socket);
}

void SocketFdCreator::FillingInfoStruct_(SocketFdCreator::struct_addrinfo_reference hints, 
									SocketFdCreator::struct_addrinfo_pointer* ai,
									SocketFdCreator::const_server_type_reference socket_inform){
	std::memset(&hints, 0, sizeof(hints));
	//ai_family = AF_UNSPEC -> accept any address family supported by the operating system
	hints.ai_family = AF_UNSPEC;
	// ai_socktype = 0 -> every socket type
	hints.ai_socktype = 0;
	if (getaddrinfo(
			socket_inform.getHost().toCharArray().getData(), 
			socket_inform.getPort().toCharArray().getData(), 
			&hints, ai
		) != 0){
		throw except("CREATE_SOCKET_ERROR: Failed creating socket info struct", EXC_ARGS);
	}
}

int SocketFdCreator::BindingSocket_(SocketFdCreator::struct_addrinfo_pointer ai){
	struct_addrinfo_pointer	iterable;
	int						socket_fd, yes;

	yes = 1; // flag for setting setsockopt parameters
	for (iterable = ai;
			iterable != NULL;
			iterable = iterable->ai_next){
		socket_fd = socket(
			iterable->ai_family,
			iterable->ai_socktype,
			iterable->ai_protocol
		);
		if (socket_fd < 0) {
			continue;
		}
		if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0
			|| bind(socket_fd, iterable->ai_addr, iterable->ai_addrlen) < 0){
			close(socket_fd);
			continue;
		}
		break ;
	}
	if (iterable == NULL) {
		throw except("CREATE_SOCKET_ERROR: Failed binding: " + std::string(strerror(errno)), EXC_ARGS);
	}
	return socket_fd;
}

void SocketFdCreator::DoSocketListening_(int created_socket){
	if (listen(created_socket, 32) < 0){
		close(created_socket);
		throw except("CREATE_SOCKET_ERROR: Failed listening", EXC_ARGS);
	}
}

}
