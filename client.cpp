/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:35:41 by minabe            #+#    #+#             */
/*   Updated: 2023/12/12 19:41:25 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/Socket.hpp"

int	main(void)
{
	Socket	sock(8080, "");

	sock.createSocket();
	sock.connectSocket();
	sock.closeSocket();
	return (0);
}
