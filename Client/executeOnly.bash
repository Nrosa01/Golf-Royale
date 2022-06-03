# Check if bin folder exist and also if bin/Golf-Royale exist
if [ -d "bin" ] && [ -f "bin/Golf-Royale" ]; then
    ./bin/Golf-Royale $@
else
    echo "bin/Golf-Royale not found"
fi