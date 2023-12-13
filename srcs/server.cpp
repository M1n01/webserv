/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:00:01 by minabe            #+#    #+#             */
/*   Updated: 2023/12/13 23:12:44 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "config.hpp"

void	nonBlockingSocket(void)
{
	Socket	sock(PORT, IP_ADDRESS);

	sock.createSocket();
	/*
	ここで、ノンブロッキングに設定しています。
	val = 0でブロッキングモードに設定できます。
	ソケットの初期設定はブロッキングモードです。
	*/

	char	buf[BUFFER_SIZE];
	int		n;
	while (true)
	{
		bzero(buf, sizeof(buf));
		n = recv(sock.getSocketfd(), buf, sizeof(buf), 0);
		if (n < 1)
		{
			if (errno == EAGAIN)
				std::cout << "まだデータは来ていない" << std::endl;
			else
			{
				strerror(errno);
				break ;
			}
		}
		else
		{
			std::cout << "受信したデータ: " << buf << std::endl;
			break ;
		}
		sleep(1);
	}
	sock.closeSocket();
}

int	main(int argc, char **argv)
{
	// if (argc != 2)
	if (argc > 2)
	{
		std::cerr << "Usage: ./server <config_file_path>" << std::endl;
		exit(EXIT_FAILURE);
	}
	(void)argv[1];
	nonBlockingSocket();
	return (0);
}
