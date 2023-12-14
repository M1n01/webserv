/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:53:41 by minabe            #+#    #+#             */
/*   Updated: 2023/12/14 08:33:48 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "config.hpp"

const int	Socket::_nonblock;

Socket::Socket(void) : _socketfd(0), _port(PORT), _ip(IP_ADDRESS)
{
	bzero(&_addr, sizeof(_addr));
}

Socket::Socket(int port, std::string ip) : _socketfd(0), _port(port), _ip(ip)
{
	bzero(&_addr, sizeof(_addr));
}

Socket::Socket(Socket const &src)
{
	*this = src;
}

Socket	&Socket::operator=(Socket const &rhs)
{
	if (this != &rhs)
	{
		_socketfd = rhs._socketfd;
		_port = rhs._port;
		_ip = rhs._ip;
		_addr = rhs._addr;
	}
	return (*this);
}

Socket::~Socket(void) {}

int	Socket::getSocketfd(void) const
{
	return (_socketfd);
}

int	Socket::getPort(void) const
{
	return (_port);
}

std::string	Socket::getIp(void) const
{
	return (_ip);
}

struct sockaddr_in	Socket::getAddr(void) const
{
	return (_addr);
}

int	Socket::getNonblock(void) const
{
	return (_nonblock);
}

void	Socket::setSockAddr(void)
{
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_len = sizeof(_addr);
}

void	Socket::createSocket(void)
{
	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd < 0)
	{
		std::cerr << "Error: socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	setSockAddr();
	bindSocket();
	listenSocket();
	nonBlockingSocket();
}

void	Socket::nonBlockingSocket(void)
{
	if (ioctl(_socketfd, FIONBIO, &_nonblock) < 0)
	{
		std::cerr << "Error: socket non-blocking failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Socket::bindSocket(void)
{
	if (bind(_socketfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		std::cerr << "Error: socket binding failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Socket::listenSocket(void)
{
	if (listen(_socketfd, MAX_CONNECTIONS) < 0)
	{
		std::cerr << "Error: socket listening failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Socket::acceptSocket(void)
{
	int	addrlen = sizeof(_addr);
	int	new_socket = accept(_socketfd, (struct sockaddr *)&_addr, (socklen_t *)&addrlen);
	if (new_socket < 0)
	{
		std::cerr << "Error: socket accepting failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	_socketfd = new_socket;
}

void	Socket::connectSocket(void)
{
	if (connect(_socketfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		std::cerr << "Error: socket connecting failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void	Socket::closeSocket(void)
{
	close(_socketfd);
}
