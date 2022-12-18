/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coreException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:27:58 by msalena           #+#    #+#             */
/*   Updated: 2022/12/18 22:16:33 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils/coreException.hpp"

namespace MAIN_NAMESPACE{

CoreException::CoreException(const char*  msg, EXCEPTION_CODES code) 
	: msg_(std::string(msg)), code_(code) {}

CoreException::CoreException(const std::string&  msg, EXCEPTION_CODES code)
	: msg_(msg), code_(code) {}

CoreException::~CoreException(void) throw() { }

const std::string CoreException::whatMsg(void) const throw(){
	return output_();
}

const EXCEPTION_CODES CoreException::whatCode(void) const throw(){
	return code_;
}

std::string CoreException::output_(void) const{
	return "CORE_EXCEPTION: " + whichCode(code_) + ": " + msg_;
}

std::string whichCode(EXCEPTION_CODES code){
	switch (code){
		case CRT_SOCK_ERR:
			return "CRT_SOCK_ERR";
			break ;
		default :
			return "";
	}
}

}