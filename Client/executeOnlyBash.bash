if [ "$1" = "-d" ]; then
    ./bin/Golf-Royale-Debug ${@:2}
elif [ "$1" = "-r" ]; then
    ./bin/Golf-Royale-Release ${@:2}
else
    ./bin/Golf-Royale-Debug $@
fi