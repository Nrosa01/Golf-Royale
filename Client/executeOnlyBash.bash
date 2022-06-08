if [ "$1" = "-d" ]; then
    ./bin/linux/Golf-Royale-Debug ${@:2}
elif [ "$1" = "-r" ]; then
    ./bin/linux/Golf-Royale-Release ${@:2}
else
    ./bin/linux/Golf-Royale-Debug $@
fi