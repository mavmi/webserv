/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:02 by msalena           #+#    #+#             */
/*   Updated: 2023/02/26 16:48:22 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/core/server.hpp"
#include "../../includes/core/sockets.hpp"
#include "../../includes/core/utils/core_utils.hpp"


namespace CORE{

// FDS_OPENER IMPLEMENTATION


int Server::OpenFd_(Server::sockets_iter it_socket, Server::managed_fds_reference masterread,
					int highest_fd){
	fds_iter it_fd = CreateFd_(it_socket);

	masterread.AddFd(
		(*it_fd).GetFd(),
		(*it_socket).GetFdsSetReference(),
		it_fd
	);
	if ((*it_fd).GetFd() > highest_fd) {
		highest_fd = (*it_fd).GetFd();
	}
	return (highest_fd);
}

Server::fds_iter Server::CreateFd_(Server::sockets_iter it_socket) {
	fd_obj tmp_fd;

	tmp_fd.SetFd(
		accept(
			(*it_socket).GetSocketFd(),
			(sockaddr_pointer)(tmp_fd.GetClientInformStruct()),
			tmp_fd.ClientInformStructLen()
		)
	);
	if (tmp_fd.GetFd() == -1){
		throw except("ACCEPR_FAILD: Fd wasn't created for client", EXC_ARGS);
	}
	fcntl(tmp_fd.GetFd(), F_SETFL, O_NONBLOCK); //do new_fd nonblocking the program
	return ((*it_socket).AddRelatedFd(tmp_fd));
}

int Server::RecvReceving_(Server::managed_fd_pair_class_reference fd_pair){
	int push_result;

	push_result = fd_pair.GetRequestMessageReference().pushBack(buf, readed_nbytes);
	if (push_result == 0){
		response_generator(fd_pair)
	}
	return push_result;
}

void Server::RecvRequest_(Server::managed_fds_reference masterread,
						Server::managed_fds_reference masterwrite,
						int current_fd){
	int readed_nbytes;
	char buf[wsrv::utils::BUFFER_SIZE];
	fds_set_iter it_current_fd;

	it_current_fd = masterread.FindFdInArray(current_fd);
	// if fd in opended fds for clients-connection
	if ((*it_current_fd).second.GetFdIter() != (*it_current_fd).second.FdPairReference().first.End()){
		readed_nbytes = recv(current_fd, buf, sizeof(buf), 0);
		if (readed_nbytes > 0) {
			(*it_current_fd).second.GetRequestMessageReference().pushBack(buf, readed_nbytes);
		} else {
			if (readed_nbytes == 0){
				masterwrite.AddFd((*it_current_fd));
				for (std::vector<std::string>::const_iterator ti = (*it_current_fd).second.GetRequestMessageReference().getLines().begin();
					ti != (*it_current_fd).second.GetRequestMessageReference().getLines().end();
					++ti){
					std::cout << (*ti) << std::endl;
				}
			} else {
				(*it_current_fd).second.DeleteFd();
			}
			masterread.DeleteFd(current_fd);
		}
	} else {
		masterread.DeleteFd(current_fd);
		(*it_current_fd).second.DeleteFd();
		throw except("RECV_FAILD: current_fd not in array fds of client-connection", EXC_ARGS);
	}
}


// SERVER IMPLEMENTATION

void Server::FtServer(Server::sockets_refernce sockets) {
	managed_fds masterread, masterwrite, fdread, fdwrite;
	int highest_fd;

	highest_fd = sockets_to_masterread(sockets, masterread);
	while (highest_fd) {
		fdread = masterread;
		fdwrite = masterwrite;
		if(select(
			(highest_fd + 1),
			fdread.GetManagedFdsAddress(),
			fdwrite.GetManagedFdsAddress(),
			NULL, NULL
		) == -1){
			continue;
		}
		for(int i = 0; i <= highest_fd; i++) {
			if (fdread.IsFdInSet(i)) {
				sockets_iter it_socket = sockets.FindSocketInArray(i);
				if (it_socket != sockets.End()) { // If it's socket's fd
					try {
						highest_fd = OpenFd_(it_socket, masterread, highest_fd);
					} catch(except& e) {
						continue;
					}
				} else { // If it's opened fd for client-connection
					try {
						RecvRequest_(masterread, masterwrite, i);
					} catch(except& e) {
						continue;
					}
				}
			} else if (fdwrite.IsFdInSet(i)) {

			}
		}
	}
}


void start_server(const wsrv::Configuration& configs) {
	Sockets	sockets;
	Server	launch_server;

	create_sockets(configs, sockets);
	launch_server.FtServer(sockets);
}


}
