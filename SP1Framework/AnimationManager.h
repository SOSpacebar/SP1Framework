#ifndef _ANIMATIONMANAGER_H
#define _ANIMATIONMANAGER_H

struct FrameData
{
	char Frame[150][150];

	int height;

	int width;

	float frameTime;
};

void readAnimation(void);

#endif 