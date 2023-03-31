/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:23:34 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 21:43:30 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/core/sockets.hpp"

namespace CORE{

//FD_OBJ IMPLEMENTATION

FdObj::FdObj(void) : fd(-1) {
	client_inform_len = sizeof(client_information);
}

FdObj::FdObj(int fd) : fd(fd) {
	client_inform_len = sizeof(client_information);
}

FdObj::FdObj(const FdObj& another) {
	operator=(another);
}

FdObj::~FdObj(void) { }

FdObj& FdObj::operator=(const FdObj& another) {
	fd = another.fd;
	client_information = another.client_information;
	client_inform_len = sizeof(client_information);
	request_message = another.request_message;
	return (*this);
}

int FdObj::GetFd(void) const {
	return (fd);
}

void FdObj::SetFd(int fd) {
	this->fd = fd;
}

FdObj::clientaddr_inform_pointer FdObj::GetClientInformStruct(void) {
	return (&client_information);
}

FdObj::clientaddr_struct_len_pointer FdObj::ClientInformStructLen(void) {
	return (&client_inform_len);
}

FdObj::bytes_container_reference FdObj::GetRequestMessageReference(void) {
	return (request_message);
}

FdObj::bytes_container_reference FdObj::GetResponseMessageReference(void){
	return (response_message);
}

//FDS IMPLEMENTATION

Fds::Fds(void) { }

Fds::Fds(const Fds& another) : fds(another.fds) { }

Fds::~Fds(void) { }

Fds::fd_array_iter Fds::Begin(void) {
	return (fds.begin());
}

Fds::fd_array_iter Fds::End(void) {
	return (fds.end());
}

Fds::fd_type Fds::GetFd(int fd){
	fd_array_iter	it;

	it = GetFdIter_(fd);
	if (it == fds.end()){
		throw except("SOCKET_NOT_FOUND: Couldn't return passed fd", EXC_ARGS);
	}
	return (*it);
}

Fds::fd_array_reference Fds::GetFdsReference(void) {
	return (fds);
}

Fds::fd_array_iter Fds::AddFd(int fd) {
	fd_type a(fd);
	return (fds.insert(fds.end(), a));
}

Fds::fd_array_iter Fds::AddFd(Fds::fd_type_reference fd) {
	return (fds.insert(fds.end(), fd));
}

void Fds::DeleteFd(int fd) {
	fd_array_iter	it;

	it = GetFdIter_(fd);
	DeleteFd(it);
}

void Fds::DeleteFd(Fds::fd_array_iter fd_it) {
	if (fd_it != fds.end()){
		close((*fd_it).GetFd());
		fds.erase(fd_it);
	}
}

Fds::fd_array_iter Fds::GetFdIter_(int fd){
	fd_array_iter	end;

	end = fds.end();
	for (fd_array_iter it = fds.begin();
			it != end; it++) {
		if ((*it).GetFd() == fd){
			return (it);
		}
	}
	return (end);
}



//SOCKET_OBJ IMPLEMENTATION

SocketObj::SocketObj(SocketObj::server_type_pointer server_info)
	: socket_fd(-1), server_info(server_info) {
		SocketFdCreator socker_creator;

		this->socket_fd = socker_creator.CreateSocketFd(*server_info);
}

SocketObj::SocketObj(const SocketObj& another)
	: socket_fd(another.socket_fd), related_fds(another.related_fds),
		server_info(another.server_info) { }

SocketObj::~SocketObj(void) { }

SocketObj& SocketObj::operator=(const SocketObj& another) {
	server_info = another.server_info;
	return *this;
}

int SocketObj::GetSocketFd(void) const {
	return socket_fd;
}

SocketObj::fds_set_reference SocketObj::GetFdsSetReference(void) {
	return (related_fds);
}

 SocketObj::fd_obj SocketObj::GetBindingFd(int fd) {
	return (related_fds.GetFd(fd));
}

SocketObj::const_server_type_reference SocketObj::GetServerInfo(void) {
	return *server_info;
}



// SOCKETS IMPLEMENTATION

Sockets::Sockets(void) { }

Sockets::Sockets(const Sockets& another) : sockets(another.sockets) { }

Sockets::~Sockets(void) { }

Sockets::sock_array_iter Sockets::Begin(void) {
	return sockets.begin();
}

Sockets::sock_array_iter Sockets::End(void) {
	return sockets.end();
}

Sockets::sock_array_reference Sockets::GetSocketsReference(void) {
	return (sockets);
}

Sockets::sock_array_iter Sockets::FindSocketInArray(int socket_fd) {
	return (GetSocketIter_(socket_fd));
}


void Sockets::AddSocket(Sockets::sock_obj added_socket) {
	sockets.push_back(added_socket);
}

void Sockets:: BindFdWithSocket(Sockets::sock_obj socket, Sockets::fd_obj new_fd) {
	BindFdWithSocket(socket.GetSocketFd(), new_fd);
}

Sockets::sock_array_iter Sockets::IsSocketInSet_(int socket_fd) {
	sock_array_iter	it;

	it = GetSocketIter_(socket_fd);
	if (it == sockets.end()){
		throw except("SOCKET_NOT_FOUND: Couldn't bind fd with unfound socket", EXC_ARGS);
	}
	return (it);
}

Sockets::sock_array_iter Sockets::GetSocketIter_(int socket_fd) {
	sock_array_iter	end;

	end = sockets.end();
	for(sock_array_iter it = sockets.begin(); it != end; ++it){
		if ((*it).GetSocketFd() == socket_fd){
			return it;
		}
	}
	return (end);
}

}
