#include "E.R.S.h"

float jigsawX[4][4];
float jigsawY[4][4];

bool takoyaki[6][6];

float tempmx, tempmy;
float tempRect[2];

int flagGameNum;
int selectRect;

int WinWid, WinHigh;

bool flagMove = false;

int takoyakiSeed;
int takoBonus;

bool takoSurren = false;

void GenGame()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			jigsawX[i][j] = rand() % 600 - 300;
			jigsawY[i][j] = rand() % 600 - 300;
		}
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			takoyaki[i][j] = rand() % 2;
	takoBonus = 2;
}

GLubyte *LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		return NULL;
	}

	if (header.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit(0);
		return NULL;
	}

	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}

void LoadBitMap()
{
	glGenTextures(4, texture);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	pBytes = LoadDIBitmap("Jigsaw1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	pBytes = LoadDIBitmap("Jigsaw2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	pBytes = LoadDIBitmap("Jigsaw3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	pBytes = LoadDIBitmap("Jigsaw4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

void DrawQuads(float posX, float posY, float codeX, float codeY)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0 + (codeX * 0.25), 1.0 - (codeY * 0.25));
	glVertex2f(posX - 50.0, posY + 50.0);
	glTexCoord2f(0.0 + (codeX * 0.25), 0.75 - (codeY * 0.25));
	glVertex2f(posX - 50.0, posY - 50.0);
	glTexCoord2f(0.25 + (codeX * 0.25), 0.75 - (codeY * 0.25));
	glVertex2f(posX + 50.0, posY - 50.0);
	glTexCoord2f(0.25 + (codeX * 0.25), 1.0 - (codeY * 0.25));
	glVertex2f(posX + 50.0, posY + 50.0);
	glEnd();
}

void LoadWinSize(int &WinW, int &WinH)
{
	WinWid = WinW;
	WinHigh = WinH;
}

bool InRect(int mx, int my, int tx, int ty, int slop)
{
	return (mx >= tx - slop && mx <= tx + slop && my >= ty - slop && my <= ty + slop) ? true : false;
}

void Minigame(int num, int &flagCount, bool &flag, int seed)
{
	bool game = true;
	bool clear = false;
	int flagClear = 0;

	switch (num)
	{
	case 0:
		flagGameNum = 1;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-400.0, 400.0, -400.0, 400.0, 400.0, -400.0);
		gluLookAt(0.0, 0.0, 200, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLineWidth(2.0f);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-200.0f, 200.0f);
		glVertex2f(-200.0f, -200.0f);
		glVertex2f(200.0f, -200.0f);
		glVertex2f(200.0f, 200.0f);
		glVertex2f(-200.0f, 200.0f);
		glEnd();

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texture[seed]);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				DrawQuads(jigsawX[i][j], jigsawY[i][j], (float)i, (float)j);
		}

		glDisable(GL_TEXTURE_2D);

		for (int i = 0; i < 16; i++)
		{
			if (InRect(jigsawX[i / 4][i % 4], jigsawY[i / 4][i % 4], -150 + (100 * (i / 4)), 150 - (100 * (i % 4)), 10))
				flagClear++;
			else flagClear--;
		}

		if (flagClear >= 16)
		{
			clear = true;
			game = false;
		}
		break;
	case 1:
		flagGameNum = 2;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-400.0, 400.0, -400.0, 400.0, 400.0, -400.0);
		gluLookAt(0.0, 0.0, 200, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		for (int i = 0; i < seed * seed; i++)
		{
			glPushMatrix();
			if (takoyaki[i / seed][i % seed])
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			else glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
			glTranslatef(-((seed - 1) * 50) + (100 * (i / seed)), -((seed - 1) * 50) + (100 * (i % seed)), 0.0f);
			glutSolidSphere(40.0f, 20, 20);
			glPopMatrix();
		}

		takoyakiSeed = seed;

		glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(300.0f, -300.0f);
		glVertex2f(350.0f, -300.0f);
		glVertex2f(350.0f, -350.0f);
		glVertex2f(300.0f, -350.0f);
		glEnd();

		for (int i = 0; i < takoBonus; i++)
		{
			glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
			glBegin(GL_QUADS);
			glVertex2f(-340.0 + (50.0 * i), 340.0f);
			glVertex2f(-340.0 + (50.0 * i), 300.0f);
			glVertex2f(-300.0 + (50.0 * i), 300.0f);
			glVertex2f(-300.0 + (50.0 * i), 340.0f);
			glEnd();
		}

		for (int i = 0; i < seed * seed; i++)
		{
			if (takoyaki[i / seed][i % seed])
				flagClear++;
			else flagClear--;
		}

		if (flagClear >= seed * seed || flagClear <= -(seed * seed))
		{
			clear = true;
			game = false;
		}

		if (takoSurren)
		{
			game = false;
			takoSurren = false;
		}
		break;
	case 2:
		flagGameNum = 3;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-400.0, 400.0, -400.0, 400.0, 400.0, -400.0);
		gluLookAt(0.0, 0.0, 200, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		break;
	}

	if (!game && !flagMove)
	{
		if (clear)
		{
			flagCount = 500;
			flag = false;
		} else {
			flagCount = 400;
			flag = false;
		}
		glViewport(0, 0, WinWid, WinHigh);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(120.0, WinWid / WinHigh, 1, 1000);
		gluLookAt(50.0, 150.0, 300.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}

GLvoid MouseMini(int button, int state, int x, int y)
{
	switch (flagGameNum)
	{
	case 1:
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			for (int i = 0; i < 16; i++)
			{
				if (InRect((x * 800 / WinWid) - 400, 400 - (y * 800 / WinHigh), jigsawX[i / 4][i % 4], jigsawY[i / 4][i % 4], 50))
				{
					selectRect = i;
					tempmx = (x * 800 / WinWid) - 400;
					tempmy = 400 - (y * 800 / WinHigh);
					tempRect[0] = jigsawX[i / 4][i % 4];
					tempRect[1] = jigsawY[i / 4][i % 4];
					flagMove = true;
					break;
				}
			}
		}
		else if (state == GLUT_UP)
			flagMove = false;
		break;
	case 2:
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			for (int i = 0; i < takoyakiSeed * takoyakiSeed; i++)
			{
				if (InRect((x * 800 / WinWid) - 400, 400 - (y * 800 / WinHigh),
					-((takoyakiSeed - 1) * 50) + (100 * (i / takoyakiSeed)), -((takoyakiSeed - 1) * 50) + (100 * (i % takoyakiSeed)), 50))
				{
					takoyaki[i / takoyakiSeed][i % takoyakiSeed] = !takoyaki[i / takoyakiSeed][i % takoyakiSeed];
					if (i / takoyakiSeed > 0)
						takoyaki[(i / takoyakiSeed) - 1][i % takoyakiSeed] = !takoyaki[(i / takoyakiSeed) - 1][i % takoyakiSeed];
					if (i / takoyakiSeed < takoyakiSeed - 1)
						takoyaki[(i / takoyakiSeed) + 1][i % takoyakiSeed] = !takoyaki[(i / takoyakiSeed) + 1][i % takoyakiSeed];
					if (i % takoyakiSeed > 0)
						takoyaki[i / takoyakiSeed][(i % takoyakiSeed) - 1] = !takoyaki[i / takoyakiSeed][(i % takoyakiSeed) - 1];
					if (i % takoyakiSeed < takoyakiSeed - 1)
						takoyaki[i / takoyakiSeed][(i % takoyakiSeed) + 1] = !takoyaki[i / takoyakiSeed][(i % takoyakiSeed) + 1];
					break;
				}
				if (InRect((x * 800 / WinWid) - 400, 400 - (y * 800 / WinHigh), 325.0, -325.0, 25))
					takoSurren = true;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			for (int i = 0; i < takoyakiSeed * takoyakiSeed; i++)
			{
				if (InRect((x * 800 / WinWid) - 400, 400 - (y * 800 / WinHigh),
					-((takoyakiSeed - 1) * 50) + (100 * (i / takoyakiSeed)), -((takoyakiSeed - 1) * 50) + (100 * (i % takoyakiSeed)), 50)
					&& takoBonus > 0)
				{
					takoyaki[i / takoyakiSeed][i % takoyakiSeed] = !takoyaki[i / takoyakiSeed][i % takoyakiSeed];
					takoBonus--;
					break;
				}
			}
		}
		break;
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	if (!flagMove) return;

	int mx = (x * 800 / WinWid) - 400;
	int my = 400 - (y * 800 / WinHigh);

	jigsawX[selectRect / 4][selectRect % 4] = tempRect[0] + (mx - tempmx);
	jigsawY[selectRect / 4][selectRect % 4] = tempRect[1] + (my - tempmy);

	glutPostRedisplay();
}