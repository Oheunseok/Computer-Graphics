#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4800)

#include <GL/glut.h> // includes gl.h glu.h
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>

#define PI 3.1415926535897

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyboard(int key, int x, int y);
GLvoid MouseMini(int button, int state, int x, int y);
void Motion(int x, int y);
void GetLight();
void Clear();

void DrawRoad(float width, float height);
void MapDraw(int points[], int seed, float width, float height, int trapSeed);
void DrawCharic(bool flat, float move, float turn);

void Minigame(int num, int &flagCount, bool &flag, int seed);

static int WinW, WinH;

static int flagMinigame;				//미니게임 지정 변수
static bool flagGame;					//미니게임 입장 판단변수

static float speedStone = 0;

static GLubyte *pBytes;
static BITMAPINFO *info;

static GLuint texture[10];

GLubyte *LoadDIBitmap(const char *filename, BITMAPINFO **info);

void LoadBitMap();
void LoadWinSize(int &WinW, int &WinH);

void GenGame();

void GetTrap(float &xPos, float &zPos, int &trap);

bool InRect(int mx, int my, int tx, int ty, int slop);