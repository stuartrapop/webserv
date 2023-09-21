/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstockli <mstockli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:30:23 by mstockli          #+#    #+#             */
/*   Updated: 2023/09/13 13:57:18 by mstockli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDER_HPP
# define RESPONDER_HPP

#include <stdio.h>
#include <iostream>
#include <cstring>

#include <stdio.h> 
#include <map>
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include <fcntl.h>

#include "ListeningSocket.hpp"
#include "Handler.hpp"
#include "CgiHandler.hpp"



class Responder
{
	public:
		Responder(Handler &handler, std::map<int, std::string> errorMap, int new_socket);
		~Responder();

		void respond(Handler &handler);
		std::string createResponseHeader(Handler &handler);
		void sendChunkedResponse(int socket, const std::string& content);

		std::string get_error_content(int statusCode);
		std::string loadFile(std::string errorFile);

		void        setServer(ListeningSocket &server);
		void		setRequest(Handler &req);
		bool		checkError();
		void    	buildResponse();

	private:
		std::map<int, std::string>	errorMap;
		std::map<int, std::string>	statusMessage;
		ListeningSocket				_server;

		Handler						request;
		CgiHandler					_cgi_obj;

		int							_cgi;
		int							_cgi_fd[2];


		int							new_socket;
		int							_code;			// status code
        // short           _code; ??


};

#endif