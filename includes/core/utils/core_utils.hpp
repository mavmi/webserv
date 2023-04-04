/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:23:10 by msalena           #+#    #+#             */
/*   Updated: 2023/02/25 19:32:01 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "../sockets.hpp"
#include "../server.hpp"
#include "../managed_fds.hpp"
#include "../../utils/utils.hpp"
#include "../../http_request_parser/http_request_parser.hpp"
#include "../../http_response_generator/http_response.hpp"


namespace CORE {

/*
 * Fills masterread set with all listening sockets
 *
 * Return:	the highest socket fd
 */
int sockets_to_masterread(Sockets& sockets, ManagedFds& masterread);

/*
 * Create sockets for every server from config
 */
void create_sockets(const wsrv::Configuration& servers, Sockets& sockets_array);

/*
 * Return:	a path to the error file with 'statusCode' name
 */
std::string get_error_file(const std::string& statusCode,
	const wsrv::configuration::ServerConfiguration::ErrorPagesContainerType& errorFiles);

/*
 * Set path of error page to response by 'status_sode'
 */
void error_setup_file(wsrv::Fds::fd_array_iter it_current_fd,
				HttpResponse& response, const std::string& status_sode);

/*
 * Generate the response when the request is invalid
 */
void invalid_request(wsrv::Fds::fd_array_iter it_current_fd, HttpResponse& response,
				utils::Exception& e);

//ADD METHODS

/*
 * Checks that the method is supported by the target resource
 *
 * Return:	True if supported or otherwise False
 */
bool is_method_allowed(wsrv::Fds::fd_array_iter it_current_fd,
					HttpResponse& response,
					const std::string& path,
					utils::METHOD method,
					utils::HTTP_VERSION	version);

/*
 * Execute coming method
 */
void execute_method(wsrv::Fds::fd_array_iter it_current_fd, HttpResponse& response,
				const http_request::HttpRequest& request);

/*
 * Generate the response for current fd
 */
void response_generator(wsrv::Fds::fd_array_iter current_fd_pair);

/*
 * Throw exceptions if there is some problem in Server
 */
void server_throws(int is_fd_in_set, std::string invalid_fd_msg,
				std::string invalid_fnc_msg);

}
