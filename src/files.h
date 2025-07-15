#pragma once

#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int readCSVToMap(const char *filename, int rows, int cols, int (*map)[cols]);
