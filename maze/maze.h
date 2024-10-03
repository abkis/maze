#pragma once

#include "resource.h"

// define some global variables here used for maze generation
const unsigned int MAX_WEIGHT = 10; // +/- weight of each block in maze
const unsigned int END_WEIGHT = 2 * MAX_WEIGHT;
const unsigned int REMOVE_WALLS = 20; // number of walls to remove after maze generated

// size when drawing maze
const unsigned int WALL_THICKNESS = 3;
const unsigned int SQUARE_SIZE = 20; // Size of each square in pixels
const unsigned int ROWS = 20;        // Number of rows in the grid
const unsigned int COLS = 20;        // Number of columns in the grid