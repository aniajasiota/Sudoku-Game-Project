# 🧩 Sudoku Game in C

## 🎯 Description
This project is a console-based Sudoku game written in C. The goal is to generate and solve Sudoku puzzles of various sizes. 
The program ensures that each generated board has a unique solution, providing a fun and logical challenge for players. 🧠
The game supports multiple grid sizes and difficulty levels, allowing for a customizable gameplay experience.

## ⚙️ Features
- Generate a valid Sudoku board with a unique solution ✅
- Choose board size: 4×4, 9×9, or 16×16 🔢
- Select difficulty level (affects number of starting hints) 🎚️
- Display the board clearly in the console 📋
- User-friendly menu: new game, board size, difficulty, instructions, exit 🧾
- Make moves by selecting a cell and entering a number ✍️
- Validate user input and check move correctness ✔️❌
- Ability to remove a value from a cell 🧼
- Save and load the game state 💾📂

## 🧮 Board Generation Algorithm
The Sudoku board is generated using a backtracking algorithm combined with randomization. This ensures that the final puzzle is valid and solvable with exactly one solution. 
The process includes:
- Generate a fully completed Sudoku board that follows all rules ✅
- Randomly remove some numbers according to the selected difficulty 🎲
- Ensure that the puzzle still has exactly one possible solution 🔐
- Use recursion and backtracking to try different values and revert if needed ↩️

  ## 👀 HOW IT LOOKS LIKE

  ### MENU
  ![sudoku_menu](https://github.com/user-attachments/assets/f94accb3-3114-4cef-af5f-ddf4fc13aa60)

  ### INSTRUCTION
  ![sudoku_instruction](https://github.com/user-attachments/assets/093cf6d4-f53d-4c8b-b2a7-18470ceecdbc)

  ### NEW GAME
  ![sudoku_new_game](https://github.com/user-attachments/assets/940e4718-1a28-47a5-8cd8-956660cbd5a7)

  ### SOLVED SUDOKU
  ![sudoku_finish](https://github.com/user-attachments/assets/b5151711-1e7e-4ed8-83b3-9b5aeb4d0433)

  ### SUDOKU EXIT
  ![sudoku_exit](https://github.com/user-attachments/assets/522c85b3-feb8-473a-8909-df71dc831d8e)


  ## 🤣 TIME FOR SOMETHING FUNNY
  ![For those of your friends who are extremely smart…](https://github.com/user-attachments/assets/d7124b82-30c7-42e5-b241-a57d19b4ab2d)


  ![git_meme](https://github.com/user-attachments/assets/8fbe920a-953a-44d9-8266-6dad59574fe8)




