/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 21:19:53 by msalena           #+#    #+#             */
/*   Updated: 2023/04/06 13:41:53 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core/cgi.hpp"

namespace CORE {

	Cgi::Cgi(const parent_socket_config& server_conf, const http_request& request){
		env["AUTH_TYPE"] = "";
		env["CONTENT_TYPE"] = request.getRequestHeaders().getContentType();
		env["GATEWAY_INTERFACE"] = "CGI/1.1";
		env["PATH_INFO"] = server_conf.getRoot();
		env["PATH_TRANSLATED"] = server_conf.getRoot() + request.getStatusLine().getUrl();
		env["QUERY_STRING"] = "";
		env["REMOTE_HOST"] = request.getRequestHeaders().getHost();
		env["REMOTE_ADDR"] = request.getRequestHeaders().getHost();
		env["REMOTE_USER"] = "";
		env["REMOTE_IDENT"] = "";
		env["REQUEST_METHOD"] = wsrv::utils::methodToString(request.getStatusLine().getMethod());
		env["REQUEST_URI"] = request.getStatusLine().getUrl();
		env["SCRIPT_NAME"] = ParseName_(request.getStatusLine().getUrl());
		env["SCRIPT_FILENAME"] = server_conf.getRoot() + request.getStatusLine().getUrl();
		env["SERVER_NAME"] = server_conf.getServerName();
		env["SERVER_PROTOCOL"] = wsrv::utils::httpVersionToString(request.getStatusLine().getHttpVersion());
		env["SERVER_PORT"] = server_conf.getPort().toString();
		env["SERVER_SOFTWARE"] = server_conf.getServerName();
		env["CONTENT_LENGTH"] = "-1";
		php_script = env["SCRIPT_FILENAME"];
	}

	Cgi::~Cgi(void){}

	char** Cgi::SetEnv(void) const{
		const size_t size = env.size();
		char** arr = new char*[size + 1];
		size_t i = 0;
		std::map<std::string, std::string>::const_iterator it = env.begin();
		
		while (it != env.end()){
			arr[i] = strdup(std::string(it->first + "=" + it->second).c_str());
			i++;
			it++;
		}
		arr[i] = NULL;
		return arr;
	}

	std::string Cgi::ParseName_(const std::string& url) const {
		size_t slashPos = url.rfind('/');
		
		if (slashPos == std::string::npos) return url;
		return url.substr(slashPos + 1, url.size() - slashPos - 1);
	}

	std::vector<std::string> Cgi::Exec(void){
		int ret_status;
		std::string readed_ret;
		std::vector<std::string> ret;
		
		std::cout << "\t -> CGI: PHP interpreter was started" << std::endl;
		ret_status = StartPHPProc_();
		if (ret_status < 0) {
			PushBackStatus_("500", "Internal Server Error", ret);
			return (ret);
		}
		
		readed_ret = ReadFromCgiProc_();
		std::cout << "\t -> CGI: read result from the interpreter" << std::endl;
		std::cout << "HERERE: " << readed_ret << std::endl;
		KillClose_();
		if (readed_ret.empty()) {
			PushBackStatus_("500", "Internal Server Error", ret);
		} else if (!readed_ret.compare("cgi: failed")) {
			PushBackStatus_("400", "Bad Request", ret);
		} else {
			PushBackStatus_("200", "OK", ret);
			ret.push_back(readed_ret);
		}
		return (ret);
	}

	int Cgi::StartPHPProc_(void){
		int write_php_fds[2];
		int read_php_fds[2];
		int ret_status;

		ret_status = pipe(read_php_fds);
		if (ret_status < 0) return (-1);
		ret_status = pipe(write_php_fds);
		if (ret_status < 0) return (-1);
		ret_status = fork();
		if (ret_status < 0) return (-1);

		if (ret_status == 0) {
			char** env;
			char* php_cmd[3];
			
			env = SetEnv();
			dup2(write_php_fds[0], STDIN_FILENO);
			dup2(read_php_fds[1], STDOUT_FILENO);
			close(write_php_fds[1]);
			close(read_php_fds[0]);
			php_cmd[0] = strdup(std::string("/usr/bin/php").c_str());
			php_cmd[1] = strdup(php_script.c_str());
			php_cmd[2] = NULL;
			execve(php_cmd[0], php_cmd, env);
			exit(1);
		} else {
			child_pid = ret_status;
			close(write_php_fds[0]);
			close(read_php_fds[1]);
			write_fd = write_php_fds[1];
			read_fd = read_php_fds[0];
			return (0);
		}
	}
	
	std::string Cgi::ReadFromCgiProc_(void){
		int readbyten;
		char buf[utils::BUFFER_SIZE + 1];
		std::string ret;

		memset(buf, 0, utils::BUFFER_SIZE + 1);
		readbyten = 1;
		while (readbyten > 0) {
			readbyten = read(read_fd, buf, utils::BUFFER_SIZE);
			if (readbyten < 0) return NULL;
			ret += buf;
			memset(buf, 0, utils::BUFFER_SIZE + 1);
		}
		return (ret);
	}

	void Cgi::KillClose_(void){
		kill(child_pid, SIGKILL);
		close(write_fd);
		close(read_fd);
	}
	
	void Cgi::PushBackStatus_(const std::string& code, const std::string& msg, 
							std::vector<std::string>& ret){
		ret.push_back(code);
		ret.push_back(msg);
	}
}