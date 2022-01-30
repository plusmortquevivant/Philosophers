/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arichie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:54:48 by arichie           #+#    #+#             */
/*   Updated: 2022/01/30 15:54:50 by arichie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERROR_INPUT	1
# define ERROR_THREAD	2
# define ERROR_ENDSIM	3

# define ERRMSG_THREAD_CREATE	"Error: thread creation failed.\n"
# define ERRMSG_THREAD_JOIN		"Error: thread join failed.\n"
# define ERRMSG_THREAD_DETACH	"Error: thread detach failed.\n"
# define ERRMSG_MUTEX_DESTROY	"Error: mutex destroy failed.\n"

#endif
