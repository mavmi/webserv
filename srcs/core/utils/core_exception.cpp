/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exception.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:27:58 by msalena           #+#    #+#             */
/*   Updated: 2023/01/28 13:49:32 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/core/utils/core_exception.hpp"

namespace CORE{

CoreException::CoreException(const char* msg) : Exception(msg) { }

CoreException::CoreException(const std::string& msg) : Exception(msg) { }

CoreException::CoreException(const char* msg, const std::string& _file_, 
	const std::string& _function_, int _line_) 
	: Exception(msg, _file_, _function_, _line_) { }

CoreException::CoreException(const std::string& msg, const std::string& _file_, 
	const std::string& _function_, int _line_) 
	: Exception(msg, _file_, _function_, _line_) { }

CoreException::CoreException(const char* msg, const std::string& _file_, 
	const std::string& _function_, int _line_, int code)
	: Exception(msg, _file_, _function_, _line_, code) { }

CoreException::CoreException(const std::string& msg, const std::string& _file_, 
	const std::string& _function_, int _line_, int code)
	: Exception(msg, _file_, _function_, _line_, code) { }

std::string CoreException::output_() const {
	return "CORE_EXCEPTION: " + msg_;
}

}
