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

std::string get_error_file(const std::string& statusCode,
	const wsrv::configuration::ServerConfiguration& serverConf){

	const std::string invalid = "invalid";
	const wsrv::configuration::ServerConfiguration::ErrorPagesContainerType& errorFiles = serverConf.getErrorPages();

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
			try {
				return serverConf.getRoot() + filePath;
			} catch (wsrv::utils::Exception&){
				return invalid;
			}
		}
	}
	return invalid;
}

std::string get_file(const std::string& path,
	const wsrv::configuration::ServerConfiguration& serverConf){
	try {
		return serverConf.getRoot() + path;
	} catch (wsrv::utils::Exception&){
		return "invalid";
	}
}

void error_setup_file(wsrv::Fds::fd_array_iter it_current_fd,
				HttpResponse& response, const std::string& status_sode){
	response.setupFile(
		"invalid",
		get_error_file(
			status_sode,
			(*it_current_fd).GetParentSocketConfigReference()
		)
	);
}

void invalid_request(wsrv::Fds::fd_array_iter it_current_fd, HttpResponse& response,
				utils::Exception& e){
	utils::HTTP_VERSION	version;
	size_t s = e.what().rfind(':') + 1;
	std::string substr = e.what().substr(s, e.what().size() - s);

	version = utils::httpVersionFromString(substr);
	if (e.what().find("Invalid method") != std::string::npos) {
		response.setStatusLine(version, "501", "Not Implemented");
		error_setup_file(it_current_fd, response, "501");
	} else {
		response.setStatusLine(version, "400", "Bad Request");
		error_setup_file(it_current_fd, response, "400");
	}
	(*it_current_fd).GetResponseMessageReference() = response.toBytes();
}

void method_get(utils::HTTP_VERSION version, const std::string& path,
			HttpResponse& response, wsrv::Fds::fd_array_iter it_current_fd){
	bool is_file;

	response.setStatusLine(version, "200", "OK");
			std::cout << path << std::endl;
	is_file = response.setupFile(
		path,
		get_error_file(
			"404",
			(*it_current_fd).GetParentSocketConfigReference()
		)
	);
	if (!is_file) {
		response.setStatusLine(version, "404", "Not Found");
	}
}

void method_post(utils::HTTP_VERSION version, const http_request::HttpRequest& request,
			HttpResponse& response, wsrv::Fds::fd_array_iter it_current_fd){
	Cgi cgi((*it_current_fd).GetParentSocketConfigReference(), request);
	std::vector<std::string> req_cgi(cgi.Exec());

	response.setStatusLine(version, req_cgi[0], req_cgi[1]);
	if (req_cgi[0] != "200") {
		error_setup_file(it_current_fd, response, req_cgi[0]);
	} else {
		// NEED TO PARS REQ_CGI BODY
		response.fillBody(req_cgi[3]);
	}
}

void method_delete(utils::HTTP_VERSION version, const std::string& path,
			HttpResponse& response, wsrv::Fds::fd_array_iter it_current_fd){
	FILE *is_file = fopen(path.c_str(), "r");

	if (is_file) {
		std::remove(path.c_str());
		response.setStatusLine(version, "200", "OK");
		//???WHICH PAGE TO RETURN???
	} else {
		response.setStatusLine(version, "404", "Not Found");
		error_setup_file(it_current_fd, response, "404");
	}
	fclose(is_file);
}

bool is_method_allowed(wsrv::Fds::fd_array_iter it_current_fd,
					HttpResponse& response,
					const std::string& path,
					utils::METHOD method,
					utils::HTTP_VERSION	version){
	bool is_allowed;

	try {
		is_allowed = (*it_current_fd).GetParentSocketConfigReference().
					getRoute(path).isMethodPresent(method);
	} catch (utils::Exception& e) {
		response.setStatusLine(version, "404", "Not Found");
		error_setup_file(it_current_fd, response, "404");
		return false;
	}
	if (!is_allowed){
		response.setStatusLine(version, "405", "Method Not Allowed");
		error_setup_file(it_current_fd, response, "405");
		return false;
	}
	return true;
}

bool execute_method(wsrv::Fds::fd_array_iter it_current_fd, HttpResponse& response,
				const http_request::HttpRequest& request){
	bool is_allowed;
	utils::METHOD method;
	utils::HTTP_VERSION	version;
	const std::string& path = request.getStatusLine().getUrl();

	method = request.getStatusLine().getMethod();
	version = request.getStatusLine().getHttpVersion();
	is_allowed = is_method_allowed(it_current_fd, response, path, method, version);
	if (is_allowed){
		if (method == utils::GET){
			method_get(
				version, 
				get_file(path, (*it_current_fd).GetParentSocketConfigReference()), 
				response, 
				it_current_fd
			);
		} else if (method == utils::POST) {
			method_post(version, request, response, it_current_fd);
		} else {
			method_delete(
				version, 
				get_file(path, (*it_current_fd).GetParentSocketConfigReference()), 
				response, 
				it_current_fd
			);
		}
	}
	(*it_current_fd).GetResponseMessageReference() = response.toBytes();
	return is_allowed;
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
	} catch (utils::Exception&) {}

	// {
	// 	std::cout << "\t// Response test output //" << std::endl;
	// 	std::cout << response.toBytes().toBytes();
	// }

	http_request::HttpRequestParser request;
	bool is_allowed;

	is_allowed = true;
	try {
		request.parseHttpRequest((*it_current_fd).GetRequestMessageReference());
		is_allowed = execute_method(it_current_fd, response, request.getHttpRequest());
	} catch (utils::Exception& e) {
		if (is_allowed){
			invalid_request(it_current_fd, response, e);
		}
	}
	// {
	// 	const std::vector<std::string>& v = it_current_fd->GetResponseMessageReference().getLines();
	// 	for (size_t i = 0; i < v.size(); i++){
	// 		std::cout << v[i] << std::endl;
	// 	}
	// }
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
