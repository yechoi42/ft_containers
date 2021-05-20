/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:40:29 by yechoi            #+#    #+#             */
/*   Updated: 2021/05/20 13:12:17 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "test_list.hpp"

enum Type
{
    LIST,
    VECTOR,
    MAP,
    STACK,
    QUEUE,
    DEQUE,
    ERROR,
};

int check_container(std::string str)
{
    if (str == "list")
        return (LIST);
    else if (str == "vector")
        return (VECTOR);
    else if (str == "map")
        return (MAP);
    else if (str == "stack")
        return (STACK);
    else if (str == "queue")
        return (QUEUE);
    else
        return (ERROR);
}

void test_vector()
{
}

void test_map()
{
}

void test_stack()
{
}

void test_queue()
{
}

int main(int argc, char **argv)
{
    int container = check_container(argv[1]);

    switch (container)
    {
        case LIST:
            test_list();
            break;
        case VECTOR:
            test_vector();
            break;
        case MAP:
            test_map();
            break;
        case STACK:
            test_stack();
            break;
        case QUEUE:
            test_queue();
            break;
        default:
            std::cerr << "Invalid argument!" << std::endl;
            break;
    }
}