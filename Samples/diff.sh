#!/bin/bash
for di in $(ls -d */);
do
    countpy=`ls -1 $di*.py 2>/dev/null | wc -l`
    countcs=`ls -1 $di*.cs 2>/dev/null | wc -l`
    if [ $countcs != 0 ] && [ $countpy != 0 ]
    then
        for i in $di*.cs; 
        do 
            diff -u $i.opcodes ${i//cs/py}.opcodes > ${i//cs/opcodes.diff}; 
        done
    fi
done
