#include "E.R.S.h"

void DrawCharic(bool flat, float move, float turn)
{
	glPushMatrix();
	glRotatef(turn, 0.0, 1.0, 0.0);
	if (flat)
	{
		glTranslatef(0.0f, -100.0f, 0.0f);
		glScalef(1.0f, 0.05f, 1.0f);
	}

		glPushMatrix();//赣府
		glTranslatef(0.0, 150.0, 0.0);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glutSolidSphere(20, 18, 18);
		glPopMatrix();

		glPushMatrix();//个烹
		glTranslatef(0.0, 80.0, 0.0);
		glScalef(1, 3, 0.5);
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCube(30);
		glPopMatrix();

		glPushMatrix();//迫 
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glLineWidth(10);
		glTranslatef(-10.0, 120.0, 0.0);
		glRotatef(move, 1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-40.0, -60.0, 0.0);
		glEnd();
		glPopMatrix();

		glPushMatrix();//迫
		glColor4f(0.0f, 1.0f, 1.0f, 0.0f);
		glLineWidth(10);
		glTranslatef(10.0, 120.0, 0.0);
		glRotatef(-move, 1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(40.0, -60.0, 0.0);
		glEnd();
		glPopMatrix();

		glPushMatrix();//促府
		glLineWidth(10);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-10.0, 30.0, 0.0);
		glRotatef(-move, 1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-10.0, -130.0, 0.0);
		glEnd();
		glPopMatrix();

		glPushMatrix();//促府
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(10);
		glTranslatef(10.0, 30.0, 0.0);
		glRotatef(move, 1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(10.0, -130.0, 0.0);
		glEnd();
		glPopMatrix();

	glPopMatrix();
}