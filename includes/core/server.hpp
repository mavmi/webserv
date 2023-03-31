/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:43 by msalena           #+#    #+#             */
/*   Updated: 2023/02/26 12:47:53 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <fcntl.h>
#include <unistd.h>

#include "sockets.hpp"
#include "managed_fds.hpp"
#include "utils/core_exception.hpp"
#include "../utils/utils.hpp"


namespace CORE{


class Server {
public:
	typedef Sockets								sockets;
	typedef sockets&							sockets_refernce;
	typedef Sockets::sock_array_iter			sockets_iter;
	typedef struct sockaddr*					sockaddr_pointer;
	typedef FdObj								fd_obj;
	typedef fd_obj::bytes_container_reference	fd_bytes_container_reference;
	typedef Fds::fd_array_iter					fd_iter;
	typedef ManagedFds							managed_fds;
	typedef ManagedFds&							managed_fds_reference;
	typedef managed_fds::fd_pair_class&			managed_fd_pair_class_reference;
	typedef managed_fds::fds_set_iter			fds_set_iter;
	typedef CoreException						except;

	/*
	* Realization of server which works using 'select'.
	*
	* It's listening opened sockets, creating new fds for every connect,
	* reading the request and sending answers to the clinet
	*/
	void FtServer(sockets_refernce sockets);
private:
	/*
	* Opens fd for clients request
	*
	* Return:		new number of largest fd number
	* Exception:	throws custom exception if couldn't open fd
	*/
	int OpenFd_(sockets_iter it_socket, managed_fds_reference masterread,
				int highest_fd);

	/*
	 * Returns:		iterator to created fd
	 * Exception:	throws custom exception if 'accept' function retuns error
	 */
	fd_iter CreateFd_(sockets_iter it_socket);

	void RecvRequest_(managed_fds_reference masterread,
							managed_fds_reference masterwrite,
							int current_fd);

	void SendResponse_(managed_fds_reference masterwrite, int current_fd);

	int MessageFormationToReceiveSend_(fd_iter it_current_fd, char* buf,
									int readed_nbytes);
} ;


void start_server(const wsrv::Configuration& configurations);

}
