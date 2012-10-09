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

##########################################################################
# 
# Translate the output file produced by oneFORline.pl into a gxl format.
# The new format is an XML dtd 
#
##########################################################################

#use strict;
use Carp;
use Getopt::Long;
use g2x;


my $ifile=();
my $ofile=();
my $tfile=();
my $help=();
my $verbose=();
my $DBG=();

my @rows = ();

my $helpMsg = "read from STDIN print on STDOUT
\nUsage:  $0

\t --ofile file |  --ofile=file output file
\t --ifile file |  --ifile=file input file
\t --table tab |  --table=tab translation table
\t --DEBG   k |  --DBG=k debug level
\t --help  this help\n\n";

GetOptions( "verbose"  => \$verbose,      # --verbose
            "DBG=i"    => \$DBG,          # --DBG 2 or --DBG=3
            "ifile=s" => \$ifile,         # --ifile pippo  or --ifile=pippo
            "ofile=s" => \$ofile,         # --ofile pippo  or --ofile=pippo
            "table=s" =>  \$tfile,        # --tfile pippo  or --tfile=pippo
            "help+"    => \$help );       # if --help print a message it does not require  arguments

# process args
unless (!defined($help)) {
    print $helpMsg;
    exit(0);
}

unless (defined($ifile) && defined($ofile) && defined($tfile)) {
    print $helpMsg;
    exit(0);
}




####################################################################
#        PHASE 1:                                                  #
#        read translation table                                    #
#        build an hash table of hash tables for traslantion        #
####################################################################

# read translation table
open(FH,"$tfile") || die "unable to open translation table $tfile:$!";
@rows = <FH>;
close(FH);

my %gcc2ga=();
# remove extra initial spaces
foreach my $r (@rows){
    $r =~ s/\s+$//g;
    $r .= "\n";
}


if ($DBG == 2) { print "Loading traslation tables\n"; }

#builds an hash table of hash tables
my $perHundred = 0;
my %gcc2ast =();
my $obj =();
my $line = 0;
foreach my $r (@rows){
    $line ++;

    chop($r);
    next if ( ($r =~ /^\s*#/) || ($r =~ /^\s*$/)); #jump white line

    if (($DBG == 2) or ($DBG == 3)) { 
	print "\tReading new rule line from $tfile ==>\n\t==> $r\n"; 
    }
	     
    # Is it a code ? 
    if ($r =~ /^case\s*(\w*):/) {
	# get the node_code : entry of the traslation table
	my $gcc_type = $1;
	$gcc_type =~ tr/[A-Z]/[a-z]/;     # UPPER 2 low

	$obj = new g2x();
	$obj -> name($gcc_type);
	$gcc2ast{$gcc_type} = $obj;

	if ($DBG == 3) { print "OLD TABLE stored. Creating new table\n"; }
	
    } elsif ($r =~/NULL/) { 

	# NO RULE for this gcc_type
	$obj -> no_rule(1);

	if ($DBG == 3) { print "\tNO traslation RULES for $gcc_type\n"; }

    } else {
        # this must be a traslation rule

	# get left and right member
	($left, $right) = split('%',$r);
	# eat all spaces in left
	$left =~ s/\s*//g;
	# eat initial && final spaces in right
	$right =~ s/^\s*//g;
	$right =~ s/\s*$//g;
	
	$r = $left . "%" .$right;
	# add $r couple traslation in $fields
	$obj -> addEntry(split('%',$r));

	if ($DBG == 3) { print "\tInserting rule\n\t  $left % $right\n"; }

    }
}

if ($DBG == 2) { print "ALL TABLES loadeds\n\n"; }


# PRINT TABLES if the flag --verbose is raisen
if($verbose){
    foreach my $k (keys %gcc2ast){
	my $o = $gcc2ast{$k};
	$o->printTable();
    }
}



####################################################################
#        PHASE 2:                                                  #
#        translate the input file                                  #
####################################################################


# OPEN the input and output files
open(FH,"$ifile") || die "unable to open $ifile:$!";
open(FOUT,"> $ofile") or die "Canno't create the output file " . $ofile;


# print HEAD of the xml document
print FOUT "<?xml version=\"1.0\"?>
\n<!DOCTYPE gxl SYSTEM \"gxl.dtd\">
\n
\n<gxl><graph id=\"GCC_AST\">
\n";


# traslate input file 

$r = "";                 # currenr row from FH
$new_r = "";             # new row after trslation
$obj = ();               # object table and traslation table 
%table = ();
$fieldR = "";            # the base fields of $r (from FH) and the current key 
$fieldK = "";
$star = 0;               # the * value in $fieldR
$index = 0;              # the current index 
$gxl_node = "";          # the gxl_NODE and gxl_EDGE
$gxl_edge = "";
$next_is_NODE_CODE = 0;  # 1 if the next $r is a NODE_CODE, 0 otherwise
$node_code = "";         # the currente node_code
$no_tbale = 0;           # 0 if node_code have a traslation's table, 1 otherwise

$line = 0;
while ( $r = <FH>){
    $line ++;
    chop($r);
    next if ($r =~ /^\s*$/); #jump white line

    if (($DBG == 2) or ($DBG == 3)) { 
	print "\tProcessing new line from $ifile\n\t-->\t$r.\n"; 
    }

 
    # START a NEW NODE ?
    if ($r =~ /^@(\d*)/) {
	
	# save the current new index
	$index = $1;

	# dump last node and its edges
	if ( ($gxl_node ne "") ) {
	    print FOUT $gxl_node . "</node>\n\n";
	    print FOUT $gxl_edge . "\n\n\n";

	    $gxl_node = "";
	    $gxl_edge = "";
	}
	
	# raise flag next_is_NODE_CODE 
	$next_is_NODE_CODE = 1;

	# CREATE new NODE
	$gxl_node = "<node id=\"nd$index\">\n";

	if ($DBG == 3) { 
	    print "START a new node. Old node saved.\nNode_INDEX : $index\n"; 
	}

    }
    # THE NODE CODE
    elsif ($next_is_NODE_CODE) {
	
	#fall the flag
	$next_is_NODE_CODE = 0;
	
	#get the code, eat initial and final spaces
	$node_code = $r;

	# ADD the node_code to NODE
	$gxl_node .= "\t<type xlink:href=\"gccast.xml#$node_code\"/>\n";

	# LOAD object for this node code, and check if it exist
	$obj = $gcc2ast{$node_code};
	if (!defined($obj)){
	    warn "Warning - unnable to translate type:", $node_code ,"\n";
	} else {
	    # HAVE THIS NODE a TABLE ?
	    $no_table = $obj -> haveTable();
	    if (! $no_table) {
		#LOAD traslation TABLE
		%table = %{$obj -> getTable()};

		if ($DBG == 3) { print "\t$index-NODE_CODE ok ! Table loaded.\n"; }

	    } else {
		if ($DBG == 3) { print "\t$index-NODE_CODE ok ! No table rule.\n"; }
	    }


	}


    }
    # FIELD to TRASLATE
    elsif (! $no_table) {

	# get the field of the ROW, and eat final spaces
	$fieldR = ($r =~ /(\w*:)\s.*/) ? $1 : $r;
	$fieldR =~ s/\s*$//g;

	foreach $k (%table) {
	
	    # get the field of the KEY
	    $fieldK = ( ($k =~ /(\w*:)\*/) ? $1 : $k);

 	    # the rule match the current row ??
	    if ($fieldK eq $fieldR) {
		
		$_ = $k;
		SWITCH : {
		    
		    # is field:* RULE 
		    /\w*:\*/ && do {
			
			# get the * from the ROW
			$r =~ /\w*:\s(\S*)/;
			$star = $1;

			# parse star : ENTITY analysis
			$star =~ s/&/&amp;/g;     # change & in &amp;
			$star =~ s/</&lt;/g;      # change < in &lt;
			$star =~ s/>/&gt;/g;      # change > in &gt;
			$star =~ s/\'/&apos;/g;   # change ' in &apos;
			$star =~ s/\"/&quote;/g;  # change " in &quote;

			# if it's a string of identifier_node
			if ( ($node_code eq "identifier_node") && 
			     ($fieldR eq "strg:") ) {
			    #change some special word
			
			    if ($DBG == 3) 
			    { print "\tString -#$star#-" }
			    $star =~s/long_double/long double/g;
			    $star =~s/unsigned_int/unsigned int/g;
			    $star =~s/long_int/long int/g;
			    $star =~s/unsigned_long_int/unsigned long int/g;
			    $star =~s/long_unsigned int/unsigned long int/g;
			    $star =~s/unsigned_long/unsigned long/g;
			    $star =~s/short_int/short int/g;
			    $star =~s/unsigned_short_int/unsigned short int/g;
			    $star =~s/short_unsigned int/unsigned short int/g;
			    $star =~s/unsigned_short/unsigned short/g;
			    $star =~s/signed_char/signed char/g;
			    $star =~s/unsigned_char/unsigned char/g;
			    if ($DBG == 3) 
			    { print " became -#$star#-\n" }
			}

			# get the translation
			$new_r = $table{$k};
			
			# substitute the * value
			if ($new_r =~ /edge/) {
			    $new_r =~ s/\*/nd$star/;
			} else {
			    $new_r =~ s/\*/$star/;
			}			    
		        last SWITCH;
		    };

		    # default is field RULE
		    $new_r = $table{$k};
		}

		# is an edge ?
		if ($new_r =~ /<edge/) {
		    # set the current index in the edge
		    $new_r =~ s/index/nd$index/;
		    # ADD to the edges
		    $gxl_edge .= ($new_r . "\n");

		} 
		# is a node's attribute ?
		else {
		    # ADD to the node's attribute
		    $gxl_node .= ("\t" . $new_r . "\n");
		}

		# FEEDBACK TO THE USER
		if (($verbose) && !($line % 5000)) {print "now at line $line\n"; }
		
		if ($DBG == 2) { print "\t$index-translate\n\t\t$r\n"}
		
		if ($DBG == 3) { 
		    print "\t$index-translate\n\t\t$r ==>\n\t\t $new_r\n";
		}
	    }
	    
	}

    }

}

# dump last node and its edges
if ( ($gxl_node ne "") ) {
     print FOUT $gxl_node . "</node>\n\n";
     print FOUT $gxl_edge . "\n\n\n";
     $gxl_node = "";
     $gxl_edge = "";
}

# prit TAIL pf the xml document
print FOUT "\n</graph></gxl>"



