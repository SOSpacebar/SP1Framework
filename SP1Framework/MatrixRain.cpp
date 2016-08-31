#include "MatrixHead.h"
#include "Framework\console.h"
#include <vector>

extern Console g_Console;
extern std::vector<Matrix>matrix;

COORD drawLocationMatrix;
char CharValue;
int offsetDelay = 0;

Matrix::Matrix() {

	// The initial seed value of the object
	srand(static_cast<unsigned int>(getpid()) ^ static_cast<unsigned int>(clock()) ^ static_cast<unsigned int>(time(NULL)));

	// Default constructor (no arguments)
	setDefault(true);

	// Default state for 'matrix lines'
	setErase(false);

	// 80 wide, 25 tall
	setPosition((rand() % 120 + 0), (rand() % 40 + 0));

	// Based on position Y
	setLength((rand() % (getPosition().Y + 1) + 0));

	// Speed of each letter being displayed
	setSpeed((rand() % 50 + 50), (rand() % 100 + 100), (rand() % 150 + 150));

	// Time between each iteration of a new color
	loopWhite_ = GetTickCount();
	loopLgreen_ = GetTickCount();
	loopDgreen_ = GetTickCount();
	lenCnt_ = 0;
};

Matrix::Matrix(const SMALL_RECT box) {

	// The initial seed value of the object
	srand(static_cast<unsigned int>(getpid()) ^ static_cast<unsigned int>(clock()) ^ static_cast<unsigned int>(time(NULL)));

	// Copy the argument to class member attribute
	setMatrixBox(box);

	// Default constructor (no arguments)
	setDefault(false);

	// Default state for 'matrix lines'
	setErase(false);

	// 80 wide, 25 tall
	setPosition((rand() % getMatrixBox().Right + getMatrixBox().Left), (rand() % getMatrixBox().Bottom + getMatrixBox().Top));

	// Based on position Y
	setLength((rand() % (getPosition().Y + 1) + 0));

	// Speed of each letter being displayed
	setSpeed((rand() % 50 + 50), (rand() % 100 + 100), (rand() % 150 + 150));

	// Time between each iteration of a new color
	loopWhite_ = GetTickCount();
	loopLgreen_ = GetTickCount();
	loopDgreen_ = GetTickCount();
	lenCnt_ = 0;
};

Matrix::Matrix(const unsigned int left, const unsigned int top,
	const unsigned int bottom, const unsigned int right) {

	// The initial seed value of the object
	srand(static_cast<unsigned int>(getpid()) ^ static_cast<unsigned int>(clock()) ^ static_cast<unsigned int>(time(NULL)));

	// Copy the argument to class member attribute
	setMatrixBox(top, bottom, left, right);

	// Default constructor (no arguments)
	setDefault(false);

	// Default state for 'matrix lines'
	setErase(false);

	// 80 wide, 25 tall
	setPosition((rand() % getMatrixBox().Right + getMatrixBox().Left), (rand() % getMatrixBox().Bottom + getMatrixBox().Top));

	// Based on position Y
	setLength((rand() % (getPosition().Y + 1) + 0));

	// Speed of each letter being displayed
	setSpeed((rand() % 50 + 50), (rand() % 100 + 100), (rand() % 150 + 150));

	// Time between each iteration of a new color
	loopWhite_ = GetTickCount();
	loopLgreen_ = GetTickCount();
	loopDgreen_ = GetTickCount();
	lenCnt_ = 0;
};

void Matrix::randLength() {
	setLength((rand() % (getPosition().Y + 1) + 5));
}

void Matrix::randSpeed() {
	setSpeed((rand() % 50 + 50), (rand() % 100 + 100), (rand() % 150 + 150));
	//setSpeed(0);
}

void Matrix::randPos() {
	if (getDefault()) {
		setPosition((rand() % 120 + 0), (rand() % 40 + 0));
	}
	else {
		setPosition((rand() % getMatrixBox().Right + getMatrixBox().Left),
			(rand() % getMatrixBox().Bottom + getMatrixBox().Top));
	}
}

void Matrix::display() {

	unsigned int whiteDelay = getSpeed(0);
	unsigned int greenDelay = getSpeed(1);
	unsigned int darkGreenDelay = getSpeed(2);

	//if (GetTickCount() >= (loopWhite_ + whiteDelay))
	//{

	if (offsetDelay <= 120)
	{
		loopWhite_ = GetTickCount();

		drawLocationMatrix.X = getPosition().X;
		drawLocationMatrix.Y = getPosition().Y;

		if (!getErase())
		{
			CharValue = (char)(rand() % 121 + 34);
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0F);
			drawLocationMatrix.Y--;
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0F);
			drawLocationMatrix.Y-=2;
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0F);
			drawLocationMatrix.Y -= (rand() % 3 + 1);
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0F);
			drawLocationMatrix.Y -= (rand() % 3 + 1);
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0F);
			drawLocationMatrix.Y -= (rand() % 3 + 1);
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0F);
			//drawLocationMatrix.Y -= (rand() % 3 + 1);
			//g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0F);
		}
		else
		{
			CharValue = (char)(rand() % 121 + 34);
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
			drawLocationMatrix.Y -= 2;
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
			drawLocationMatrix.Y-=2;
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
			drawLocationMatrix.Y -= 4;
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
			drawLocationMatrix.Y -= 2;
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
			drawLocationMatrix.Y --;
			g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
		}

		if (offsetDelay <= 80)
		{
			loopLgreen_ = GetTickCount();

			drawLocationMatrix.X = getPosition().X;
			drawLocationMatrix.Y = getPosition().Y;
			if (!getErase())
			{
				CharValue = (char)(rand() % 121 + 34);
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0A);
				drawLocationMatrix.Y--;
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0A);
				drawLocationMatrix.Y-=2;
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0A);
				drawLocationMatrix.Y -= (rand() % 3 + 1);
				//g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0A);
				//drawLocationMatrix.Y -= (rand() % 3 + 1);
				//g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0A);
				//drawLocationMatrix.Y -= (rand() % 3 + 1);
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0A);
				drawLocationMatrix.Y -= (rand() % 3 + 1);
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x0A);
			}
			else
			{
				CharValue = (char)(rand() % 121 + 34);
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
				drawLocationMatrix.Y -= 2;
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
				drawLocationMatrix.Y -= 2;
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
				drawLocationMatrix.Y -= 4;
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
				drawLocationMatrix.Y -= 2;
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
				drawLocationMatrix.Y--;
				g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
			}

			if (offsetDelay <= 30)
			{
				loopDgreen_ = GetTickCount();

				drawLocationMatrix.X = getPosition().X;
				drawLocationMatrix.Y = getPosition().Y;

				if (rand() % 2)
				{
					if (!getErase())
					{
						CharValue = (char)(rand() % 121 + 34);
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x02);
						drawLocationMatrix.Y--;
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x02);
						drawLocationMatrix.Y-=2;
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x02);
						drawLocationMatrix.Y -= (rand() % 3 + 1);
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x02);
						drawLocationMatrix.Y -= (rand() % 3 + 1);
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x02);
						drawLocationMatrix.Y -= (rand() % 3 + 1);
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x02);
						drawLocationMatrix.Y -= (rand() % 3 + 1);
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x02);
					}
					else
					{
						CharValue = (char)(rand() % 121 + 34);
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
						drawLocationMatrix.Y -= 2;
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
						drawLocationMatrix.Y -= 2;
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
						drawLocationMatrix.Y -= 4;
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
						drawLocationMatrix.Y -= 2;
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);
						drawLocationMatrix.Y--;
						g_Console.writeToBuffer(drawLocationMatrix, CharValue, 0x00);

					}
				}

				// Move the cursor down by one
				setPosition(getPosition().X, (getPosition().Y + 1));

				if (lenCnt_ >= getLength()) {
					randPos();
					randSpeed();
					randLength();

					lenCnt_ = 0; // reset counter
				}
				else { lenCnt_++; }
			}
		}
	}
	offsetDelay++;

	if (offsetDelay >= 120)
	{
		offsetDelay = 0;
	}
}

void Matrix::setDefault(const bool setting) {
	isDefault_ = setting;
}

bool Matrix::getDefault() {
	return isDefault_;
}

void Matrix::setErase(const bool setting) {
	erase_ = setting;
}

bool Matrix::getErase() {
	return erase_;
}

void Matrix::setSpeed(const unsigned int white, const unsigned int light_green, const unsigned int dark_green) {
	speed_[0] = white;
	speed_[1] = light_green;
	speed_[2] = dark_green;
}

unsigned int Matrix::getSpeed(const unsigned int color) {
	return speed_[color];
}

void Matrix::setLength(const unsigned int length) {
	length_ = length;
}

unsigned int Matrix::getLength() {
	return length_;
}

void Matrix::setPosition(const COORD position) {
	position_.X = position.X;
	position_.Y = position.Y;
}

void Matrix::setPosition(const unsigned int X, const unsigned int Y) {
	position_.X = X;
	position_.Y = Y;
}

COORD Matrix::getPosition() {
	return position_;
}

void Matrix::setMatrixBox(const SMALL_RECT matrixBox) {
	matrixBox_.Top = matrixBox.Top;
	matrixBox_.Bottom = matrixBox.Bottom;
	matrixBox_.Left = matrixBox.Left;
	matrixBox_.Right = matrixBox.Right;
}

void Matrix::setMatrixBox(const unsigned int top, const unsigned int bottom,
	const unsigned int left, const unsigned int right) {
	matrixBox_.Top = top;
	matrixBox_.Bottom = bottom;
	matrixBox_.Left = left;
	matrixBox_.Right = right;
}

SMALL_RECT Matrix::getMatrixBox() {
	return matrixBox_;
}


void initMatrix()
{

	for (int y = 0; y < 15; y++) {
		matrix.push_back(Matrix());
	}

	for (int z = 0; z < 5; z++) {
		matrix.push_back(Matrix()); matrix.at(z).setErase(true);
	}
}
void drawMatrix()
{
	for (int x = 0; x < matrix.size(); x++) {
		matrix.at(x).display();
	}
}