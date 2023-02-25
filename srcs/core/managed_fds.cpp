/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managed_fds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:23:44 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 21:47:26 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/core/managed_fds.hpp"

namespace CORE{

// OBJECT_REFERENCE_PAIR IMPLEMENTATION

ObjectReferencePair::ObjectReferencePair(void) : type(PARENT) { }

ObjectReferencePair::~ObjectReferencePair(void) { }

ObjectReferencePair::OBJECT_TYPE ObjectReferencePair::ObjectType(void) {
	return (type);
}



// SOCKET_REFERENCE_PAIR IMPLEMENTATION

SocketReferencePair::SocketReferencePair(SocketReferencePair::sockets_reference sockets_array,
									SocketReferencePair::sockets_iter socket_iter)
									: socket_pair(sockets_array, socket_iter),
									type(SOCKET) { }

SocketReferencePair::~SocketReferencePair(void) { }

SocketReferencePair::OBJECT_TYPE SocketReferencePair::ObjectType(void) {
	return (type);
}



// FD_REFERENCE_PAIR IMPLEMENTATION

FdReferencePair::FdReferencePair(FdReferencePair::fds_reference fds_array,
							FdReferencePair::fds_iter fd_iter)
							: fd_pair(fds_array, fd_iter),
							type(FD) { }

FdReferencePair::~FdReferencePair(void) { }

FdReferencePair::fd_bytes_container_reference FdReferencePair::GetRequestMessageReference(void) {
	return ((*(fd_pair.second)).GetRequestMessageReference());
}

void FdReferencePair::DeleteObj(void) {
	fds_reference	array_reference = fd_pair.first;
	fds_iter		fd_it = fd_pair.second;

	if (fd_it != array_reference.End()){
		array_reference.DeleteFd(fd_it);
		fd_pair.second = array_reference.End();
	}
}

FdReferencePair::fds_iter FdReferencePair::GetFdIter(void){
	return (fd_pair.second);
}

FdReferencePair::fds_iter FdReferencePair::GetFdsEnd(void){
	return (fd_pair.first.End());
}

FdReferencePair::OBJECT_TYPE FdReferencePair::ObjectType(void) {
	return (type);
}


// MANAGED_FDS INITIALIZATION

ManagedFds::ManagedFds(void) {
	FD_ZERO(&managed_fds);
}

ManagedFds::ManagedFds(const ManagedFds& another) {
	operator=(another);
}

ManagedFds::~ManagedFds(void) { }

ManagedFds& ManagedFds::operator=(const ManagedFds& another) {
	managed_fds = another.managed_fds;
	managed_sockets_array = another.managed_sockets_array;
	managed_fds_array = another.managed_fds_array;
	return *this;
}

void ManagedFds::AddFd(ManagedFds::fd_pair fd_pair_obj) {
	FD_SET(fd_pair_obj.first, &managed_fds);
	managed_fds_array.push_back(fd_pair_obj);
}

ManagedFds::fds_set_iter ManagedFds::DeleteFd(int fd) {
	FD_CLR(fd, &managed_fds);
	return (DeleteFdFromArray_(fd));
}

bool ManagedFds::IsFdInSet(int fd) {
	bool is_in_set;

	is_in_set = bool(FD_ISSET(fd, &managed_fds));
	return (is_in_set);
}

ManagedFds::fd_set_pointer ManagedFds::GetManagedFdsAddress(void) {
	return (&managed_fds);
}

ManagedFds::sockets_set_iter ManagedFds::BeginSocket(void) {
	return (managed_sockets_array.begin());
}

ManagedFds::sockets_set_iter ManagedFds::EndSocket(void) {
	return (managed_sockets_array.end());
}

ManagedFds::fds_set_iter ManagedFds::BeginFd(void) {
	return (managed_fds_array.begin());
}

ManagedFds::fds_set_iter ManagedFds::EndFd(void) {
	return (managed_fds_array.end());
}

ManagedFds::sockets_set_iter ManagedFds::FindSocketInArray(int fd) {
	for (sockets_set_iter it = managed_sockets_array.begin();
			it != managed_sockets_array.end();
			++it){
		if ((*it).first == fd) {
			return (it);
		}
	}
	return (managed_sockets_array.end());
}

ManagedFds::fds_set_iter ManagedFds::FindFdInArray(int fd) {
	for (fds_set_iter it = managed_fds_array.begin();
			it != managed_fds_array.end();
			++it){
		if ((*it).first == fd) {
			return (it);
		}
	}
	return (managed_fds_array.end());
}

ManagedFds::fds_iter ManagedFds::FindFdIterator(int fd) {
	for (fds_set_iter it = managed_fds_array.begin();
			it != managed_fds_array.end();
			++it){
		if ((*it).first == fd) {
			return ((*it).second.GetFdIter());
		}
	}
	return ((*managed_fds_array.begin()).second.GetFdIter());
}

ManagedFds::fds_set_iter ManagedFds::DeleteFdFromArray_(int fd) {
	fds_set_iter	findin_fd_iter;

	findin_fd_iter = FindFdInArray(fd);
	if (findin_fd_iter != managed_fds_array.end()){
		return (managed_fds_array.erase(findin_fd_iter));
	}
	throw except("DIDN_DELETE: Deleted fd not found", EXC_ARGS);
}

void ManagedFds::AddElemToArray_(int fd, ManagedFds::sockets_reference array_ref,
							ManagedFds::sockets_iter obj_it) {
	socket_pair	elem_pair(fd, socket_pair_class(array_ref, obj_it));

	managed_sockets_array.push_back(elem_pair);
}

void ManagedFds::AddElemToArray_(int fd, ManagedFds::fds_reference array_ref,
							ManagedFds::fds_iter obj_it) {
	fd_pair	elem_pair(fd, fd_pair_class(array_ref, obj_it));

	managed_fds_array.push_back(elem_pair);
}

}
