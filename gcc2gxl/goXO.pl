#!/usr/bin/perl

#/***************************************************************************
#     copyright            : (C) 2001 by lucas75it
#     email                : lucas75it@yahoo.it
#***************************************************************************/
#/***************************************************************************
# *                                                                         *
# *   This program is free software; you can redistribute it and/or modify  *
# *   it under the terms of the GNU General Public License as published by  *
# *   the Free Software Foundation; either version 2 of the License, or     *
# *   (at your option) any later version.                                   *
# *                                                                         *
# ***************************************************************************/

#use strict;
use Carp;
use Getopt::Long;


my $ifile=();

my $helpMsg = "Usage:  $0

\t --ifile file |  --ifile=file input file\n\n";

GetOptions( "ifile=s" => \$ifile);         # --ifile pippo  or --ifile=pippo 

unless ( defined($ifile) ) {
    print $helpMsg;
    exit(0);
}

$tmpF = $ifile . ".one.for.line.temp";     # temporary file
$tblF = "g2x.map";                         # traslation table
$outF = $ifile . ".gxl";                   # output file


printf "\n  SPLITTING one field FOR line on $ifile";
# splits the GAST file
system("./oneFORline.pl --ifile $ifile --ofile $tmpF");

printf "\n  GENERATING gxl file $outF";
# trslate the GAST file 
system("./gcc2gxl.pl --table $tblF --ifile $tmpF --ofile $outF");

system("rm -f $tmpF");

printf "\nAll done !!\n";
