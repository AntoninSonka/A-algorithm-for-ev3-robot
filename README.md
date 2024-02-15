# A* algorithm for EV3 robot

This is a school project for robotics.
We choose to create a robot that will navigate through a maze on x by y grid.
The robot will be using **A* algorithm** which we thaught woucd be best suited for this project.
Robot will probably have only **4 directions**.

## Modifying the code

Is it possible to modify the code by tweaking enum values in aStar.h.
Note that when changing size of the grid, you have to also change size of 2D boolean array in gridSetup function.

## Minor problems

### **Only 4 directions**

    0 0 0
    X X 2
    0 1 0

Robot wants to get from 1 to 2. This would be possible in theory, but in real life probably boxes will be used to block tiles *(walls in code)*.
Those boxes would prevent robot from going diagonaly.
If we will think of any other solution, we will probably adapt code and other things to suit that scenario.

### **Robot calibration**

Potentional problem could be calibration of the robot, because right now we didn't folus in it at all.

## Updates

### **Simulation of the robot moving from one place to another**

The program now behaves like a robot. For it to descover tile, it must first get there. It does by using A* algorithm, like before.
Now we really only have to add the raw movement of the robot and everything is set.

*Authors: Antonín Šonka, Oliver Špaček*
