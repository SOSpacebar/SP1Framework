#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H

#include <string>
#include <fstream>

struct FrameData
{
	char frameToLoad[50][150][150];

	int height;

	int width;

	float frameTime;
};

void readAnimation(void);
void drawAnimation(int keyFrame);
void setAnimation();

#endif 