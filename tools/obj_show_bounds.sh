#!/bin/bash

[[ "$1" == "" ]] && echo "usage: $0 <model.obj>" && exit 1;

cat $1 | awk '

BEGIN{
    FS=" ";
    x=9999; X=-9999;
    y=9999; Y=-9999;
    z=9999; Z=-9999;
} 

($0 ~ /^v /) {
    if(x>$2) x=$2; 
    if(X<$2) X=$2;

    if(y>$3) y=$3;
    if(Y<$3) Y=$3;

    if(z>$4) z=$4;
    if(Z<$4) Z=$4;
} 

END{ 
    abzX=(X<0)?-X:X; 
    abzY=(Y<0)?-Y:Y; 
    abzZ=(Z<0)?-Z:Z; 

    abzx=(x<0)?-x:x; 
    abzy=(y<0)?-y:y; 
    abzz=(z<0)?-z:z; 

    print "X: "x" <-> "X" (avg. dist: "(abzx-abzX)/2")"; 
    print "Y: "y" <-> "Y" (avg. dist: "(abzy-abzY)/2")";
    print "Z: "z" <-> "Z" (avg. dist: "(abzz-abzZ)/2")";
}'
