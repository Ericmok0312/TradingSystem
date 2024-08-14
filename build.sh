#!/bin/bash

# Navigate to WebServer directory and start the server in a new terminal
current_directory=$(pwd)

echo "Select a command to run:"
echo "1) start c++ core only"
echo "2) run Whole"


read -p "Enter your choice (1-2): " choice



case $choice in
1)
gnome-terminal -- bash -c "cd \"$current_directory\" && make && ./test; exec bash"
;;
2)
gnome-terminal -- bash -c "cd \"$current_directory\"/WebServer && npm run start"
gnome-terminal -- bash -c "cd "$current_directory" && make && ./test; exec bash"
gnome-terminal -- bash -c "cd \"$current_directory\"/Web && npm run start"
;;

*)
echo "Invalid choice. Please select a number between 1 and 4."
;;
esac