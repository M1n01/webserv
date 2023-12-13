/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:50:12 by minabe            #+#    #+#             */
/*   Updated: 2023/12/13 23:07:34 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <iostream>
# include <unistd.h>
# include <cstring>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <netinet/in.h>
# include <fcntl.h>

class Socket
{
	private:
		int					_socketfd;
		int					_port;
		std::string			_ip;
		struct sockaddr_in	_addr;
		static const int	_nonblock = 1;

	public:
		Socket(void);
		Socket(int port, std::string ip);
		Socket(Socket const &src);
		Socket	&operator=(Socket const &rhs);
		~Socket(void);

		int					getSocketfd(void) const;
		int					getPort(void) const;
		std::string			getIp(void) const;
		struct sockaddr_in	getAddr(void) const;
		int					getNonblock(void) const;

		void				setSockAddr(void);

		void				createSocket(void);
		void				nonBlockingSocket(void);
		void				bindSocket(void);
		void				listenSocket(void);
		void				acceptSocket(void);
		void				connectSocket(void);
		void				closeSocket(void);
};

#endif
