# calls bash buildAndExecute.bash & $1 times

# check if first argument is a number
if [[ $1 == ?(-)+([0-9]) ]]; then
    # if it is a number, then it is a number of times to call buildAndExecute.bash
    echo "Number of times to call buildAndExecute.bash: $1"
    for ((i=0; i<$1; i++)); do
        echo "Calling buildAndExecute.bash $i"
        bash executeOnlyBash.bash ${@:2} &
    done
else
    # if it is not a number, then it is a command to be executed
    echo "Calling buildAndExecute.bash with command: $@"
    bash executeOnlyBash.bash $@
fi