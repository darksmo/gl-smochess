#!/bin/bash
obj="$1";

[[ "$obj" == "" ]] && echo "Usage: $0 <file.obj>" && exit 1;

cat $obj > ./.tmp.obj;


while [ 1 ];
do

    wc ./.tmp.obj;
    echo "-----------------------------------";
    echo "          Current Bounds";
    ./obj_show_bounds.sh ./.tmp.obj;
    echo "";
    echo "Input <x> <y> <z> or 'w' to write:";
    echo -n "> ";


    dx="";
    dy="";
    dz="";
    read vals;
    [[ "$vals" == "w" ]] && mv .tmp.obj $obj && echo "$obj written!" && exit 0;
    
    for i in $vals ; do 
        [[ "$dx" == "" ]] && dx="$i" && continue;
        [[ "$dy" == "" ]] && dy="$i" && continue;
        [[ "$dz" == "" ]] && dz="$i" && continue;
    done;

    [[ "$dx" == "" ]] && dx="0";
    [[ "$dy" == "" ]] && dy="0";
    [[ "$dz" == "" ]] && dz="0";

    echo "Moving object by x: $dx y: $dy z: $dz";

    tmpfile=".tmpr_$RANDOM";
    ./obj_move.sh ./.tmp.obj $dx $dy $dz > "$tmpfile";
    mv $tmpfile ./.tmp.obj;
done;
