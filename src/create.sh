#!/usr/bin/env sh

TERGET=$1
OSNAME=`uname -s`

if [ ${OSNAME} == 'Darwin' ]; then

    if [ ${TERGET} == 'libeyeballs' ]; then

    echo 'g++ -O3 -Wall -shared eyeballs.cpp -o libeyeballs.dylib'
    echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
    eval 'g++ -Wall -shared eyeballs.cpp -o libeyeballs.dylib'
    eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    elif [ ${TERGET} == 'debug' ]; then

    echo 'g++ -O3 -Wall -shared eyeballs.cpp -o libeyeballs.dylib -DDEBUG'
    echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
    eval 'g++ -Wall -shared eyeballs.cpp -o libeyeballs.dylib -DDEBUG'
    eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    fi

elif [ ${OSNAME} == 'Linux' ]; then

    if [ ${TERGET} == 'libeyeballs' ]; then

    echo 'g++ -O3 -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
    eval 'g++ -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    elif [ ${TERGET} == 'debug' ]; then

    echo 'g++ -O3 -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
    eval 'g++ -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    fi

elif [ ${OSNAME} == 'FreeBSD' ]; then

    if [ ${TERGET} == 'libeyeballs' ]; then

    echo 'g++ -O3 -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
    eval 'g++ -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    elif [ ${TERGET} == 'debug' ]; then

    echo 'g++ -O3 -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
    eval 'g++ -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
    eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    fi 

else 
    :
fi

