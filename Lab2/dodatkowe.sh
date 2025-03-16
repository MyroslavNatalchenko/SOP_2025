#!/bin/bash

if [ -f results.txt ]
then
   rm results.txt
fi

for file in s[0-9][0-9][0-9][0-9][0-9]_z1.cpp
do
    index=$(echo "$file" | sed -E 's/_z1\.cpp//')  

    echo "Sprawdzanie dla studenta z indeksem: $index"
    echo "---- WYNIKI KODU ----"
    echo "---------------------"

    g++ "$file" -o Skompilowany_Program

    if [ $? -ne 0 ]
    then
        echo "Błąd kompilacji dla kodu od studenta $index"
        echo "$index - 0 (błąd kompilacji)" >> "results.txt"
        continue
    fi

    echo "TEST FOR 5, 10, 30:"
    for number in 5 10 30 
    do
        echo "INPUT: $number"
        echo "$number" | ./Skompilowany_Program
        echo "-------------------"
    done

    echo "Podaj ocenę ('kod', żeby zobaczyć kod):"
    read ocena

    if [ "$ocena" == "kod" ]
    then
        cat "$file"
        echo "Podaj ocenę:"
        read ocena
    fi

    echo "$index - $ocena" >> "results.txt"
done

echo "-----------------------"
echo "--- ZAPISANE WYNIKI ---"
echo "-----------------------"
cat results.txt
