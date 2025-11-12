#pragma once
// enumerate directions for easier indexing
enum DIR
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

// constants for displaying grid

const static int pixels_per_cell = 30;
const static int grid_width = 20;
const static int grid_height = 20;

// weighting constants for grid search
const static float K1 = 0.5;
const static float K2 = 0.5;

// weighting constant for seen cells
const static float SEEN = 100;
const static float VISITED = 100;