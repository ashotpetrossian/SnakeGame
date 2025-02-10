# SnakeGame

This is a classic Snake game built using SFML (Simple and Fast Multimedia Library) in C++.
The game lets you control a snake that grows in size as it eats food.
The objective is to avoid hitting walls or the snake's own body while trying to get the highest possible score.

Features
Dynamic Difficulty: Choose from three levels of difficulty: Easy, Medium, and Hard.
Growing Snake: The snake grows in length every time it eats food.
Collision Detection: The game ends if the snake collides with a wall or its own body.
Game Restart Option: After losing, the player can choose to play again or exit.

Controls
Arrow Keys: Use the arrow keys (Up, Down, Left, Right) to control the direction of the snake.

How to Play
Start the game and choose the difficulty level (Easy, Medium, or Hard).
Control the snake using the arrow keys and try to eat the food to grow.
Avoid hitting the walls or the snake's own body. If you collide, the game ends.
After losing, you can choose to play again.

To run this game, you'll need the SFML DLL files. They should be placed in the same directory as the executable file or in a directory accessible via your system's PATH variable. You can download the appropriate SFML version from SFML downloads.

Prerequisites
C++17 
SFML library (Simple and Fast Multimedia Library).
CMake (for building the project).

Installation

For Linux/MacOS
Clone this repository:
git clone https://github.com/ashotpetrossian/SnakeGame.git
cd SnakeGame
mkdir build
cd build
cmake ..
make

Place the SFML DLL files (downloaded from SFML's website) in the same directory as the executable or set them in your PATH.

Run the game:
./SnakeGame


For Windows
Clone this repository:
git clone https://github.com/ashotpetrossian/SnakeGame.git

Download and install SFML for Windows from SFML downloads. Extract the SFML folder to a location of your choice.

Open CMake GUI and set the following:

Where is the source code: Point to the folder where you have cloned the SnakeGame repository.
Where to build the binaries: Choose a folder where you want the project to be built (e.g., build/ inside the project directory).
Click Configure. Select Visual Studio 16 2019 or your appropriate version of Visual Studio. Click Generate.

Open the generated .sln file in Visual Studio.

In Visual Studio, set the build configuration to "Release" (or "Debug" depending on your preference).

Build the project by clicking on Build > Build Solution.

After the build finishes, go to the output directory (e.g., bin/Release) where the executable was created.

Copy the SFML DLL files (from the SFML\bin folder you downloaded) into the same directory as the executable.

Run the game:
SnakeGame.exe

License
This project is licensed under the MIT License - see the LICENSE file for details.
