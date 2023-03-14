/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:23:53 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 21:42:00 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/core/utils/core_utils.hpp"


namespace CORE{

int sockets_to_masterread(Sockets& sockets, ManagedFds& masterread){
	int highest_fd;

	highest_fd = 0;
	for(Sockets::sock_array_iter it = sockets.Begin();
		it != sockets.End();
		++it){
		int tmp_fd;

		tmp_fd = (*it).GetSocketFd();
		masterread.AddFd(tmp_fd, sockets, it);
		if (highest_fd < tmp_fd){
			highest_fd = tmp_fd;
		}
	}
	return (highest_fd);
}

void create_sockets(const wsrv::Configuration& servers, Sockets& sockets_array) {
	typedef SocketObj								socket_obj;
	typedef wsrv::Configuration						configuration;
	typedef configuration::ServersContainerType		servers_container;
	typedef servers_container::SizeType				servers_size;
	typedef const servers_container&				const_servers_container_reference;

	const_servers_container_reference	servers_array = servers.getServers();

	for (servers_size counter = 0, last_num = servers.getServersCount();
			counter < last_num;
			++counter
		) {
		socket_obj new_socket(&(servers_array.at(counter)));

		sockets_array.AddSocket(new_socket);
	}
}

void response_generator(FdReferencePair& current_fd_pair){
	http_request::HttpRequest request(current_fd_pair.GetRequestMessageReference());
	http_responce::HttpResponse	response;

	response.setData();
	//difference implementation because of GET/POST/DELETE
}

}
