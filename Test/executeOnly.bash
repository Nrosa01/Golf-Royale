# Check if bin folder exist and also if bin/Golf-Royale exist
if [ -d "bin" ] && [ -f "bin/Golf-Client" ]; then
    ./bin/Golf-Client $@
else
    echo "bin/Golf-Client not found"
fi