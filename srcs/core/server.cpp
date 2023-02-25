/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:02 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 21:53:20 by msalena          ###   ########.fr       */
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


void Server::ClientCommunication_(Server::managed_fds_reference masterread, 
								Server::managed_fds_reference masterwrite,
								int current_fd){	
	int readed_nbytes;
	char buf[wsrv::utils::BUFFER_SIZE];

	if ((readed_nbytes = recv(current_fd, buf, sizeof(buf), 0)) <= 0) {
		masterread.DeleteFd(current_fd);
		// client sent all and/or closed connection
		if (readed_nbytes == 0) {
			//masterwrite.AddFd(current_fd);
			for (std::vector<char*>::iterator ti = (*masterread.FindFdIterator(current_fd)).GetRequestMessageReference().bytesContainer.begin();
				ti != (*masterread.FindFdIterator(current_fd)).GetRequestMessageReference().bytesContainer.end();
				++ti){
				std::cout << (*ti) << std::endl;
			}
		} else {
			//(*it).second.DeleteObj();
			throw except("RECV_FAILD: invalid readed_count", EXC_ARGS);
		}
		
	} else {
		fds_iter it_current_fd = masterread.FindFdIterator(current_fd);
		
		(*it_current_fd).GetRequestMessageReference().pushBack(buf);
		//std::cout << buf << std::endl;
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
						ClientCommunication_(masterread, masterwrite, i);
					} catch(except& e) {
						continue;
					}
				} 
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