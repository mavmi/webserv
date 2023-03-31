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


int Server::OpenFd_(Server::sockets_iter it_socket,
				Server::managed_fds_reference masterread,
				int highest_fd){
	fd_iter it_fd = CreateFd_(it_socket);

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

Server::fd_iter Server::CreateFd_(Server::sockets_iter it_socket) {
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

void Server::RecvRequest_(Server::managed_fds_reference masterread,
						Server::managed_fds_reference masterwrite,
						int current_fd){
	int nbytes;
	bool is_fd_in_set;
	char buf[wsrv::utils::BUFFER_SIZE];
	fds_set_iter it_set_curretn_fd;
	managed_fd_pair_class_reference fd_pair;

	it_set_curretn_fd = masterread.FindFdInArray(current_fd);
	fd_pair = (*it_set_curretn_fd).second;
	is_fd_in_set = fd_pair.GetFdIter() != fd_pair.FdPairReference().first.End();

	// if fd in opended fds for clients-connection
	if (is_fd_in_set){
		nbytes = recv(current_fd, buf, sizeof(buf), 0);
		// if recv worked correct
		if (nbytes >= 0) {
			nbytes = MessageFormationToReceiveSend_(fd_pair.GetFdIter(), buf, nbytes);
			if (!nbytes) {
				masterwrite.AddFd((*it_set_curretn_fd));
				masterread.DeleteFd(current_fd);
			}
			return ;
		}
	}
	if (!is_fd_in_set || nbytes < 0) {
		masterread.DeleteFd(current_fd);
		fd_pair.DeleteFd();
		recv_throw();
	}
}

int Server::MessageFormationToReceiveSend_(Server::fd_iter it_current_fd,
										char* buf, int nbytes){
	int is_req_end;
	fd_bytes_container_reference request_container;

	request_container = (*it_current_fd).GetRequestMessageReference();
	is_req_end = request_container.pushBack(buf, nbytes);
	if (!is_req_end){
		response_generator();
	}
	return is_req_end;
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
