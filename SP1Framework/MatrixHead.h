#pragma once

#include <time.h>
#include <process.h>
#include <iostream>
#include "game.h"

class Matrix {
private:
	bool isDefault_; // Flag to signal using default "0 to 80" width, and "0 to 25" height
	bool erase_; // Flag to signal erasing of text (black matrix lines)

	// Timers for each color (no alternative)
	unsigned int loopWhite_;
	unsigned int loopLgreen_;
	unsigned int loopDgreen_;

	unsigned int speed_[3]; // Delay between printing a new line
	unsigned int length_; // Max. length before it quits
	unsigned int lenCnt_; // Counter for length

	COORD position_; // Position on the console

	SMALL_RECT matrixBox_; // Box for the "Matrix" to be in

public:
	Matrix::Matrix();
	Matrix::Matrix(const SMALL_RECT);
	Matrix::Matrix(const unsigned int, const unsigned int, const unsigned int, const unsigned int);

	void display();

	void setErase(const bool);
	bool getErase();

	void setSpeed(const unsigned int16, const unsigned int, const unsigned int);
	unsigned int getSpeed(const unsigned int);

private:
	void randLength();
	void randSpeed();
	void randPos();

	void setDefault(const bool);
	bool getDefault();

	void setLength(const unsigned int);
	unsigned int getLength();

	void setPosition(const COORD);
	void setPosition(const unsigned int, const unsigned int);
	COORD getPosition();

	void setMatrixBox(const SMALL_RECT);
	void setMatrixBox(const unsigned int, const unsigned int, const unsigned int, const unsigned int);
	SMALL_RECT getMatrixBox();
};

void drawMatrix();
void initMatrix();