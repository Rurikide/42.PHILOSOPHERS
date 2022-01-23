/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/23 17:30:06 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    *test()
{
    printf("Hello\n");
    usleep(1000000);
    printf("Bye\n");
    return 0;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    pthread_t th;
    pthread_t t2;

    pthread_create(&th, NULL, &test, NULL);
    pthread_create(&t2, NULL, &test, NULL);
    pthread_join(th, NULL);
    pthread_join(t2, NULL);
    
    return (0);
}