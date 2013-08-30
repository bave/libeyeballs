#!/usr/bin/env sh

TERGET=$1
OSNAME=`uname -s`

if [ ${OSNAME} = 'Darwin' ]; then

    if [ ${TERGET} = 'libeyeballs' ]; then

        echo 'g++ -Wall -O3 -dynamiclib eyeballs.cpp -o libeyeballs.dylib'
        echo 'g++ -Wall -o test test.cpp -L./ -leyeballs'
        eval 'g++ -Wall -O3 -dynamiclib eyeballs.cpp -o libeyeballs.dylib'
        eval 'g++ -Wall -o test test.cpp -L./ -leyeballs'

    elif [ ${TERGET} = 'debug' ]; then

        echo 'g++ -g -Wall -dynamiclib eyeballs.cpp -o libeyeballs.dylib -DDEBUG'
        echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
        eval 'g++ -g -Wall -dynamiclib eyeballs.cpp -o libeyeballs.dylib -DDEBUG'
        eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    elif [ ${TERGET} = 'install' ]; then

        echo 'pleas run following command'
        echo 'cp ./eyeballs.hpp /usr/local/include/'
        echo 'cp ./libeyeballs.so  /usr/local/lib/'

    elif [ ${TERGET} = 'deinstall' ]; then

        echo 'pleas run following command'
        echo 'rm -f /usr/local/include/libeyeballs.hpp'
        echo 'rm -f /usr/local/lib/libeyeballs.so'

    fi

elif [ ${OSNAME} = 'Linux' ]; then

    if [ ${TERGET} = 'libeyeballs' ]; then

        echo 'g++ -Wall -O3 -shared eyeballs.cpp -o libeyeballs.so -fPIC'
        echo 'g++ -Wall -o test test.cpp -L./ -leyeballs'
        eval 'g++ -Wall -O3 -shared eyeballs.cpp -o libeyeballs.so -fPIC'
        eval 'g++ -Wall -o test test.cpp -L./ -leyeballs'

    elif [ ${TERGET} = 'debug' ]; then

        echo 'g++ -g -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
        echo 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'
        eval 'g++ -g -Wall -shared eyeballs.cpp -o libeyeballs.so -fPIC'
        eval 'g++ -g -Wall -o test test.cpp -L./ -leyeballs'

    elif [ ${TERGET} = 'install' ]; then

        cp ./eyeballs.hpp /usr/local/include/
        cp ./libeyeballs.so  /usr/local/lib/
        nice ldconfig
        echo 'install complete.'

    elif [ ${TERGET} = 'deinstall' ]; then

        rm -f /usr/local/include/eyeballs.hpp
        rm -f /usr/local/lib/libeyeballs.so
        nice ldconfig
        echo 'deinstall complete.'

    fi

elif [ ${OSNAME} = 'FreeBSD' ]; then

    :

else 
    :
fi

