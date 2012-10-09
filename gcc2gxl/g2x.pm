package g2x;

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


#
# translation rule representatio
# cation must be paid to the fancy rule used to translate
# file and loc; this is due to the gcc format:
#
#     srcp: file.c:lic
# thus srcp must be converted into both file and loc!
#
#
 
use vars qw($AUTOLOAD);  # it's a package global

use Carp;


# attributes of this class:

my %fields =(
	     name => undef,
	     gcc2ast => undef,
	     no_rule => undef
	     );

my $HEADERS = 1 ;
my $DBG=0;


sub  new{
    my $that=shift;
    my $class = ref($that) || $that;
    my %lfields = %fields;   # copy here the class copy to avoid mixing entries due to multiple kids
    my $self = {
    _permitted => \%lfields, # my own copy of the class antries
    %fields,                 # my own copy
    };
    bless $self, $class;
    return ($self  -> _init());
}


sub _init{
 my $self=shift;
 my $type  = ref($self) or croak "$self is not an object\n";
 my %table=();
 
 $self -> {'gcc2ast'} = \%table;
 $self -> {'name'} =();
 $self -> {'no_rule'} = 0;
 return $self;
}



sub setDBGLevel{
 my $self=shift;
 my $type  = ref($self) or croak "$self is not an object\n";
 $DBG=shift;
}



sub addEntry{

 my $self=shift;
 my ($old,$new)=(@_);

 my $type  = ref($self) or croak "$self is not an object\n";
 my %table = %{$self -> {'gcc2ast'}};
 if (defined($table{$old})){
     warn "$old already defined in:", $self -> {'name'},"\n";
     $table{$old} .= ("%" . $new);
 }else{
     $table{$old} = $new;
 }

 $self -> {'gcc2ast'} = \%table;
}


sub getTable{
 my $self=shift;
 return  $self -> {'gcc2ast'};
}



sub getCode{
 my $self=shift;
 my ($key)=shift;

 my $type  = ref($self) or croak "$self is not an object\n";
 my %table = %{$self -> {'gcc2ast'}};
 if (!defined($table{$key})){
     warn "$key unknown for:", $self -> {'name'},"\n";
 }
 return $table{$key};
}


sub haveTable{
 my $self=shift;
 return $self -> {'no_rule'};
}


sub printTable{

 my $self=shift;

 print "case ", $self -> {'name'},"\n";
 if ($self -> {'no_rule'} != 1) {
     my %table = %{$self -> {'gcc2ast'}};
     foreach my $k (keys %table){
	 print $k,"%",$table{$k},"\n";
     }
     print "\n\n";
 } else {
     print "NO translantion RULE\n\n";
 }

}

sub AUTOLOAD {
    my $self=shift;
    my $type  = ref($self) or croak "$self is not an object\n";
    my $name=$AUTOLOAD;

    $name =~ s/(.*:)//; #strip fully qualified portion

    # print "$1 Called AUTOLOAD for >$name<:>@_<\n" ;

    unless ( exists $self -> {'_permitted'}->{$name}){
        croak "$1 Can't access $name field in class type\n";
    }

    if(@_){
        return $self -> {$name}=shift;
    }else{
        return $self -> {$name};
    }
}

1;
