# Check if bin folder exist and also if bin/Golf-Royale exist
if [ -d "bin" ] && [ -f "bin/Golf-Server" ]; then
    ./bin/Golf-Server
else
    echo "bin/Golf-Server not found"
fi