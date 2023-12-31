/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:51:09 by max               #+#    #+#             */
/*   Updated: 2023/10/03 23:27:24 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "Colors.hpp"
#include "Utils.hpp"

#include <stdio.h>
#include <iostream>
#include <cstring>

#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#include <fcntl.h>
#include <map>
#include <vector>
#include <list>

#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

/* USAGE :
-	Method and version are stored separtely in a string.
	Any version other than 1.0 or 1.1 is considered invalid
	if the method or the HTTP version is invalid, ret is set to 400 (BAD Request)
	otherwise it stays at its default 200 value
-	Implemented headers are parsed as follows : "KEY:[OWS]VALUE[OWS]"
	and stored in a map<string, string> as (KEY, VALUE)
	OWS = optionnal whitespace
-	An empty line ended by CRLF is considered to be the end of the header section
	anything that follows is stored in a single string labelled "_body"
*/
class Request
{
		private:
			std::string									_method;
			std::string									_version;
			std::map<std::string, std::string>			_headers;
			std::map<std::string, std::string>			_env_for_cgi;
			int											_ret;
			std::string									_body;
			int											_port;
			std::string									_path;
			std::string									_query;
			const std::string&							_raw;

			/*** PARSING ***/
			int			readFirstLine(const std::string& line);
			int			readPath(const std::string& line, size_t i);
			int			readVersion(const std::string& line, size_t i);
			int			checkMethod();
			int			checkPort();
			void		findQuery();
			std::string formatHeaderForCGI(std::string& key);
			std::string	nextLine(const std::string &str, size_t& i);


			/*** AVAILABLE HTTP METHODS ***/
			static	std::vector<std::string>	methods;

			/*** UNAVAILABLE CTORS ***/
			Request();
			Request(const Request&);

		public:
			Request(const std::string& str);
			~Request();
			Request&	operator=(const Request&);

			/*** GETTERS ***/
			const std::map<std::string, std::string>&			getHeaders() const;
			const std::map<std::string, std::string>&			getEnv() const;
			const std::string&									getMethod() const;
			const std::string&									getVersion() const;
			int													getRet() const;
			const std::string&									getBody() const;
			int													getPort() const;
			const std::string&									getPath() const;
			const std::string&									getQuery() const;
			const std::string&									getRaw() const;

			/*** SETTERS **/
			void	setBody(const std::string& line);
			void	setRet(int);
			void	setMethod(const std::string &method);

			/*** UTILS ****/
			int		parse(const std::string& str);
			void	resetHeaders();
			void	stripAll();
			void	displayHeaders() const;

			static std::vector<std::string>		initMethods();

};

std::ostream&	operator<<(std::ostream& os, const Request& re);

# endif