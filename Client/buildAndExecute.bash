if [ "$1" = "-d" ]; then
    echo "Building with debug flag"
    make debug
    ./bin/linux/Golf-Royale-Debug ${@:2}
elif [ "$1" = "-r" ]; then
    echo "Building with release flag"
    make release
    ./bin/linux/Golf-Royale-Release ${@:2}
else
    echo "Building with debug flag"
    make debug
    ./bin/linux/Golf-Royale-Debug $@
fi