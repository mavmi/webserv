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
		response.setStatusLine(version, "501", "Not Implemented");
		response.setupFile(
			"invalid", 
			getErrorFile(
				"501", 
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
	} else {
		response.setStatusLine(version, "400", "Bad Request");
		response.setupFile(
			"invalid", 
			getErrorFile(
				"400", 
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
	}
	(*it_current_fd).GetResponseMessageReference() = response.toBytes();
}

void execute_method(wsrv::Fds::fd_array_iter it_current_fd, HttpResponse& response,
				const http_request::HttpRequest& request){
	bool is_file;
	utils::METHOD method;
	utils::HTTP_VERSION	version;

	method = request.getStatusLine().getMethod();
	version = request.getStatusLine().getHttpVersion();
	if (method == utils::GET){
		//GET METHOD TO ANOTHER FUNCTION
		response.setStatusLine(version, "200", "OK");
		is_file = response.setupFile(
			request.getStatusLine().getUrl(),
			getErrorFile(
				"404",
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
		if (!is_file) {
			response.setStatusLine(version, "404", "Not Found");
		}
	} else if (method == utils::POST) {

	} else {

	}
	(*it_current_fd).GetResponseMessageReference() = response.toBytes();
}

bool is_method_allowed(wsrv::Fds::fd_array_iter it_current_fd, 
					const http_request::HttpRequest& request,
					HttpResponse& response){
	bool is_allowed;
	utils::HTTP_VERSION	version;

	version = request.getStatusLine().getHttpVersion();

	try {
		is_allowed = (*it_current_fd).GetParentSocketConfigReference().getRoute(
				request.getStatusLine().getUrl()	
			).isMethodPresent(request.getStatusLine().getMethod());
	} catch (utils::Exception& e) {
		response.setupFile(
			"invalid", 
			getErrorFile(
				"404", 
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
		response.setStatusLine(version, "404", "Not Found");
		(*it_current_fd).GetResponseMessageReference() = response.toBytes();
		return false;
	}
	if (!is_allowed){
		response.setupFile(
			"invalid", 
			getErrorFile(
				"405", 
				(*it_current_fd).GetParentSocketConfigReference().getErrorPages()
			)
		);
		response.setStatusLine(version, "405", "Method Not Allowed");
		(*it_current_fd).GetResponseMessageReference() = response.toBytes();
		return false;
	}
	return true;
}

void response_generator(wsrv::Fds::fd_array_iter it_current_fd){	
	HttpResponse	response;

	try {
		// {
		// 	response.getStatusLine().setHttpVersion(utils::HTTP_1_0);
		// 	response.getStatusLine().setStatusCode("123");
		// 	response.getStatusLine().setMessage("msg");
		// }
		response.setDate();
		response.setRetryAfter();
	} catch (utils::Exception&) { }

	// {
	// 	std::cout << "\t// Response test output //" << std::endl;
	// 	std::cout << response.toBytes().toBytes();
	// }

	http_request::HttpRequestParser request;
	try {
		request.parseHttpRequest((*it_current_fd).GetRequestMessageReference());
	} catch (utils::Exception& e) {
		invalid_request(it_current_fd, response, e);
		return ;
	}
	if (!is_method_allowed(it_current_fd, request.getHttpRequest(), response)){
		return ;
	}
	execute_method(it_current_fd, response, request.getHttpRequest());
		{
			const std::vector<std::string>& v = it_current_fd->GetResponseMessageReference().getLines();
			for (size_t i = 0; i < v.size(); i++){
				std::cout << v[i] << std::endl;
			}
		}
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
