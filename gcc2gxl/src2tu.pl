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

use strict;

my $code=();
foreach my $p (@ARGV){
    if ($p =~ /\.c$/){
	$code .= $p;
    }
}

my $image = $code;
$image =~ s/\.c/\.o/;

my $added= "-traditional  -fno-strict-prototype -fno-strict-prototype -fdump-translation-unit ";
my $parms = join (" ",@ARGV);

my $cmd="g++ " . $added . $parms;

print $cmd,"\n";

open (FH , "| $cmd ") || die "Unable to pipe\n";
my @out =<FH>;
close(FH);


system ("rm -vf $image");

exit(0);

