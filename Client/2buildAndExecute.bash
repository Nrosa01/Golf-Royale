# build and execute bash
bash updateNet.bash
args=$@
make
./bin/Golf-Royale $args &
./bin/Golf-Royale $args &