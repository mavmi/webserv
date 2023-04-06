/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exception.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:22:49 by msalena           #+#    #+#             */
/*   Updated: 2023/04/06 17:44:41 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "../../utils/utils.hpp"

namespace CORE {

class CoreException : public utils::Exception {
public:
	CoreException(const char* msg);
	CoreException(const std::string& msg);

	CoreException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
	CoreException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

	CoreException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
	CoreException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
	virtual std::string output_() const;
};

}
