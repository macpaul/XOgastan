/***************************************************************************
			   dot2gif.h  -  description
			      -------------------
     begin                : Aug 30 2001
     copyright            : (C) 2001 by Gianluca Masone
     email                : lucas75it@yahoo.it
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/*! \file 

  Header for the function that convert a dot file into
  a gif image file.

 */

#ifndef _DOT2GIF_H
#define _DOT2GIF_H

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <string>
// ---------------------------------------------------------------------------
//  Functions
// ---------------------------------------------------------------------------

//! Convert a dot file into agif image file
/*! 

  This function require :
  
  - the system call for the process management : fork, wait, exec
  - the free software graphviz  (the version used by the
  developer is graphviz 1.7c)

  \param dotFile Name of the dot file
  \param gifFile Name of the gif file
*/
extern void dot2gif(string &dotFile, string &gifFile);

#endif
