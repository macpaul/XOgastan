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

#################################################################
# Lexical analysis of the GCC output.
# The result is a output file with one field (and its value)
# for line.
#################################################################


#use strict;
use Carp;
use Getopt::Long;

my $ifile=();
my $ofile=();
my $help=();
my $DBG=();

my @rows = ();

my $helpMsg = "read from STDIN print on STDOUT
\nUsage:  $0

\t --ofile file |  --ofile=file output file
\t --ifile file |  --ofile=file input file
\t --DBG   k |  --DBG=k debug level
\t --help  this help\n\n";

GetOptions( "DBG=i"    => \$DBG,          # --DBG 2 or --DBG=3
            "ifile=s" => \$ifile,         # --ifile pippo  or --ifile=pippo
            "ofile=s" => \$ofile,         # --ofile pippo  or --ofile=pippo
            "help+"    => \$help );       # if --help print a message it does not require  arguments

# process args
unless (!defined($help)) {
    print $helpMsg;
    exit(0);
}
unless (defined($ifile) && defined($ofile)) {
    print $helpMsg;
    exit(0);
}



#
# Read the inpt file and tokenize it
#
open(FH,"$ifile") || die "unable to open $ifile:$!";
open(FOUT,"> $ofile") or die "Canno't create the output file " . $ofile;


$count = 1;
@elements = ();
$line = 0;

# delete space before and after each : , and alls other space, 
# and put one field per row on FOUT
while ( $r = <FH>){

    $line ++;
    next if ($r =~ /^\s*$/); #jump white line

 
    #If it's a begin of new node then get the node_code
    if ($r =~ /^@\d*\s*(\S*)\s*/) {

	$node_code = $1;
	
	if (($DBG==2) or ($DBG ==3)) {
	    print "processing ".$node_code." at line ". $line."\n";
	}

    }


    # CHANGES SOME PART 
    $r =~ s/:\s+@(\d+)/:$1/g;   # change body : @20 in body :20
    $r =~ s/:\s+-(\d+)/:-$1/g;  # change low : -20 in low :-20
    $r =~ s/:\s+(\d+)/:$1/g;    # change high : 20 in high :20
    $r =~ s/:\s+(\S+)/:$1/g;    # change strg : int in strg :int
    
    $r =~ s/(\S+)\s+:/$1:/g;    # change body :20 in body:20
    
    $r =~ s/op 0:/op0:/g;       # change op 0: in op0: 
    $r =~ s/op 1:/op1:/g;       # change op 1: in op1:
    $r =~ s/op 2:/op2:/g;       # change op 2: in op2:
    
    chop($r);                   #eat final space (it is \n)
    $r =~ s/^\s+//g;            #eat initial space
    $r =~ s/\s+/ /g;            #replace many consec. spaces with one space
    
    # CHANGES same multi string in one string
    $r =~ s/global fini/global_fini/g;
    $r =~ s/global init/global_init/g;
    $r =~ s/pseudo tmpl/pseudo_templ/g;

    if ($r =~ /strg:(\w*)\s*(\w*)\s*(\w*)\s*(\w*)\s*lngt:/) {
	$newStringValue = $1;
	if ($2 ne "") { $newStringValue .= ("_" . $2); }
	if ($3 ne "") { $newStringValue .= ("_" . $3); }
	if ($4 ne "") { $newStringValue .= ("_" . $4); }
    }
    $r =~ s/strg:(\w*)\s*(\w*)\s*(\w*)\s*(\w*)\s*lngt:/strg:$newStringValue lngt:/g;

    # SPLITTING IN MULTILINE
    @elements = split(' ',$r);


    #
    # PARSE fields and write them on FOUT
    foreach $el (@elements) {
	# RE-CHANGING SAME PART
	$el =~ s/(\w*):(.*)/$1: $2/g;     # change body:@20 in body: @20
	                                  # change low:-20 in low: -20
	                                  # change high:20 in high: 20
	                                  # ......
	$el =~ s/(\w*:) @(\d+)/$1: $2/g;  # change body: @20 in body: 20
	                                  # the address is whitout @
	$el =~ s/^\s*//g;                 # eat INITIAL spaces
	$el =~ s/\s*$//g;                 # eat FINAL spaces


	if ($DBG == 3) {
	    print "\tdumping element - $el\n";
	}
	
	# WRITE on FOUT

	# SPECIAL CASES
	$_ = $el;
	SWITCH : {

	    # CASE qualifier
	    /qual: (\w*)/  && do { 
		# qual: cvr 
		#
		# became 
		#
		# qual: c
		# qual: v
		# qual: r
		@qualifier = split('',$1);
		foreach $q (@qualifier) {print FOUT "qual:$q\n";}
		last SWITCH;
	    };

	    # CASE source position
	    /srcp: (<?.*>?):(\d*)/ && do { 
		# scrp: hello.c:10
		#
		# became 
		#
		# srcf: hello.c
		# srcl: 10
		print FOUT "srcf: $1\n";
		print FOUT "srcl: $2\n";
		last SWITCH;
	    };
	    
	    # DEFAULT 
	    print FOUT $el,"\n"; 
	}
    } 
	    
}


