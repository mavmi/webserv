/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:57 by msalena           #+#    #+#             */
/*   Updated: 2023/04/02 18:42:11 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <vector>
#include <list>

#include "socket_creator.hpp"
#include "utils/core_exception.hpp"
#include "../utils/utils.hpp"


/*
 *	//// Structure of sockets' information implementation \\\\
 *
 *
 * class Sockets (all managed sockets)
 * 	|
 * 	|___ vector < class SocketObj (all about socket) >
 * 					|
 * 					|___ class Fds (set of fds which are binded with socket)
 * 							|
 * 							|___ list < class FdObj (all about fd) >
 */


namespace CORE{

class SocketFdCreator;
class FdObj;
class Fds;
class SocketObj;
class Sockets;


// Manager of fd object
class FdObj {
public:
	typedef utils::BytesContainer				bytes_container;
	typedef bytes_container&					bytes_container_reference;
	typedef struct sockaddr_storage				clientaddr_inform;
	typedef clientaddr_inform*					clientaddr_inform_pointer;
	typedef socklen_t							clientaddr_struct_len;
	typedef clientaddr_struct_len*				clientaddr_struct_len_pointer;
	typedef SocketObj							parent_socket;
	typedef parent_socket*						parent_socket_pointer;
	typedef const Configuration::ServerType&	const_parent_socket_config_reference;

	FdObj(parent_socket_pointer parent);
	FdObj(const FdObj& another);
	FdObj(int fd, parent_socket_pointer parent);
	~FdObj(void);

	FdObj& operator=(const FdObj& another);

	// Return:	copy of fd's number
	int GetFd(void) const;

	void SetFd(int fd);

	// Return:	pointer to client_information structure
	clientaddr_inform_pointer GetClientInformStruct(void);

	// Return:	pointer to socklen_t variable with sizeof(client_information)
	clientaddr_struct_len_pointer ClientInformStructLen(void);

	// Return:	reference to the Request BytesContainer class
	bytes_container_reference GetRequestMessageReference(void);

	// Return:	reference to the Response BytesContainer class
	bytes_container_reference GetResponseMessageReference(void);

	// Return:	const reference to the Config class of socket-parent
	const_parent_socket_config_reference GetParentSocketConfigReference(void);
private:
	int						fd;
	parent_socket_pointer	parent;
	clientaddr_inform		client_information;
	clientaddr_struct_len	client_inform_len;
	bytes_container			request_message;
	bytes_container			response_message;
	// HTTP send
};


// Manager of set with fds
class Fds {
public:
	typedef FdObj					fd_type;
	typedef FdObj&					fd_type_reference;
	typedef std::list<fd_type>		fd_array;
	typedef fd_array&				fd_array_reference;
	typedef fd_array::iterator		fd_array_iter;
	typedef CoreException			except;

	Fds(void);
	Fds(const Fds& another);
	~Fds(void);
	/*
	 * Returns:
	 *	- iterator to first fd in set
	 *	- end() iterator if there is not fd in set
	 */
	fd_array_iter Begin(void);

	// Returns:	iterator to the element following the last fd
	fd_array_iter End(void);

	/*
	 * Return:		copy of fd object
	 * Exception:	throws custom exception if there is not fd in sockets
	 */
	fd_type GetFd(int fd);

	// Return:	reference to fds_array
	fd_array_reference GetFdsReference(void);

	// Return:	iterator to the inserted fd
	//fd_array_iter AddFd(int fd);

	// Return:	iterator to the inserted fd
	fd_array_iter AddFd(fd_type_reference fd);

	void DeleteFd(fd_array_iter fd);

	void DeleteFd(int fd);
private:
	fd_array	fds;

	/*
	 * Return:
	 *	- iterator to finding fd
	 *	- end() iterator if there is notfd in list of fds
	 */
	fd_array_iter GetFdIter_(int fd);
};


// Manager of socket object
class SocketObj {
public:
	typedef FdObj										fd_obj;
	typedef wsrv::Configuration::ServerType				server_type;
	typedef server_type&								server_type_reference;
	typedef const server_type&							const_server_type_reference;
	typedef server_type const *							server_type_pointer;
	typedef Fds											fds_set;
	typedef Fds&										fds_set_reference;
	typedef fds_set::fd_array_reference					fds_array_reference;
	typedef Fds::fd_array_iter							fds_set_iter;
	typedef CoreException								except;

	SocketObj(server_type_pointer server_info);
	SocketObj(const SocketObj& another);
	~SocketObj(void);

	SocketObj& operator=(const SocketObj& another);

	// Return:	copy of socket's fd number
	int GetSocketFd(void) const;

	// Return:	reference to fds_array
	fds_set_reference GetFdsSetReference(void);

	/*
	 * Return:		copy of binding fd object
	 * Exception:	throws custom exception if there is not fd in sockets
	 */
	fd_obj GetBindingFd(int fd);

	// Return:	reference to object with information about socket's server
	const_server_type_reference GetServerInfo(void);

	// Return:	iterator to the realed fd
	template < class fd_type >
		fds_set_iter AddRelatedFd(fd_type& fd){
			return (related_fds.AddFd(fd));
		}
private:
	int							socket_fd;
	fds_set						related_fds;
	server_type_pointer			server_info;
};


// Manager of sockets
class Sockets {
public:
	typedef FdObj					fd_obj;
	typedef SocketObj				sock_obj;
	typedef std::vector<sock_obj>	sock_array;
	typedef sock_array&				sock_array_reference;
	typedef sock_array::iterator	sock_array_iter;
	typedef CoreException			except;

	Sockets(void);
	Sockets(const Sockets& another);
	~Sockets(void);

	/*
	 * Returns:
	 *	- iterator to first socket in set
	 *	- end() iterator if there is not sockets in set
	 */
	sock_array_iter Begin(void);


	// Returns:	iterator to the element following the last socket
	sock_array_iter End(void);

	// Return:	reference to sockets_array
	sock_array_reference GetSocketsReference(void);

	/*
	 * Return:		copy of socket object
	 * Exception:	throws custom exception if there is not socket_fd in listening sockets
	 */
	sock_array_iter FindSocketInArray(int socket_fd);


	void AddSocket(sock_obj added_socket);

	template < class fd_type >
		// Exception:	throws custom exception if there is not socket_fd in listening sockets
		void BindFdWithSocket(int socket_fd, fd_type new_fd) {
			sock_array_iter	it;

			it = IsSocketInSet_(socket_fd);
			(*it).AddRelatedFd(new_fd);
		}

	// Exception:	throws custom exception if there is not socket_fd in listening sockets
	void BindFdWithSocket(sock_obj socket, fd_obj new_fd);
private:
	sock_array	sockets;

	/*
	 * Returns:
	 *	- iterator to finding socket
	 *	- end() iterator if there is not socket_fd in listening sockets
	 */
	sock_array_iter GetSocketIter_(int socket_fd);

	/*
	 * Returns:		iterator to finding socket
	 * Exception:	throws custom exception if there is not socket_fd in listening sockets
	 */
	sock_array_iter IsSocketInSet_(int socket_fd);
};

}
