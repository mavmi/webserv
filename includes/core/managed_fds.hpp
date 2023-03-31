/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managed_fds.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:49 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 22:32:07 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <sys/select.h>
#include <algorithm>
#include <utility>

#include "../utils/utils.hpp"
#include "sockets.hpp"


namespace CORE{

/*
 * ObjectReferencePair class is parent class
 * for SocketReferencePair and FdReferencePair
 */
class ObjectReferencePair {
public:
	typedef CoreException	except;
	enum OBJECT_TYPE{
		PARENT,
		SOCKET,
		FD
	} ;

	ObjectReferencePair(void);
	~ObjectReferencePair(void);

	virtual OBJECT_TYPE	ObjectType(void);
private:
	OBJECT_TYPE type;
};

/* SocketReferencePair class keeps pair with the iterator to some socket
 * and the reference to sockets_array where exactly the above socket stays
 */
class SocketReferencePair : public ObjectReferencePair {
public:
	typedef SocketObj									socket_obj;
	typedef Sockets										sockets;
	typedef sockets&									sockets_reference;
	typedef sockets::sock_array_iter					sockets_iter;
	typedef std::pair<sockets, sockets_iter>			refer_iter_pair;

	SocketReferencePair(sockets_reference sockets_array, sockets_iter socket_iter);
	~SocketReferencePair(void);

	// Return:	enum type of object - SOCKET
	OBJECT_TYPE	ObjectType(void);
private:
	refer_iter_pair	socket_pair;
	OBJECT_TYPE		type;
};

/* FdReferencePair class keeps pair with the iterator to some fd
 * and the reference to fds_array where exactly the above fd stays
 */
class FdReferencePair : public ObjectReferencePair {
public:
	typedef FdObj								fd_obj;
	typedef fd_obj::bytes_container_reference	fd_bytes_container_reference;
	typedef Fds									fds;
	typedef fds&								fds_reference;
	typedef fds::fd_array_iter					fd_iter;
	typedef std::pair<fds_reference, fd_iter>	refer_iter_pair;
	typedef refer_iter_pair&					pair_reference;

	FdReferencePair(fds_reference fds_array, fd_iter fd_iter);
	~FdReferencePair(void);

	fd_bytes_container_reference GetRequestMessageReference(void);

	fd_iter GetFdIter(void);

	// After deleting fd_pair.second keeps iterator to the end() or fds_array
	void DeleteFd(void);

	pair_reference FdPairReference(void);

	// Return:	enum type of object - FD
	OBJECT_TYPE	ObjectType(void);
private:
	refer_iter_pair fd_pair;
	OBJECT_TYPE		type;
};

// Class which defines structure for classes with set of opening fds
class ManagedFds {
public:
	typedef fd_set									fd_set_type;
	typedef fd_set_type*							fd_set_pointer;
	typedef SocketReferencePair						socket_pair_class;
	typedef FdReferencePair							fd_pair_class;
	typedef socket_pair_class::sockets_reference	sockets_reference;
	typedef fd_pair_class::fds_reference			fds_reference;
	typedef socket_pair_class::sockets_iter			sockets_iter;
	typedef fd_pair_class::fd_iter					fd_iter;
	typedef std::pair<int, socket_pair_class>		socket_pair;
	typedef std::pair<int, fd_pair_class>			fd_pair;
	typedef std::vector<socket_pair>				sockets_set;
	typedef std::vector<fd_pair>					fds_set;
	typedef sockets_set::iterator					sockets_set_iter;
	typedef fds_set::iterator						fds_set_iter;
	typedef CoreException							except;

	ManagedFds(void);
	ManagedFds(const ManagedFds& another);
	~ManagedFds(void);

	ManagedFds& operator=(const ManagedFds& another);

	/*
	 * Adds fd to the fd_set and adds passed pair<int, fd_pair_class>
	 * to the fds_array
	 */
	void AddFd(fd_pair fd_pair_obj);

	/*
	 * Adds fd to fd_set and create new socket_elem or fd_elem dependig on
	 * type of the passed array_reference_type and the iter_type
	 */
	template <class array_reference_type, class iter_type>
		void AddFd(int fd, array_reference_type array_ref, iter_type obj_it) {
			FD_SET(fd, &managed_fds);
			AddElemToArray_(fd, array_ref, obj_it);
		}
	// Return:	iterator to the element after erased in fds set
	fds_set_iter DeleteFd(int fd);

	/*
	 * Return:
	 *	- 0: fd is not in set of opening fds
	 *	- 1: fd is in set of opening fds
	 */
	bool IsFdInSet(int fd);

	// Returns:	address of managed_fds fd_set
	fd_set_pointer GetManagedFdsAddress(void);

	/*
	 * Return:
	 *	- iterator to first socket in sockets set
	 *	- end() iterator if there is not sockets in set
	 */
	sockets_set_iter BeginSocket(void);

	// Returns:	iterator to the elemeny following the last socket
	sockets_set_iter EndSocket(void);

	/*
	 * Return:
	 *	- iterator to first fd in fds set
	 *	- end() iterator if there is not fds in set
	 */
	fds_set_iter BeginFd(void);

	// Return:	iterator to the elemeny following the last fd
	fds_set_iter EndFd(void);

	/*
	 * Return:
	 *	- iterator to finding socket in array
	 *	- end() iterator if socket isn't in set
	 */
	sockets_set_iter FindSocketInArray(int fd);

	/*
	 * Return:
	 *	- iterator to finding pair<fd, fd_pair_class> in array
	 *	- end() iterator if fd isn't in set
	 */
	fds_set_iter FindFdInArray(int fd);
protected:
	fd_set_type	managed_fds;
	sockets_set	managed_sockets_array;
	fds_set		managed_fds_array;

	// Creates and adds elem to sockets array
	void AddElemToArray_(int fd, sockets_reference array_ref,
					sockets_iter obj_it);

	// Creates and adds elem to fds array
	void AddElemToArray_(int fd, fds_reference array_ref, fd_iter obj_it);

	/*
	 * Deletes fd from fd_array
	 *
	 * Return:		iterator to the element sfter erased in fds set
	 * Exception:	throws custom exception if couldn't find the remoted fd
	 */
	fds_set_iter DeleteFdFromArray_(int fd);
} ;
}
