/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_creator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:27 by msalena           #+#    #+#             */
/*   Updated: 2023/01/28 14:44:57 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h> // struct addrinfo
#include <cstring> // memset()
#include <sys/types.h> // getaddrinfo()
#include <sys/socket.h> // socket()

#include "utils/core_exception.hpp"
#include "../configurations/configuration.hpp"
#include "sockets.hpp"
#include "../utils/utils.hpp"

namespace CORE{

class SocketObj;

// Creator of listening socket
class SocketFdCreator{
public:
	typedef struct addrinfo								struct_addrinfo;
	typedef struct_addrinfo*							struct_addrinfo_pointer;
	typedef struct_addrinfo&							struct_addrinfo_reference;
	typedef wsrv::Configuration::ServerType	server_type;
	typedef server_type&								server_type_reference;
	typedef const server_type&							const_server_type_reference;
	typedef CoreException								except;

	/*
	 * 1. Creats inform structure
	 * 2. Opens socket_fd
	 * 2. Sets settings for allow reuse of local adresses
	 * 3. Binds socket_fd with needing id and port
	 * 4. Frees struct_addrinfo list
	 * 5. Does created_socket listening
	 *
	 * Return:		created fd socket
	 * Exception:	throws custom exceptions from calling private methods
	 */
	int CreateSocketFd(const_server_type_reference socket_inform);

private:
	// Exception:	throws custom exception if addrinfo structure wasn't created
	void FillingInfoStruct_(struct_addrinfo_reference hints, struct_addrinfo_pointer* ai,
						const_server_type_reference socket_inform);

	/*
	 * Return:		binded socket
	 * Exception:	throws custom exception if socket wasn't binded
	 */
	int BindingSocket_(struct_addrinfo_pointer ai);

	// Exception:	throws custom exception if socket didn't listen
	void DoSocketListening_(int socket_fd);
};

}
