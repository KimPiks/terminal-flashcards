# terminal-flashcards

Flashcards for learning in the terminal.

<div style="text-align: center;">
  <img width="100%" src="../main/ui1.png?raw=true">
</div>

## Database schema
<div style="text-align: center;">
  <img width="100%" src="../main/database-entity-relationship-diagram.png?raw=true">
</div>

## Flashcards file format
First line is the title of the flashcard set.<br>
Each question is followed by a # and the correct answer is prefixed with a +.<br>
Incorrect answers are prefixed with a -.

### Example file
```
Computer Architecture
#What is the size of the EAX register?
-8-bit
-16-bit
+32-bit
-64 bit
#What does the ADD command do?
+adds
-subtracts
-multiplies
-divides
```

## Installation
1. Clone the repository.
```
git clone https://github.com/KimPiks/terminal-flashcards.git
```

2. Go to the project directory.
```
cd terminal-flashcards
```

3. Build the project.
```
cmake .
make
```

4. Run the program.
```
./terminal-flashcards
```

or run the exe file if you are on Windows.

## Usage
1. Create a flashcards file in the format described above.
2. In the main menu, select "Import Deck" and enter the path to the flashcards file.
3. Use "Show Decks" option to select the deck you want to study.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.