#include "E.R.S.h"

void LoadStartBit();
void MapFuntion1();
void MapFuntion2();

static int chaXpos;
static int chaZpos;

static int stoneXpos;
static int stoneYpos;
static int stoneZpos;

static int mapXpos;
static int mapYpos;
static int mapZpos;

static float move;
static float stoneAngle;
static float trapPoint[2];

static int imsiMapArray[3];
static int imsiSeed;
static int mapPoint[4][3];				//맵 좌표 저장 배열
static int seed[4];					//시드값 저장 배열
static int trapSeed[4];
static int imsiTrapSeed;
static int flagTrap;

static int gameseed;
static int chaTurn;
static int stoneTurn;

static bool startERS;
static bool flagMove;
static bool flagTurn;
static bool flagFlat;

void main(int argc, char *argv[])
{

	//초기화 함수들
	srand((unsigned)time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(50, 50); // 윈도우의 위치지정 
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정 
	glutCreateWindow("E.R.S"); // 윈도우 생성 (윈도우 이름) 
	glutMouseFunc(MouseMini);
	glutMotionFunc(Motion);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수의 지정 
	glutSpecialFunc(SpecialKeyboard);
	glutKeyboardFunc(Keyboard);
	Clear();		//변수 초기화 함수

	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glViewport(0, 0, WinW, WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!flagGame && startERS)
	{
		gluPerspective(120.0, WinW / WinH, 1, 800);
		if (flagTurn)
			gluLookAt(chaXpos, 0.0, chaZpos + 200.0, chaXpos, 0.0, chaZpos, 0.0, 1.0, 0.0);
		else
			gluLookAt(chaXpos + 50.0, 150.0, chaZpos + 300.0, chaXpos, 0.0, chaZpos, 0.0, 1.0, 0.0);
	}
	else {
		glOrtho(-400.0, 400.0, -400.0, 400.0, 400.0, -400.0);
		gluLookAt(0.0, 0.0, 200, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	if (startERS)
	{
		if (!flagGame)
		{
			glDisable(GL_LIGHT1);
			glEnable(GL_LIGHT0);
			glPushMatrix();
			glTranslatef(mapXpos, mapYpos, mapZpos);

			//길 그리기
			for (int i = 0; i < 4; i++)
			{
				MapDraw(mapPoint[i], seed[i], 300.0, 600.0, trapSeed[i]);
				if (InRect(chaXpos, chaZpos, trapPoint[0] + mapPoint[i][0], trapPoint[1] + mapPoint[i][2], 20) && flagTrap == 2)
				{
					flagMinigame = 1;
					gameseed = rand() % 4;
					GenGame();
					glutTimerFunc(20, Timerfunction, 1);
					trapSeed[i] = (((rand() % 3) + 1) * 100)
						+ (((rand() % 3) + 1) * 10)
						+ (rand() % 10);
					break;
				}
				else if (InRect(chaXpos, chaZpos, trapPoint[0] + mapPoint[i][0], trapPoint[1] + mapPoint[i][2], 20) && flagTrap == 3) {
					flagMinigame = 101;
					gameseed = rand() % 3 + 4;
					GenGame();
					glutTimerFunc(20, Timerfunction, 1);
					trapSeed[i] = (((rand() % 3) + 1) * 100)
						+ (((rand() % 3) + 1) * 10)
						+ (rand() % 10);
					break;
				}
			}
			if (imsiSeed != 0)
				MapDraw(imsiMapArray, imsiSeed, 300.0, 600.0, imsiTrapSeed);

			glPopMatrix();

			glPushMatrix();
			glTranslatef(chaXpos, 0, chaZpos);
			if (chaTurn == 1)
				DrawCharic(flagFlat, move, 45);
			else if (chaTurn == 2)
				DrawCharic(flagFlat, move, -45);
			else DrawCharic(flagFlat, move, 0);
			glPopMatrix();

			if (flagTurn)
			{
				glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
				glBegin(GL_QUADS);
				glVertex3f(chaXpos + 200.0, 300.0f, chaZpos + 0.0);
				glVertex3f(chaXpos + 200.0, 250.0f, chaZpos + 0.0);
				glVertex3f(chaXpos + 250.0, 250.0f, chaZpos + 0.0);
				glVertex3f(chaXpos + 250.0, 300.0f, chaZpos + 0.0);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(chaXpos + 249.0, 330.0f, chaZpos + 0.0);
				glVertex3f(chaXpos + 249.0, 220.0f, chaZpos + 0.0);
				glVertex3f(chaXpos + 300.0, 275.0f, chaZpos + 0.0);
				glEnd();

				glBegin(GL_QUADS);
				glVertex3f(chaXpos - 200.0, 300.0f, chaZpos + 0.0);
				glVertex3f(chaXpos - 200.0, 250.0f, chaZpos + 0.0);
				glVertex3f(chaXpos - 250.0, 250.0f, chaZpos + 0.0);
				glVertex3f(chaXpos - 250.0, 300.0f, chaZpos + 0.0);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(chaXpos - 249.0, 330.0f, chaZpos + 0.0);
				glVertex3f(chaXpos - 249.0, 220.0f, chaZpos + 0.0);
				glVertex3f(chaXpos - 300.0, 275.0f, chaZpos + 0.0);
				glEnd();
			}

			glPushMatrix();
			glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
			glTranslatef(stoneXpos, stoneYpos, stoneZpos);
			glRotatef(stoneAngle, 1.0f, 0.0f, 0.0f);
			glutSolidSphere(120.0f, 50, 50);
			glPopMatrix();
		}
		else {
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			Minigame((flagMinigame / 100) - 1, flagMinigame, flagGame, gameseed);
			if (flagMinigame == 400)
			{
				flagMinigame = 0;
				speedStone += 0.2;
				glutTimerFunc(20, Timerfunction, 2);
				glutTimerFunc(20, Timerfunction, 3);
				for (int i = 0; i < 4; i++)
				{
					trapSeed[i] = (((rand() % 3) + 1) * 100)
						+ (((rand() % 3) + 1) * 10)
						+ (rand() % 10);
				}
			}
			else if (flagMinigame == 500)
			{
				flagMinigame = 0;
				speedStone -= 0.2;
				if (speedStone <= 1)
					speedStone = 1;
				glutTimerFunc(20, Timerfunction, 2);
				glutTimerFunc(20, Timerfunction, 3);
				for (int i = 0; i < 4; i++)
				{
					trapSeed[i] = (((rand() % 3) + 1) * 100)
						+ (((rand() % 3) + 1) * 10)
						+ (rand() % 10);
				}
			}
		}
	} else {
		glEnable(GL_LIGHT2);
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texture[5]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-400.0f, 400.0f);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-400.0f, -400.0f);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(400.0f, -400.0f);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(400.0f, 400.0f);
		glEnd();

		glDisable(GL_LIGHT2);
		glDisable(GL_TEXTURE_2D);
	}
	glutSwapBuffers();
}


void Timerfunction(int value)
{
	if (startERS)
	{
		if (value == 1)
		{
			if (flagMinigame != 0 && !flagGame)
			{
				mapYpos += 12;
				stoneYpos += 12;
				flagMinigame++;
				glutTimerFunc(50, Timerfunction, 1);
			}
			if (flagMinigame % 100 == 0 && flagMinigame != 0)
			{
				flagGame = true;
				mapYpos = 0;
				stoneYpos = 0;
				glutTimerFunc(50, Timerfunction, 1);
			}
		}
		if (value == 2 && !flagTurn && flagMinigame == 0 && !flagGame)
		{
			stoneZpos -= speedStone;
			if (stoneZpos <= chaZpos + 70)
				flagFlat = true;
			if (chaZpos < 0)
				stoneXpos = chaXpos;
			glutTimerFunc(50, Timerfunction, 2);
		}
		if (value == 3 && flagMinigame == 0 && !flagGame)
		{
			if (!flagTurn)
			{
				if (chaTurn == 1)
					chaXpos -= 4;
				else if (chaTurn == 2)
					chaXpos += 4;
				chaZpos -= 4;
				if (flagMove)
				{
					move += 3.5;
					if (move >= 30)
						flagMove = false;
				}
				else {
					move -= 3.5;
					if (move <= -30)
						flagMove = true;
				}
			}

			if (chaZpos <= -200 && chaTurn == 0 && seed[1] < 50)
			{
				glViewport(0, 0, WinW, WinH);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(120.0, WinW / WinH, 1, 1000);
				gluLookAt(chaXpos, 0.0, chaZpos + 200.0, chaXpos, 0.0, chaZpos, 0.0, 1.0, 0.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				flagTurn = true;
				chaZpos += 400;
				mapZpos += 400;
				stoneZpos += 400;

				MapFuntion1();
			}
			else if (chaZpos <= -200 && chaTurn == 0 && seed[1] >= 50) {
				chaZpos += 400;
				mapZpos += 400;
				stoneZpos += 400;

				MapFuntion1();

				MapFuntion2();
			}
			else if (chaZpos <= -200 && chaTurn > 0) {
				chaZpos += 400;
				mapZpos += 400;
				stoneZpos += 400;

				imsiMapArray[0] = mapPoint[0][0];
				imsiMapArray[1] = mapPoint[0][1];
				imsiMapArray[2] = mapPoint[0][2];
				imsiSeed = seed[0];
				imsiTrapSeed = trapSeed[0];

				mapPoint[0][0] = mapPoint[chaTurn][0];
				mapPoint[0][1] = mapPoint[chaTurn][1];
				mapPoint[0][2] = mapPoint[chaTurn][2];
				seed[0] = seed[chaTurn];
				trapSeed[0] = trapSeed[chaTurn];

				mapPoint[1][0] = mapPoint[0][0];
				mapPoint[1][1] = mapPoint[0][1];
				mapPoint[1][2] = mapPoint[0][2] - 400.0;
				seed[1] = 70;
				trapSeed[1] = (((rand() % 3) + 1) * 100)
					+ (((rand() % 3) + 1) * 10)
					+ (rand() % 10);

				mapPoint[2][0] = mapPoint[1][0];
				mapPoint[2][1] = mapPoint[1][1];
				mapPoint[2][2] = mapPoint[1][2] - 400.0;
				seed[2] = rand() % 100;
				trapSeed[2] = (((rand() % 3) + 1) * 100)
					+ (((rand() % 3) + 1) * 10)
					+ (rand() % 10);

				mapPoint[3][0] = mapPoint[2][0];
				mapPoint[3][1] = mapPoint[2][1];
				mapPoint[3][2] = mapPoint[2][2];
				seed[3] = seed[2];
				trapSeed[3] = trapSeed[2];
				chaTurn = 0;
			}
			glutTimerFunc(50, Timerfunction, 3);
		}
	}
	glutPostRedisplay();
}

GLvoid Reshape(int w, int h)
{
	WinW = w, WinH = h;
	LoadWinSize(w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!flagGame)
	{
		gluPerspective(120.0, w / h, 1, 1000);
		if (flagTurn)
			gluLookAt(chaXpos, 0.0, chaZpos + 200.0, chaXpos, 0.0, chaZpos, 0.0, 1.0, 0.0);
		else
			gluLookAt(chaXpos + 50.0, 150.0, chaZpos + 300.0, chaXpos, 0.0, chaZpos, 0.0, 1.0, 0.0);
	} else {
		glOrtho(-400.0, 400.0, -400.0, 400.0, 400.0, -400.0);
		gluLookAt(0.0, 0.0, 200, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Keyboard(unsigned char key, int x, int y)
{
	if (key == 32 && !startERS)
	{
		startERS = true;
		glutTimerFunc(20, Timerfunction, 2);
		glutTimerFunc(20, Timerfunction, 3);
		sndPlaySoundA("music.wav", SND_ASYNC || SND_LOOP);
	}
	if (!flagGame && startERS)
	{
		switch (key)
		{
		case '1':
			flagMinigame = 1;
			gameseed = rand() % 4;
			GenGame();
			glutTimerFunc(20, Timerfunction, 1);
			break;
		case '2':
			flagMinigame = 101;
			gameseed = rand() % 3 + 4;
			GenGame();
			glutTimerFunc(20, Timerfunction, 1);
			break;
		}
	}
	if (key == 'q' || key == 'Q')
		exit(1);
	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	if (startERS)
	{
		if (!flagTurn)
		{
			if (key == GLUT_KEY_LEFT && chaXpos > mapPoint[0][0] - 110)
				chaXpos -= 2;
			else if (key == GLUT_KEY_RIGHT && chaXpos < mapPoint[0][0] + 110)
				chaXpos += 2;
		}
		else {
			if (key == GLUT_KEY_LEFT)
			{
				chaTurn = 1;
				flagTurn = false;
				glViewport(0, 0, WinW, WinH);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(120.0, WinW / WinH, 1, 1000);
				gluLookAt(chaXpos + 50.0, 150.0, chaZpos + 300.0, chaXpos, 0.0, chaZpos, 0.0, 1.0, 0.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glutTimerFunc(50, Timerfunction, 2);
			}
			else if (key == GLUT_KEY_RIGHT) {
				chaTurn = 2;
				flagTurn = false;
				glViewport(0, 0, WinW, WinH);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(120.0, WinW / WinH, 1, 1000);
				gluLookAt(chaXpos + 50.0, 150.0, chaZpos + 300.0, chaXpos, 0.0, chaZpos, 0.0, 1.0, 0.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glutTimerFunc(50, Timerfunction, 2);
			}
		}
	}
	glutPostRedisplay();
}

void Clear()
{
	chaXpos = 0;
	chaZpos = 0;
	mapXpos = mapYpos = mapZpos = 0;
	stoneXpos = stoneYpos = 0;
	stoneZpos = 400;
	speedStone = 4;
	stoneAngle = 0;
	flagMinigame = 0;
	gameseed = 0;
	chaTurn = 0;
	move = 0;
	stoneTurn = 0;

	mapPoint[0][0] = 0.0;
	mapPoint[0][1] = 0.0;
	mapPoint[0][2] = 0.0;
	seed[0] = 70;

	mapPoint[1][0] = mapPoint[0][0];
	mapPoint[1][1] = mapPoint[0][1];
	mapPoint[1][2] = mapPoint[0][2] - 400.0;
	seed[1] = 70;

	MapFuntion2();

	for (int i = 0; i < 4; i++)
		trapSeed[i]
		= (((rand() % 3) + 1) * 100)
		+ (((rand() % 3) + 1) * 10)
		+ (rand() % 10);
	trapSeed[0] = 237;

	flagGame = false;
	startERS = false;
	flagMove = false;
	flagTurn = false;
	flagFlat = false;
	LoadBitMap();
	LoadStartBit();
	GetLight();
	glutTimerFunc(50, Timerfunction, 2);
}

void LoadStartBit()
{
	glGenTextures(1, texture);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	pBytes = LoadDIBitmap("start.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1024, 1024, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
}

void MapFuntion1()
{
	imsiMapArray[0] = mapPoint[0][0];
	imsiMapArray[1] = mapPoint[0][1];
	imsiMapArray[2] = mapPoint[0][2];
	imsiSeed = seed[0];
	imsiTrapSeed = trapSeed[0];

	mapPoint[0][0] = mapPoint[1][0];
	mapPoint[0][1] = mapPoint[1][1];
	mapPoint[0][2] = mapPoint[1][2];
	seed[0] = seed[1];
	trapSeed[0] = trapSeed[1];

	mapPoint[1][0] = mapPoint[2][0];
	mapPoint[1][1] = mapPoint[2][1];
	mapPoint[1][2] = mapPoint[2][2];
	seed[1] = seed[2];
	trapSeed[1] = trapSeed[2];

	mapPoint[2][0] = mapPoint[3][0];
	mapPoint[2][1] = mapPoint[3][1];
	mapPoint[2][2] = mapPoint[3][2];
	seed[2] = seed[3];
	trapSeed[2] = trapSeed[3];
}

void MapFuntion2()
{
	if (seed[1] < 50)
	{
		mapPoint[2][0] = mapPoint[1][0] - 400.0;
		mapPoint[2][1] = mapPoint[1][1];
		mapPoint[2][2] = mapPoint[1][2] - 400.0;
		seed[2] = 70;
		trapSeed[2] = (((rand() % 3) + 1) * 100)
			+ (((rand() % 3) + 1) * 10)
			+ (rand() % 10);

		mapPoint[3][0] = mapPoint[1][0] + 400.0;
		mapPoint[3][1] = mapPoint[1][1];
		mapPoint[3][2] = mapPoint[1][2] - 400.0;
		seed[3] = 70;
		trapSeed[3] = (((rand() % 3) + 1) * 100)
			+ (((rand() % 3) + 1) * 10)
			+ (rand() % 10);
	}
	else {
		mapPoint[2][0] = mapPoint[1][0];
		mapPoint[2][1] = mapPoint[1][1];
		mapPoint[2][2] = mapPoint[1][2] - 400.0;
		seed[2] = rand() % 100;
		trapSeed[2] = (((rand() % 3) + 1) * 100)
			+ (((rand() % 3) + 1) * 10)
			+ (rand() % 10);

		mapPoint[3][0] = mapPoint[2][0];
		mapPoint[3][1] = mapPoint[2][1];
		mapPoint[3][2] = mapPoint[2][2];
		seed[3] = seed[2];
		trapSeed[3] = trapSeed[2];
	}
}

void GetTrap(float &xPos, float &zPos, int &trap)
{
	trapPoint[0] = xPos;
	trapPoint[1] = zPos;
	flagTrap = trap;
}