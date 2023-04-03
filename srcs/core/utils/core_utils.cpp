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

std::string getErrorFile(const std::string& statusCode,
	const wsrv::configuration::ServerConfiguration::ErrorPagesContainerType& errorFiles){

	const std::string invalid = "invalid";

	for (size_t i = 0; i < errorFiles.size(); i++){
		const std::string& filePath = errorFiles.at(i);
		size_t slashPos = filePath.rfind('/');
		std::string fileName = (slashPos == std::string::npos) ?
			filePath :
			filePath.substr(slashPos + 1, filePath.size() - slashPos - 1);
		size_t dotPos = fileName.rfind('.');

		if (dotPos != std::string::npos){
			fileName = fileName.substr(0, dotPos);
		}
		if (fileName == statusCode){
			return filePath;
		}
	}
	return invalid;
}

void invalid_request(wsrv::Fds::fd_array_iter it_current_fd, HttpResponse& response,
				utils::Exception& e){
	utils::HTTP_VERSION	version;
	size_t s = e.what().rfind(':') + 1;
	std::string substr = e.what().substr(s, e.what().size() - s);
	
	version = utils::httpVersionFromString(substr);
	if (e.what() == "Invalid method") {
		response.setupFile(
			"invalid", 
			getErrorFile(
				"501", 
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
		response.setStatusLine(version, "501", "Not Implemented");
	} else {
		response.setupFile(
			"invalid", 
			getErrorFile(
				"400", 
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
		response.setStatusLine(version, "400", "Bad Request");
	}
	(*it_current_fd).GetResponseMessageReference() = response.toBytes();
}

void execute_method(wsrv::Fds::fd_array_iter it_current_fd, HttpResponse& response,
				http_request::HttpRequestParser& request){
	bool is_file;
	utils::METHOD method;
	utils::HTTP_VERSION	version;

	method = request.getHttpRequest().getStatusLine().getMethod();
	version = request.getHttpRequest().getStatusLine().getHttpVersion();
	if (method == utils::GET){
		//GET METHOD TO ANOTHER FUNCTION
		is_file = response.setupFile(
			request.getHttpRequest().getStatusLine().getUrl(),
			getErrorFile(
				"404",
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
		if (is_file) {
			response.setStatusLine(version, "200", "OK");
		} else {
			response.setStatusLine(version, "404", "Not Found");
		}
	} else if (method == utils::POST) {

	} else {

	}
	(*it_current_fd).GetResponseMessageReference() = response.toBytes();
}

void response_generator(wsrv::Fds::fd_array_iter it_current_fd){
	HttpResponse	response;

	try {
		response.setDate();
		response.setRetryAfter();
	} catch (utils::Exception&) { }
	http_request::HttpRequestParser request;
	try {
		request.parseHttpRequest((*it_current_fd).GetRequestMessageReference());
	} catch (utils::Exception& e) {
		invalid_request(it_current_fd, response, e);
	//
	char* aaa;

	aaa = it_current_fd->GetResponseMessageReference().toBytes();
	// std::cout << aaa << std::endl;
	free(aaa);
	//
		return ;
	}
	execute_method(it_current_fd, response, request);
}

void server_throws(int is_fd_in_set, std::string invalid_fd_msg,
				std::string invalid_fnc_msg){
	if (!is_fd_in_set) {
		throw CoreException(invalid_fd_msg, EXC_ARGS);
	} else {
		throw CoreException(invalid_fnc_msg, EXC_ARGS);
	}
}

}
