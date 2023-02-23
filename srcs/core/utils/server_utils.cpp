/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:23:53 by msalena           #+#    #+#             */
/*   Updated: 2023/02/23 18:27:00 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/core/utils/server_utils.hpp"


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

void close_delete_fd(RequestsReader::managed_fds_array_iter it,
				RequestsReader::managed_fds_sets_reference fds_sets) {
	(*it).second.DeleteObj();
	fds_sets.masterread.DeleteFd((*it).first);
	fds_sets.fdread.DeleteFd((*it).first);
}

}
