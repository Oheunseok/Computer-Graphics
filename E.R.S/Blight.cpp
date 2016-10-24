#include "E.R.S.h"

float ambFirLight = 0.3, difFirLight = 0.1, speFirLight = 0.0;
float ambSecLight = 0.7, difSecLight = 0.9, speSecLight = 0.9;
float ambTirLight = 1.0, difTirLight = 1.0, speTirLight = 1.0;

GLfloat ambientBLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat ambientFirLight[] = { ambFirLight, ambFirLight, ambFirLight, 1.0f };
GLfloat diffuseFirLight[] = { difFirLight, difFirLight, difFirLight, 1.0f };
GLfloat specularFirLight[] = { speFirLight, speFirLight, speFirLight, 1.0f };
GLfloat lightFirPos[] = { 100.0f, -100.0f, -300.0f, 0.0 };

GLfloat ambientSecLight[] = { ambSecLight, ambSecLight, ambSecLight, 1.0f };
GLfloat diffuseSecLight[] = { difSecLight, difSecLight, difSecLight, 1.0f };
GLfloat specularSecLight[] = { speSecLight, speSecLight, speSecLight, 1.0f };
GLfloat lightSecPos[] = { 0.0f, 0.0f, -50.0f, 1.0 };

GLfloat ambientTirLight[] = { ambTirLight, ambTirLight, ambTirLight, 1.0f };
GLfloat diffuseTirLight[] = { difTirLight, difTirLight, difTirLight, 1.0f };
GLfloat specularTirLight[] = { speTirLight, speTirLight, speTirLight, 1.0f };
GLfloat lightTirPos[] = { 0.0f, 0.0f, 0.0f, 1.0 };

void GetLight()
{
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientBLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientFirLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseFirLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularFirLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightFirPos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientSecLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseSecLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularSecLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightSecPos);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientTirLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseTirLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularTirLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightTirPos);
}