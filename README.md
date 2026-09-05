# Robot Arena Searching Algorithm

The program generates a random-sized rectangular arena with a random number of obstacles and markers, and the program is always solvable.

## File structure

| File                        | Description                                       |
| --------------------------- | ------------------------------------------------- |
| constants.h                 | Declarations of all global variables              |
| background.c / background.h | Create and draw the background (arena)            |
| robot.c / robot.h           | Robot's drawing, movement and searching algorithm |
| main.c                      | Main code to run the program                      |

## Program explanation

In main.c, the program generates an arena and runs the robot searching algorithm quickly to check if the arena is solvable. This is done by checking whether the robot's collected markers are equal to the total number of generated markers when the robot is done searching the arena. If the arena is solvable, then the window and robot are drawn and the program is run for the user to see. If the arena is not solvable, the program generates a new arena and repeats the process until a solvable arena is generated.

The robot uses the depth-first search algorithm to search the entire arena. This is done using a recursive algorithm.

## Keys

| Arena        | Robot's Memory  |
| ------------ | --------------- |
| 0 = empty    | 0 = not visited |
| 1 = wall     | 1 = visited     |
| 2 = obstacle |
| 3 = marker   |

## Compile

### Unix

```bash
gcc -Iinclude src/*.c -o robot.out
```

### Windows

```bash
gcc -Iinclude src\*.c -o robot.exe
```

## Run program

### Flags

| Flag      | Default   | Behaviour                                              |
| --------- | --------- | ------------------------------------------------------ |
| delay     | 50        | Changes speed of robot                                 |
| show_path | 0 (false) | Set to 1 to leave green trace wherever the robot moves |
| size      | 10        | Size of each square in grid                            |

When running the program, you have the option to change these values in the command line, as shown below.

### Unix

```bash
./robot.out {delay} {show_path} {size} | java -jar lib/drawapp-4.0.jar
```

### Windows

```bash
.\robot.exe {delay} {show_path} {size} | java -jar lib\drawapp-4.0.jar
```
