# C Coursework
My program is somewhere between stage 6 and 7. The program generates a random-sized rectangular arena with a random number of obstacles and markers, and the program is always solvable.

## File structure
| File | Description |
| ----- | ----- |
| constants.h | Declarations of all global variables |
| background.c / background.h | Create and draw the background (arena) |
| robot.c / robot.h | Robot's drawing, movement and searching algorithm |
| main.c | Main code to run the program |

## Program explanation
In main.c, the program generates an arena and runs the robot searching algorithm quickly to check if the arena is solvable. This is done by checking whether the robot's collected markers are equal to the total number of generated markers when the robot is done searching the arena. If the arena is solvable, then the window and robot are drawn and the program is run for the user to see. If the arena is not solvable, the program generates a new arena and repeats the process until a solvable arena is generated.

The robot uses the depth-first search algorithm to search the entire arena. This is done using a recursive algorithm.


## Keys
| Arena | Robot's Memory |
| ----- | ----- |
| 0 = empty | 0 = not visited |
| 1 = wall | 1 = visited 
| 2 = obstacle |
| 3 = marker | 

## Compile
Command to compile program:
```
gcc main.c graphics.c background.c robot.c
```
OR
```
gcc *.c
```

## Run program
By default, the ```delay``` of the robot is set to **50** and ```show_path``` (boolean value which, if true, leaves a green trace wherever the robot moves) is **false**.

When running the program, you have the option to change these values in the command line. To set ```show_path``` to **false**, type **0**. To set it to **true**, type any **non-zero integer**.
### Unix
```
./a.out {delay} {show_path} | java -jar drawapp-4.0.jar
```
### Windows
```
./a.exe {delay} {show_path} | java -jar drawapp-4.0.jar
```
