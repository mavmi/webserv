/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:22:02 by msalena           #+#    #+#             */
/*   Updated: 2023/02/23 22:30:58 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/core/server.hpp"
#include "../../includes/core/sockets.hpp"
#include "../../includes/core/utils/server_utils.hpp"


namespace CORE{

// FDS_OPENER IMPLEMENTATION

int FdsOpener::OpenFds(FdsOpener::sockets_reference sockets, int highest_fd,
					FdsOpener::managed_fds_sets_reference fds_sets){
	for(sock_iter it = sockets.Begin();
		it != sockets.End();
		++it){
		fds_iter new_fd_it;

		if(fds_sets.fdread.IsFdInSet((*it).GetSocketFd())){
			try {
				new_fd_it = CreateFd_((*it));
			} catch (except& e) {
				continue;
			}
			fds_sets.masterread.AddFd(
				(*new_fd_it).GetFd(),
				(*it).GetFdsSetReference(),
				new_fd_it
			);
			if ((*new_fd_it).GetFd() > highest_fd){
				highest_fd = (*new_fd_it).GetFd();
			}
		}
	}
	return (highest_fd);
}

FdsOpener::fds_iter FdsOpener::CreateFd_(FdsOpener::sock_obj_reference socket) {
	fd_obj tmp_fd;

	tmp_fd.SetFd(
		accept(
			socket.GetSocketFd(),
			(sockaddr_pointer)(tmp_fd.GetClientInformStruct()),
			tmp_fd.ClientInformStructLen()
		)
	);
	if (tmp_fd.GetFd() == -1){
		throw except("ACCEPR_FAILD: Fd wasn't created for client", EXC_ARGS);
	}
	fcntl(tmp_fd.GetFd(), F_SETFL, O_NONBLOCK); //do new_fd nonblocking the program
	return (socket.AddRelatedFd(tmp_fd));
}


// REQUESTS_READER IMPLEMENTATION

void RequestsReader::ReadRequests(RequestsReader::managed_fds_sets_reference fds_sets) {

	for (managed_fds_array_iter it = fds_sets.fdread.BeginFd();
			it != fds_sets.fdread.EndFd();
			++it){
		int tmp_fd = (*it).first;

		if (fds_sets.fdread.IsFdInSet(tmp_fd)) {
			char	buf[2048];
			ssize_t	readed_count = 0;

			readed_count = recv(tmp_fd, buf, sizeof(buf), 0);
			try {
				SafeRequestMessage_(tmp_fd, buf, it, fds_sets);
			} catch(except& e) {
				continue;
			}
		}
	}
}

void RequestsReader::SafeRequestMessage_(int readed_count, char* buf,
									RequestsReader::managed_fds_array_iter it,
									RequestsReader::managed_fds_sets_reference fds_sets) {
	if (readed_count > 0) {
		(*it).second.GetRequestMessageReference().pushBack(buf);
		//PRINT REQUEST
		/*
		for (std::vector<char*>::iterator ti = (*it).second.GetRequestMessageReference().bytesContainer.begin();
			ti != (*it).second.GetRequestMessageReference().bytesContainer.end();
			++ti){
			std::cout << (*ti) << std::endl;
		}
		*/
	} else if (readed_count == 0) {
		// in this place: i should send to pasring

		fds_sets.masterread.DeleteFd((*it).first);
		fds_sets.masterwrite.AddFd((*it));
	} else {
		close_delete_fd(it, fds_sets);
		throw except("RECV_FAILD: invalid readed_count", EXC_ARGS);
	}
}


// SERVER IMPLEMENTATION

void Server::FtServer(Server::sockets_refernce sockets) {
	managed_fds masterread, masterwrite, fdread, fdwrite;
	manageds_fds_sets fds_sets(masterread, masterwrite, fdread, fdwrite);
	int highest_fd;

	highest_fd = sockets_to_masterread(sockets, masterread);
	//Print all sockets
	/*
	for(Sockets::sock_array_iter it = sockets.Begin();
		it != sockets.End();
		++it){
		std::cout << (*it).GetSocketFd() << std::endl;
	}
	*/
	while(highest_fd){
		fdread = masterread;
		fdwrite = masterwrite;
		//Print sets
		/*
		for(ManagedFds::fds_set_iter it = masterwrite.BeginFd();
			it != fdwrite.EndFd();
			++it){
			std::cout << (*it).first << std::endl;
		}
		*/
		if(select(
			(highest_fd + 1),
			fdread.GetManagedFds(),
			fdwrite.GetManagedFds(),
			0, 0
		) == -1){
			continue;
		}
		highest_fd = opener.OpenFds(sockets, highest_fd, fds_sets);
		reader.ReadRequests(fds_sets);
		//sender.send_answer(sockets, fdwrite, masterwrite);
	}
}


void start_server(const wsrv::Configuration& configs) {
	Sockets	sockets(create_sockets(configs));
	Server	launch_server;

	launch_server.FtServer(sockets);
}


}
