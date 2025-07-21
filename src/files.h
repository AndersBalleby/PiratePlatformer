#pragma once

#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int extractNumber(const char *filename);
int compareFilePaths(const void *a, const void *b);

#define ROWS 11
#define COLS 60
int readCSVToMap(const char *filename, int map[ROWS][COLS]);
