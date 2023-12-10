/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:47:12 by minabe            #+#    #+#             */
/*   Updated: 2023/12/10 09:58:57 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <iostream>
# include <cstring>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>

# define DEBUG 1

class Socket
{
	public:
		Socket(void);
		Socket(int domain, int type, int protocol);
		Socket(Socket const &src);
		Socket &operator=(Socket const &rhs);
		~Socket(void);
}

#endif
