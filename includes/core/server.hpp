/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:43 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 22:09:06 by msalena          ###   ########.fr       */
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

/*
 * WorkWithFds class is the Parent for FdsOpener,
 * RequestsReader and AnswersSender classes
 */
class WorkWithFds {
public:
	typedef Sockets							sockets;
	typedef sockets&						sockets_reference;
	typedef sockets::sock_array_iter		sock_iter;
	typedef sockets::sock_obj				sock_obj;
	typedef sock_obj&						sock_obj_reference;
	typedef FdObj							fd_obj;
	typedef Fds								fds;
	typedef Fds::fd_array_iter				fds_iter;
	typedef ManagedFds						managed_fds;
	typedef managed_fds&					managed_fds_reference;
	typedef managed_fds::fds_set_iter		managed_fds_array_iter;
	typedef struct sockaddr*				sockaddr_pointer;
	typedef CoreException					except;
} ;

// AnswersSender class is describing sending answers to the clients
class AnswersSender : public WorkWithFds{
public:

	/*
	* Sends answering messages to clients
	*
	* Return:	size of readed bytes
	*/
	//int send_answer(Socket& sockets, ManagedFds& fdwrite,
	//					ManagedFds& masterwrite);
private:
} ;


class Server {
public:
	typedef Sockets						sockets;
	typedef sockets&					sockets_refernce;
	typedef Sockets::sock_array_iter	sockets_iter;
	typedef struct sockaddr*			sockaddr_pointer;
	typedef FdObj						fd_obj;
	typedef Fds::fd_array_iter			fds_iter;
	typedef ManagedFds					managed_fds;
	typedef ManagedFds&					managed_fds_reference;
	typedef managed_fds::fds_set_iter	fds_set_iter;
	typedef CoreException				except;

	/*
	* Realization of server which works using 'select'.
	*
	* It's listening opened sockets, creating new fds for every connect,
	* reading the request and sending answers to the clinet
	*/
	void FtServer(sockets_refernce sockets);
private:
	//AnswersSender	sender;

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
	fds_iter CreateFd_(sockets_iter it_socket);
	
	void RecvRequest_(managed_fds_reference masterread, 
							managed_fds_reference masterwrite,
							int current_fd);
} ;


void start_server(const wsrv::Configuration& configurations);

}
