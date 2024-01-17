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

### **It may be not possible to use ev3dev on EV3, that we have in school**

Schools are often really strict on which software you can run where and ev3dev could fall into this category.
But because of the open-source and portable nature of the project it could be possible to allow this project, from my perspectivity.

*Authors: Antonín Šonka, Oliver Špaček*
