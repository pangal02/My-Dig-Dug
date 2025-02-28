# My-Dig-Dug 🎮

My-Dig-Dug is a console-based game inspired by the classic arcade game Dig Dug. The player digs through the ground, avoids obstacles, and collects diamonds to progress through the levels.

## 📌 This implementation was created as university assigment.

## 📖 Περιεχόμενα
- [Installation](#installation)
- [Usage](#usage)
- [Game Rules](#game-rules)
- [Functions Overview](#functions-overview)
- [Contributing](#contributing)
- [License](#license)

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/pangal02/My-Dig-Dug.git
2. Navigate to the project directory:
    cd My-Dig-Dug

3. Compile the code:
   gcc Galiotos-DigDug.c -o digdug

**Usage**
Run the executable:
./digdug

**Game Rules**

- Choose the difficulty level: Easy, Medium, or Hard.
- Enter the dimensions of the game area (N x M) where both N and M should be at least 5.
- Dig through the soil, avoid obstacles, and collect diamonds.
- Use the following commands to move:
  U or u for Up
  D or d for Down
  L or l for Left
  R or r for Right
  X or x to Exit the game
- Collect all diamonds to advance to the next level. The game ends if you hit an obstacle or fall from a height.

**Functions Overview**

- obs_table: Generates the game table with obstacles.
- soil: Initializes the game table with soil.
- getMemory: Allocates memory for the game table.
- Dig_Doug: Places the Dig Dug character on the game table.
- diam: Places diamonds on the game table.
- path: Moves the Dig Dug character based on user commands.
- print_table: Prints the current state of the game table.
- Random: Generates a random number.
- found_x and found_y: Find the current position of Dig Dug on the game table.
- down: Handles the falling logic for Dig Dug.
