#!/bin/bash
#Компилируем все исходники до обьектных модулей
cd src
for file in `find -type f -name "*.c"`;
do
	gcc -fPIC $file -c
done
cd ..
#Формируем строку с именями всех модулей
listf=""
for file in `find ./src -name "*.o"`;
do
	listf="$listf $file"
done
#Сибираем динамическую библиотеку 
gcc -shared  -o libcalc.so $listf
mv libcalc.so ./lib/
#Компилируем сам программу и запускаем
gcc main.c -o main -ldl
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:./lib" ./main
exit 0