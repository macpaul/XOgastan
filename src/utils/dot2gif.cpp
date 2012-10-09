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

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include "utils/dot2gif.h"


// ---------------------------------------------------------------------------
//  Function
// ---------------------------------------------------------------------------

void 
dot2gif(string &dotFile, string &gifFile) {

  string        s;          // temporary string
  const char    *args[5];   // arguments of dot
  pid_t         childp;     // child process
  int           status;     // status of the child process

  // build the args array
  args[0] = "dot";
  args[1] = "-Tgif";
  s = "-o" + gifFile;
  args[2] = s.c_str();
  args[3] = dotFile.c_str();
  args[4] = NULL;

  childp = fork();

  if (childp == 0) {

    execlp("dot",args[0],args[1],args[2],args[3],args[4]);
  
  }
  else if (childp != 0)
    wait(&status);

  return;
}
