/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:31:16 by msalena           #+#    #+#             */
/*   Updated: 2023/04/06 13:42:13 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#include "../http_request_parser/http_request_parser.hpp"
#include "../configurations/configuration.hpp"
#include "utils/core_exception.hpp"
#include "../utils/utils.hpp"

namespace CORE {

class Cgi {
public:
	typedef Configuration::ServerType	parent_socket_config;
	typedef http_request::HttpRequest	http_request;

	Cgi(const parent_socket_config& server_conf, const http_request& request);
	~Cgi(void);

	std::vector<std::string> Exec(void);
	char** SetEnv(void) const;
private:
	std::map<std::string, std::string> env;
	std::string php_script;
	int read_fd;
	int write_fd;
	int child_pid;

	std::string ParseName_(const std::string& url) const;

	int StartPHPProc_(void);
	std::string ReadFromCgiProc_(void);
	void KillClose_(void);
	void PushBackStatus_(const std::string& code, const std::string& msg, 
						std::vector<std::string>& ret);
	
};

}