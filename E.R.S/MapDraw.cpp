#include "E.R.S.h"

int trap;
float trapX, trapZ;

void DrawRoad(float width, float height)
{
	glBegin(GL_QUADS);
	glVertex3f(-(width / 2), -100.0f, -(height / 2));
	glVertex3f(-(width / 2), -100.0f, (height / 2));
	glVertex3f((width / 2), -100.0f, (height / 2));
	glVertex3f((width / 2), -100.0f, -(height / 2));
	glEnd();
}

void MapDraw(int points[], int seed, float width, float height, int trapSeed)
{
	glPushMatrix();
	glTranslatef(points[0], points[1], points[2]);
	if (seed >= 50)
	{
		glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
		DrawRoad(width, height);

			glPushMatrix();
			glColor4f((trapSeed / 100) == 1 ? 1.0 : 0.0, (trapSeed / 100) == 2 ? 1.0 : 0.0, (trapSeed / 100) == 3 ? 1.0 : 0.0, 1.0f);
			glTranslatef(-200.0 + (((trapSeed % 100) / 10)) * 100, -100.0f, -300.0 + ((trapSeed % 100) % 10) * (height / 10));
			glutSolidSphere(20.0f, 15, 15);
			glPopMatrix();
			trap = trapSeed / 100;
			trapX = -200.0 + (((trapSeed % 100) / 10)) * 100;
			trapZ = -300.0 + ((trapSeed % 100) % 10) * (height / 10);

			GetTrap(trapX, trapZ, trap);

		glPopMatrix();

	} else {
		glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
		glTranslatef(200.0f, 0.0f, 0.0f);
		glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
		DrawRoad(width, height);

		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(-400.0f, 0.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
		DrawRoad(width, height);
		glPopMatrix();
	}
}