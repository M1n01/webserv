/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minabe <minabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:00:01 by minabe            #+#    #+#             */
/*   Updated: 2023/12/10 18:04:31 by minabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

void	runServer(void)
{
	std::cout << "runServer..." << std::endl;
}

int	main(int argc, char **argv)
{
	// if (argc != 2)
	if (argc > 2)
	{
		std::cerr << "Usage: ./server <config_file_path>" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << argv[1] << std::endl;
	runServer();
	return (0);
}
