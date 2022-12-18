/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coreException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:22:49 by msalena           #+#    #+#             */
/*   Updated: 2022/12/18 22:14:16 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#define wsrv MAIN_NAMESPACE


namespace MAIN_NAMESPACE {

enum EXCEPTION_CODES{
	CRT_SOCK_ERR
} ;

class CoreException {
public:
	CoreException(const char*  msg, EXCEPTION_CODES code);
	CoreException(const std::string& msg, EXCEPTION_CODES code);
	~CoreException(void) throw();

	virtual const std::string whatMsg(void) const throw();
	virtual const EXCEPTION_CODES whatCode(void) const throw();

protected:
	const std::string	msg_;
	EXCEPTION_CODES 	code_;

	virtual std::string output_(void) const;
} ;

std::string whichCode(void);

}