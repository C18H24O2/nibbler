/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@dynamicdispat.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:07:40 by kiroussa          #+#    #+#             */
/*   Updated: 2026/03/08 02:08:57 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print>

namespace Nibbler
{

void main(int argc, char **argv)
{
	std::println("Hello, World!");
}

}; // namespace Nibbler

int main(int argc, char **argv)
{
	Nibbler::main(argc, argv);
	return 0;
}
