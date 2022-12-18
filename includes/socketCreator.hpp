/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketCreator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:21:16 by msalena           #+#    #+#             */
/*   Updated: 2022/12/18 22:16:06 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils/coreException.hpp"

#include <iostream>
#include <unistd.h>
#include <netdb.h> // struct addrinfo
#include <cstring> // memset()
#include <sys/types.h> // getaddrinfo()
#include <sys/socket.h> // socket()

#define wsrv MAIN_NAMESPACE

namespace MAIN_NAMESPACE{

struct SocketInfomation{
	int 		ai_family;
	int 		ai_socktype;
	int 		ai_flags;
	const char* host;
	const char* port;
};

/*
	Class's constructor:
		1. Creats inform structure
		2. Opens socket_fd
		2. Sets settings for allow reuse of local adresses
		3. Bind socket_fd with needing id and port
		4. Free struct_addrinfo list
		5. Does created_socket listening
*/
class SocketCreator{
public:
	typedef struct addrinfo					struct_addrinfo;
	typedef MAIN_NAMESPACE::CoreException	except; 

	SocketCreator(const SocketInfomation &socket_inform);
	~SocketCreator(void);

	int getSocket(void) const;
	
private:
	int created_socket;

	void createInfoStructure_(struct_addrinfo& hints, struct_addrinfo* ai,
								const SocketInfomation& socket_inform);	
	int bindingSocket_(struct_addrinfo& hints, struct_addrinfo* ai,
								const SocketInfomation& socket_inform);	
	void listeningSocket_(void);
};

}