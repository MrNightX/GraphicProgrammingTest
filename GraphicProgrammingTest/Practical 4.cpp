#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#define WINDOW_TITLE "Practical 4"

bool viewPrac = false;
int qNo = 1;

int rX = 0, rY = 0, rZ = 0;
float rSpeed = 0.5;

float armRotate = 0;
float armRotate2 = 0;
float armRotate3 = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) 
			PostQuitMessage(0);

		if (wParam == VK_F1) 
			qNo++;

		if (wParam == VK_F2) 
			viewPrac = !viewPrac;

		if (wParam == 'X') 
			rX = abs(rX - 1);

		if (wParam == 'Y') 
			rY = abs(rY - 1);

		if (wParam == 'Z') 
			rZ = abs(rZ - 1);

		if (wParam == VK_UP && armRotate < 90) 
			armRotate += rSpeed * 5;

		if (wParam == VK_DOWN && armRotate > 0) 
			armRotate -= rSpeed * 5;

		if (wParam == VK_LEFT) 
			armRotate2 -= rSpeed * 5;

		if (wParam == VK_RIGHT) 
			armRotate2 += rSpeed * 5;

		if (wParam == VK_NUMPAD2) 
			armRotate3 += rSpeed * 5;

		if (wParam == VK_NUMPAD8) 
			armRotate3 -= rSpeed * 5;

		if (wParam == VK_SPACE)
		{
			armRotate = 0;
			armRotate2 = 0;
			armRotate3 = 0;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void prac4A(float size) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glLoadIdentity();

	//glPushMatrix();
	glRotatef(0.05, 1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	//Face 1
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, size);
	glVertex3f(size, 0.0, size);
	glVertex3f(size, 0.0, 0.0);
	//Face 2
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size, size, 0.0);
	glVertex3f(size, size, size);
	glVertex3f(size, 0.0, size);
	//Face 3
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(size, 0.0, size);
	glVertex3f(size, size, size);
	glVertex3f(0.0, size, size);
	glVertex3f(0.0, 0.0, size);
	//Face 4
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, size);
	glVertex3f(0.0, size, size);
	glVertex3f(0.0, size, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	//Face 5
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size, size, 0.0);
	glVertex3f(0.0, size, 0.0);
	//Face 6
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.0, size, 0.0);
	glVertex3f(0.0, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, 0.0);
	glEnd();

	//glPopMatrix();
} // DrawCube

void pracAQ1n2(float size) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLineWidth(3);
	glRotatef(rX * (rSpeed), 1.0, 0.0, 0.0);
	glRotatef(rY * (rSpeed), 0.0, 1.0, 0.0);
	glRotatef(rZ * (rSpeed), 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size, 0.0, size);
	glVertex3f(0.0, 0.0, size);
	glVertex3f(size / 2, size, size / 2);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, size);
	glVertex3f(0.0, 0.0, 0.0);

	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0, size);

	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0, 0.0);
	glEnd();
}

void pracAQ3(float size) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();

	glLineWidth(3);

	glPushMatrix();
	glRotatef(armRotate2, 0.0, 1.0, 0.0);
	glRotatef(armRotate3, 1.0, 0.0, 0.0);

	//A1F1
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-size, 0, 0);
	glVertex3f(-size, 0, size / 2);
	glVertex3f(0, 0, size / 2);
	glVertex3f(0, 0, 0);
	glEnd();

	//A1F2
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(-size, 0, 0);
	glVertex3f(-size, size / 2, 0);
	glVertex3f(0, size / 2, 0);
	glEnd();

	//A1F3
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, size / 2, 0);
	glVertex3f(-size, size / 2, 0);
	glVertex3f(-size, size / 2, size / 2);
	glVertex3f(0, size / 2, size / 2);
	glEnd();

	//A1F4
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, size / 2, size / 2);
	glVertex3f(0, size / 2, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size / 2);
	glEnd();

	//A1F5
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, size / 2);
	glVertex3f(0, size / 2, size / 2);
	glVertex3f(-size, size / 2, size / 2);
	glVertex3f(-size, 0, size / 2);
	glEnd();

	//A1F6
	glBegin(GL_LINE_LOOP);
	glVertex3f(-size, 0, size / 2);
	glVertex3f(-size, 0, 0);
	glVertex3f(-size, size / 2, 0);
	glVertex3f(-size, size / 2, size / 2);
	glEnd();

	//-------------------------------------------------------------------------------

	glPushMatrix();

	glRotatef(armRotate, 0.0, 0.0, 1.0);

	//A2F1
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(size, 0, 0);
	glVertex3f(size, 0, size / 2);
	glVertex3f(0, 0, size / 2);
	glVertex3f(0, 0, 0);
	glEnd();

	//A2F2
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glVertex3f(size, size / 2, 0);
	glVertex3f(0, size / 2, 0);
	glEnd();

	//A2F3
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, size / 2, 0);
	glVertex3f(size, size / 2, 0);
	glVertex3f(size, size / 2, size / 2);
	glVertex3f(0, size / 2, size / 2);
	glEnd();

	//A2F4
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, size / 2, size / 2);
	glVertex3f(0, size / 2, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size / 2);
	glEnd();

	//A2F5
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0, size / 2);
	glVertex3f(0, size / 2, size / 2);
	glVertex3f(size, size / 2, size / 2);
	glVertex3f(size, 0, size / 2);
	glEnd();

	//A2F6
	glBegin(GL_LINE_LOOP);
	glVertex3f(size, 0, size / 2);
	glVertex3f(size, 0, 0);
	glVertex3f(size, size / 2, 0);
	glVertex3f(size, size / 2, size / 2);
	glEnd();

	glPopMatrix();
	glPopMatrix();
}

void drawSphere(float r) {
	GLUquadricObj* sphere = NULL;	//declare quadric obj pointer
	sphere = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(sphere, GLU_LINE);	//draws outline on the sphere

	gluSphere(sphere, r, 30, 30);	//draw sphere
	gluDeleteQuadric(sphere);	//destroy the sphere
}

void drawCylinder(float tR, float bR, float h) {
	GLUquadricObj* cylinder = NULL;	//declare quadric obj pointer
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cylinder

	gluCylinder(cylinder, bR, tR, h, 30, 30);	//draw cylinder
	gluDeleteQuadric(cylinder);	//destroy the cylinder
}

void drawCone(float bR, float h) {
	GLUquadricObj* cylinder = NULL;	//declare quadric obj pointer
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, bR, 0.0, h, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone
}

void drawDisk(float inR, float outR) {
	GLUquadricObj* disk = NULL;	//declare quadric obj pointer
	disk = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(sphere, GLU_LINE);	//draws outline on the disk

	gluDisk(disk, inR, outR, 30, 30);	//draw disk
	gluDeleteQuadric(disk);	//destroy the disk
}

void prac4B1(float r) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(rSpeed, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);

	drawSphere(r);
}

void prac4B2(float tR, float bR, float h) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(rSpeed, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.8, 1.0);

	drawCylinder(tR, bR, h);
}

void prac4B3(float bR, float h) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(0.05, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.8, 1.0);

	drawCone(bR, h);
}

void pracBQ1() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(rSpeed, 0.0, 1.0, 0.0);

	glPushMatrix();
	glRotatef(90, 0.0, 0.2, 1.0);

	//Ice cream 1
	glColor3f(0.0, 0.5, 1.0);
	drawSphere(0.2);

	//Ice cream 2
	glPushMatrix();
	glTranslatef(0.2, 0.0, 0.0);
	glColor3f(0.8, 0.8, 0.8);
	drawSphere(0.2);
	glPopMatrix();

	//Cone
	glPushMatrix();
	glRotatef(-90, 0.0, 1.0, 0.0);
	glColor3f(0.8, 0.5, 0.2);
	drawCone(0.23, 0.7);
	glPopMatrix();

	//Cone line
	glPushMatrix();
	glRotatef(-90, 0.0, 1.0, 0.0);
	glColor3f(0.7, 0.3, 0.0);
	GLUquadricObj* cone = NULL;	//declare quadric obj pointer
	cone = gluNewQuadric();		//create quadric obj in the memory
	gluQuadricDrawStyle(cone, GLU_LINE);	//draws outline on the cone
	gluCylinder(cone, 0.23, 0.0, 0.7, 30, 30);	//draw cone
	gluDeleteQuadric(cone);	//destroy the cone
	glPopMatrix();

	//Biscuit
	glPushMatrix();
	glTranslatef(0.4, 0.1, 0.0);
	glColor3f(0.8, 0.5, 0.2);
	drawDisk(0.0, 0.1);
	glPopMatrix();

	//Biscuit 2 
	glPushMatrix();
	glTranslatef(0.3, -0.1, -0.05);
	glRotatef(-10, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.2, 0.0);
	drawCylinder(0.02, 0.02, 0.2);
	glPopMatrix();

	//Cherry
	glPushMatrix();
	glTranslatef(0.3, -0.1, 0.1);
	glRotatef(-40, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	drawSphere(0.05);
	glPopMatrix();

	glPopMatrix();
}

void display()
{
	if (viewPrac) {
		switch (qNo) {
		case 1:
			prac4A(0.5);	//DrawCube
			break;

		case 2:
			prac4B1(0.5);	//DrawSphere
			break;

		case 3:
			prac4B2(0.5, 0.5, 1.0);	//DrawCylinder
			break;

		case 4:
			prac4B3(0.5, 1.0);	//DrawCylinder
			break;

		default:
			qNo = 1;
		}
	}
	else {
		switch (qNo) {
		case 1:
			pracAQ1n2(0.5);	//DrawPyramid
			break;

		case 2:
			pracAQ3(0.5);	//DrawArm
			break;

		case 3:
			pracBQ1();		//DrawIceCream
			break;

		default:
			qNo = 1;
		}
	}
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------