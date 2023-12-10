/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:46:46 by minabe            #+#    #+#             */
/*   Updated: 2023/12/10 09:59:17 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(void)
{
	if (DEBUG)
		std::cout << "Socket default constructor called" << std::endl;
}

Socket::Socket(int domain, int type, int protocol)
{
	if (DEBUG)
		std::cout << "Socket constructor called" << std::endl;
	this->_socket = socket(domain, type, protocol);
	if (this->_socket == -1)
	{
		std::cerr << "Socket creation failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Socket::Socket(Socket const &src)
{
	if (DEBUG)
		std::cout << "Socket copy constructor called" << std::endl;
	*this = src;
}

Socket &Socket::operator=(Socket const &rhs)
{
	if (DEBUG)
		std::cout << "Socket assignation operator called" << std::endl;
	if (this != &rhs)
	{
		this->_socket = rhs._socket;
	}
	return (*this);
}

Socket::~Socket(void)
{
	if (DEBUG)
		std::cout << "Socket destructor called" << std::endl;
	close(this->_socket);
}
