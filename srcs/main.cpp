/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:00:01 by minabe            #+#    #+#             */
/*   Updated: 2023/12/10 18:38:15 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

void	nonBlockingSocket(void)
{
	int	sockfd;
	struct sockaddr_in	addr;
	char	buf[2048];
	int	n;
	int	val;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		std::cerr << "socket error" << std::endl;
		exit(EXIT_FAILURE);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	/*
	ここで、ノンブロッキングに設定しています。
	val = 0でブロッキングモードに設定できます。
	ソケットの初期設定はブロッキングモードです。
	*/
	val = 1;
	ioctl(sockfd, FIONBIO, &val);
	
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "bind error" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		memset(buf, 0, sizeof(buf));
		n = recv(sockfd, buf, sizeof(buf), 0);
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
	close(sockfd);
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
