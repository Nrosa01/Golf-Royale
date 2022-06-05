if [ "$1" = "-d" ]; then
    ./bin/Golf-Server-Debug ${@:2}
elif [ "$1" = "-r" ]; then
    ./bin/Golf-Server-Release ${@:2}
else
    ./bin/Golf-Server-Debug $@
fi