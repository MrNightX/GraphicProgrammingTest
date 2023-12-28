#include <Windows.h>
#include <Windowsx.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
#include <iostream>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Robot"                  // Can change the window name
int qNo = 1;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- alphabet declaring n checking
#pragma region define
// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- numberpad button
//VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define PI 3.1415927
#pragma endregion
#pragma region void

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- Declare Start
float bodyAngle = 0.0f;
void wKeyAction();
void aKeyAction();
void sKeyAction();
void dKeyAction();

bool viewPrac = false;
//int qNo = 1;
int rX = 0, rY = 0, rZ = 0;
float rSpeed = 0.5;
float armRotate = 0;
float armRotate2 = 0;
float armRotate3 = 0;
const float ROTATION_INCREMENT = 5.0f;


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------switch case placing
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		if (wParam == VK_F1) qNo++;
		if (wParam == VK_F2) viewPrac = !viewPrac;

		if (wParam == 0x58) rX = abs(rX - 1);
		if (wParam == 0x59) rY = abs(rY - 1);
		if (wParam == 0x5A) rZ = abs(rZ - 1);

		//switch case for arms movement

		switch (wParam) {
		case VK_UP:
			if (armRotate < 45)  // Limiting the maximum rotation to 45 degrees
				armRotate += ROTATION_INCREMENT;
			break;
		case VK_DOWN:
			if (armRotate > 0) // Limiting the minimum rotation to 0 degrees
				armRotate -= ROTATION_INCREMENT;
			if (armRotate < 0) // Ensure the rotation doesn't go below 0 degrees
				armRotate = 0;
			break;
		case VK_LEFT:
			if (armRotate3 > -90) // Limiting the minimum rotation to -90 degrees
				armRotate3 -= ROTATION_INCREMENT;
			if (armRotate3 < -90) // Ensure the rotation doesn't go below -90 degrees
				armRotate3 = -90;
			break;

		case VK_RIGHT:
			if (armRotate3 < 90) // Limiting the maximum rotation to 90 degrees
				armRotate3 += ROTATION_INCREMENT;
			if (armRotate3 > 90) // Ensure the rotation doesn't exceed 90 degrees
				armRotate3 = 90;
			break;

		case VK_NUMPAD6:
			if (armRotate3 < 90) // Limiting the maximum rotation to 90 degrees
				armRotate3 += ROTATION_INCREMENT;
			if (armRotate3 > 90) // Ensure the rotation doesn't exceed 90 degrees
				armRotate3 = 90;
			break;

		case VK_NUMPAD4:
			if (armRotate3 > -90) // Limiting the minimum rotation to -90 degrees
				armRotate3 -= ROTATION_INCREMENT;
			if (armRotate3 < -90) // Ensure the rotation doesn't go below -90 degrees
				armRotate3 = -90;
			break;

		case VK_NUMPAD2: // Rotate right around the Y-axis
			if (armRotate2 < 90) // Limiting the maximum rotation to 90 degrees
				armRotate2 += ROTATION_INCREMENT;
			if (armRotate2 > 90) // Ensure the rotation doesn't exceed 90 degrees
				armRotate2 = 90;
			break;

		case VK_NUMPAD8: // Rotate left around the Y-axis
			if (armRotate2 > -90) // Limiting the minimum rotation to -90 degrees
				armRotate2 -= ROTATION_INCREMENT;
			if (armRotate2 < -90) // Ensure the rotation doesn't go below -90 degrees
				armRotate2 = -90;
			break;

		case VK_SPACE:
			armRotate = armRotate2 = armRotate3 = 0;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------nothing to change here

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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Void Start
void wKeyAction() {
	bodyAngle = 0.0f;
}
void aKeyAction() {
	bodyAngle = 90.0f;
}
void sKeyAction() {
	bodyAngle = 180.0f;
}
void dKeyAction() {
	bodyAngle = 270.0f;
}
void drawSphere(float r)
{
	//glRotatef(0.01, 1.0, 1.0, 1.0);
	GLUquadricObj* sphere = NULL;			//declare quadric obj pointer
	sphere = gluNewQuadric();				//create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//draw using line
	gluSphere(sphere, r, 30, 30);         //draw sphere
	gluDeleteQuadric(sphere);				//destroy obj
}
void drawSidedTriangle(float Length, float Width, float thickness) // have centering function
{
	glPushMatrix();
	glTranslatef(0.0, -Width / 2, 0);
	//front face
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-Length / 2, 0.0, -thickness / 2);
	glVertex3f(Length / 2, 0.0, -thickness / 2);
	glVertex3f(0.0, Width, -thickness / 2);

	glEnd();

	//back face
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-Length / 2, 0.0, thickness / 2);
	glVertex3f(0.0, Width, thickness / 2);
	glVertex3f(Length / 2, 0.0, thickness / 2);


	glEnd();

	//filling
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-Length / 2, 0.0, -thickness / 2);
	glVertex3f(-Length / 2, 0.0, thickness / 2);
	glVertex3f(Length / 2, 0.0, thickness / 2);
	glVertex3f(Length / 2, 0.0, -thickness / 2);

	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(Length / 2, 0.0, -thickness / 2);
	glVertex3f(Length / 2, 0.0, thickness / 2);
	glVertex3f(0.0, Width, thickness / 2);
	glVertex3f(0.0, Width, -thickness / 2);

	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, Width, -thickness / 2);
	glVertex3f(0.0, Width, thickness / 2);
	glVertex3f(-Length / 2, 0.0, thickness / 2);
	glVertex3f(-Length / 2, 0.0, -thickness / 2);

	glEnd();

	glPopMatrix();
}

//new

void drawRightTriangle(float OnX, float OnY, float thickness) //1st point is on the origin, have centering function
{
	glPushMatrix();
	glTranslatef(-OnX / 2, -OnY / 2, 0);
	//front face
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.0, -thickness / 2);
	glVertex3f(OnX, 0.0, -thickness / 2);
	glVertex3f(0.0, OnY, -thickness / 2);

	glEnd();

	//back face
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.0, thickness / 2);
	glVertex3f(0.0, OnY, thickness / 2);
	glVertex3f(OnX, 0.0, thickness / 2);


	glEnd();

	//filling
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.0, -thickness / 2);
	glVertex3f(0.0, 0.0, thickness / 2);
	glVertex3f(OnX, 0.0, thickness / 2);
	glVertex3f(OnX, 0.0, -thickness / 2);

	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(OnX, 0.0, -thickness / 2);
	glVertex3f(OnX, 0.0, thickness / 2);
	glVertex3f(0.0, OnY, thickness / 2);
	glVertex3f(0.0, OnY, -thickness / 2);

	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, OnY, -thickness / 2);
	glVertex3f(0.0, OnY, thickness / 2);
	glVertex3f(0.0, 0.0, thickness / 2);
	glVertex3f(0.0, 0.0, -thickness / 2);

	glEnd();

	glPopMatrix();
}

void drawTrianglePrism(float P1x, float P1y, float P2x, float P2y, float P3x, float P3y, float Thickness) //Drawing on the center of the z, this can get derailled very quickly
{
	glPushMatrix();
	glColor3f(0.0, 0.5, 1.0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(P1x, P1y, Thickness / 2);
	glVertex3f(P2x, P2y, Thickness / 2);
	glVertex3f(P3x, P3y, Thickness / 2);

	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(P1x, P1y, Thickness / 2);
	glVertex3f(P2x, P2y, Thickness / 2);
	glVertex3f(P2x, P2y, -Thickness / 2);
	glVertex3f(P1x, P1y, -Thickness / 2);

	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(P2x, P2y, Thickness / 2);
	glVertex3f(P3x, P3y, Thickness / 2);
	glVertex3f(P3x, P3y, -Thickness / 2);
	glVertex3f(P2x, P2y, -Thickness / 2);

	glVertex3f(P3x, P3y, Thickness / 2);
	glVertex3f(P3x, P3y, -Thickness / 2);
	glVertex3f(P1x, P1y, -Thickness / 2);
	glVertex3f(P1x, P1y, Thickness / 2);

	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(P1x, P1y, -Thickness / 2);
	glVertex3f(P2x, P2y, -Thickness / 2);
	glVertex3f(P3x, P3y, -Thickness / 2);

	glEnd();
	glPopMatrix();
}
//
//void drawCube(float x, float y, float z) // keep in mind that the cube will always draw and center on the origin, but the z is pointing away from ... you
//{
//	float P_X = x/2, P_Y = y/2 , P_Z = z/2;
//	glPushMatrix();
//	glTranslatef(-P_X, -P_Y, P_Z);
//		
//
//		glPolygonMode(GL_FRONT, GL_LINE);
//		glBegin(GL_POLYGON);//ps: I made sure this can be safely converted into GL_Polygon
//			glVertex3f(0, 0, 0); //front
//			glVertex3f(x, 0, 0);
//			glVertex3f(x, y, 0);
//			glVertex3f(0, y, 0);
//		glEnd();
//
//		glPolygonMode(GL_FRONT, GL_LINE);
//		glBegin(GL_POLYGON);
//			glVertex3f(0, y, 0); //top
//			glVertex3f(x, y, 0);
//			glVertex3f(x, y, -z);
//			glVertex3f(0, y, -z);
//		glEnd();
//
//		glPolygonMode(GL_FRONT, GL_LINE);
//		glBegin(GL_POLYGON);
//			glVertex3f(0, y, -z); //back
//			glVertex3f(x, y, -z);
//			glVertex3f(x, 0, -z);
//			glVertex3f(0, 0, -z);
//		glEnd();
//
//		glPolygonMode(GL_FRONT, GL_LINE);
//		glBegin(GL_POLYGON);
//			glVertex3f(0, 0, -z);  //bottom
//			glVertex3f(0, 0, 0);
//			glVertex3f(x, 0, 0);
//			glVertex3f(x, 0, -z);
//		glEnd();
//
//		glPolygonMode(GL_FRONT, GL_LINE);
//		glBegin(GL_POLYGON);
//			  //left side
//			glVertex3f(0, 0, 0);
//			glVertex3f(0, 0, -z);
//			glVertex3f(0, y, -z);
//			glVertex3f(0, y, 0);
//		glEnd();
//
//		glPolygonMode(GL_FRONT, GL_LINE);
//		glBegin(GL_POLYGON);
//		//right side
//			glVertex3f(x, 0, 0);
//			glVertex3f(x, 0, -z);
//			glVertex3f(x, y, -z);
//			glVertex3f(x, y, 0);
//		glEnd();
//
//	glPopMatrix();
//}

void drawCube(float x, float y, float z) // keep in mind that the cube will always draw and center on the origin, but the z is pointing away from ... you
{
	float P_X = x / 2, P_Y = y / 2, P_Z = z / 2;
	glPushMatrix();
	glTranslatef(-P_X, -P_Y, P_Z);


	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);//ps: I made sure this can be safely converted into GL_Polygon
	glVertex3f(0, 0, 0); //front
	glVertex3f(0, y, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x, 0, 0);
	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, -z); //top
	glVertex3f(x, y, 0);
	glVertex3f(0, y, 0);
	glVertex3f(0, y, -z);
	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(x, 0, -z); //back
	glVertex3f(x, y, -z);
	glVertex3f(0, y, -z);
	glVertex3f(0, 0, -z);
	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -z);  //bottom
	glVertex3f(0, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, 0, -z);
	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	//left side
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -z);
	glVertex3f(0, y, -z);
	glVertex3f(0, y, 0);
	glEnd();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	//right side
	glVertex3f(x, y, -z);
	glVertex3f(x, 0, -z);
	glVertex3f(x, 0, 0);
	glVertex3f(x, y, 0);
	glEnd();

	glPopMatrix();
}

void drawIrregularCube(float TopSize, float BottomSize, float height) //make cube with different top size and bottom size
{
	glPushMatrix();
	float TopWidthSize = TopSize;
	float BottomWidthSize = BottomSize;
	//Top
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, TopWidthSize / 2);
	glVertex3f(-TopSize / 2, height / 2, TopWidthSize / 2);

	glEnd();

	//Bottom
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, BottomWidthSize / 2);

	glEnd();

	//front
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, -TopWidthSize / 2);

	glEnd();
	//right
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, TopWidthSize / 2);

	glEnd();
	//back
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(TopSize / 2, height / 2, TopWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(-TopSize / 2, height / 2, TopWidthSize / 2);

	glEnd();
	//left
	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-TopSize / 2, height / 2, TopWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(-TopSize / 2, height / 2, -TopWidthSize / 2);

	glEnd();
	glPopMatrix(); //need to thank Jason for fixing them :)
}
void arm() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	//glRotatef(-90, 0.0, 0.0, 1.0);     //rotate 90 degrees so taht arm is down
	glTranslatef(-0.5, 0.0, 0.0);
	glPushMatrix();
	glRotatef(armRotate2, 0.0, 1.0, 0.0);
	glRotatef(armRotate3, 1.0, 0.0, 0.0);
#pragma region shoulder
	//----shoulder----//
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	// Face 1
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	//middle hand elbow
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0.52, 0.1, 0.1);
	GLUquadricObj* sphere = NULL;			//declare quadric obj pointer
	sphere = gluNewQuadric();				//create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//draw using line
	gluSphere(sphere, 0.1, 30, 30);         //draw sphere
	gluDeleteQuadric(sphere);				//destroy obj
	//-------------------------------------------------------------------------------
	glPopMatrix();
#pragma endregion
#pragma region foreArm
	//----fore arm----//
	glPushMatrix();
	glTranslatef(0.55, 0.0, 0.0);
	glRotatef(armRotate, 0.0, 0.0, 0.1);
	glColor3f(0, 0, 1);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	//----wrist ball----//
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0.5, 0.1, 0.1);
	sphere = gluNewQuadric();				//create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//draw using line
	gluSphere(sphere, 0.09, 30, 30);         //draw sphere
	gluDeleteQuadric(sphere);				//destroy obj
	//-------------------------------------------------------------------------------
	glPopMatrix();
#pragma endregion
#pragma region hand palm
	//----handPalm----//
	glColor3f(1, 1, 0);
	glTranslatef(0.52, 0, 0.0);
	glBegin(GL_QUADS);
	// Face 1
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.1f, 0.2f, 0.2f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.2f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glEnd();
#pragma endregion
	glPushMatrix();
#pragma region Hand Thumb
	//----HandThumbBase----//
	glPushMatrix();
	glScalef(1.1f, 1.1f, 1.1f);
	glTranslatef(0.0, -0.09, 0.0);
	glRotatef(10, 0.0, 0.0, 1.0);
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.1, 0.2, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	//----HandThumbMIddle----//
	glPushMatrix();
	glScalef(0.9f, 0.9f, 0.9f);
	glTranslatef(0.04, 0, 0.0);
	glRotatef(-10, 0.0, 0.0, 1.0);
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.1, 0.2, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();
	//----HandThumbTop----// pyramid
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.249, 0.168, 0.028);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	GLUquadricObj* cylinder = NULL;	//declare quadric obj pointer
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.03, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
#pragma endregion
	glTranslatef(-0.02, 0.02, 0.0);
	glRotatef(-10, 0.0, 0.0, 1.0);
#pragma region Hand Pointer
	//----HandPointer----//
	glColor3f(1, 0, 1);
	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
#pragma endregion
#pragma region Hand Middle Finger
	//----HandMiddleFinger----//
	glColor3f(0, 1, 1);
	glTranslatef(0, 0, 0.05);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
#pragma endregion
#pragma region Hand Ring Finger
	//----HandRingFinger----//
	glColor3f(1, 0, 1);
	glTranslatef(0, 0, 0.05);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
#pragma endregion
#pragma region Hand Pinky
	//----HandPinky----//
	glColor3f(0, 1, 1);
	glTranslatef(0, 0, 0.05);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
#pragma endregion
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void leg(float AnimationControl)
{
	//glLoadIdentity();

	glPushMatrix();
	/*glRotatef(armRotate, 0.0, 0.0, 1.0);
	glRotatef(armRotate2, 0.0, 1.0, 0.0);*/
	glRotatef(AnimationControl, 1.0, 0.0, 0.0);

	//drawTrianglePrism(0.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.1f);
	//drawRightTriangle(0.3f, -0.6f, 0.1f);
	//drawSidedTriangle(0.2, 0.5, 0.1);
	//drawIrregularCube(0.2, 0.5, 1.0);

	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, -0.825f, 0); //original transformation

	//glTranslatef(0, -0.4f, 0.0f); //focusing on that thicc thigh
	//glTranslatef(0, 0.3f, 0.0f); // focusing on those slender shin
	//dear viewers, pls do not look at me with weird eyes, i swear im just joking... hehe
	glPushMatrix();
	glTranslatef(0.0, 0.825, 0.0);
	drawIrregularCube(0.15, 0.2, 0.15);
	glPopMatrix();

	glColor3f(1, 1, 1);
#pragma region Thigh
	glPushMatrix(); 

	glTranslatef(0, 0.4f, 0);
	drawCube(0.2f, 0.7f, 0.2f);
	
		//Real fun begins here
		glPushMatrix();
#pragma region Thigh front armor
		glColor3f(0.5, 0.0, 1.0);
		glLineWidth(5);
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);
		 
		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, 0.35, -0.175); //right frontface
		glVertex3f(0.0, -0.01, -0.225);
		glVertex3f(0.0, -0.4, -0.175);
		glVertex3f(0.175, -0.1, -0.05);
		glVertex3f(0.175, 0.35, -0.05);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, 0.35, -0.125);
		glVertex3f(0.0, -0.01, -0.205);
		glVertex3f(0.0, -0.4, -0.125);
		glVertex3f(0.175, -0.1, -0.03);
		glVertex3f(0.175, 0.35, -0.03);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, 0.35, -0.175);
		glVertex3f(0.0, -0.01, -0.225);
		glVertex3f(0.0, -0.01, -0.205);
		glVertex3f(0.0, 0.35, -0.125);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, -0.01, -0.225);
		glVertex3f(0.0, -0.4, -0.175);
		glVertex3f(0.0, -0.4, -0.125);
		glVertex3f(0.0, -0.01, -0.205);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, -0.4, -0.175);
		glVertex3f(0.175, -0.1, -0.05);
		glVertex3f(0.175, -0.1, -0.03);
		glVertex3f(0.0, -0.4, -0.125);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.175, -0.1, -0.05);
		glVertex3f(0.175, 0.35, -0.05);
		glVertex3f(0.175, 0.35, -0.03);
		glVertex3f(0.175, -0.1, -0.03);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.175, 0.35, -0.05);
		glVertex3f(0.0, 0.35, -0.175);
		glVertex3f(0.0, 0.35, -0.125);
		glVertex3f(0.175, 0.35, -0.03);

		glEnd();

		glColor3f(0.5, 0.0, 1.0);
		glLineWidth(5);
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, 0.35, -0.175); //left frontface
		glVertex3f(0.0, -0.01, -0.225);
		glVertex3f(0.0, -0.4, -0.175);
		glVertex3f(-0.175, -0.1, -0.05);
		glVertex3f(-0.175, 0.35, -0.05);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, 0.35, -0.125);
		glVertex3f(0.0, -0.01, -0.205);
		glVertex3f(0.0, -0.4, -0.125);
		glVertex3f(-0.175, -0.1, -0.03);
		glVertex3f(-0.175, 0.35, -0.03);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, 0.35, -0.175);
		glVertex3f(0.0, -0.01, -0.225);
		glVertex3f(0.0, -0.01, -0.205);
		glVertex3f(0.0, 0.35, -0.125);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, -0.01, -0.225);
		glVertex3f(0.0, -0.4, -0.175);
		glVertex3f(0.0, -0.4, -0.125);
		glVertex3f(0.0, -0.01, -0.205);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.0, -0.4, -0.175);
		glVertex3f(-0.175, -0.1, -0.05);
		glVertex3f(-0.175, -0.1, -0.03);
		glVertex3f(0.0, -0.4, -0.125);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(-0.175, -0.1, -0.05);
		glVertex3f(-0.175, 0.35, -0.05);
		glVertex3f(-0.175, 0.35, -0.03);
		glVertex3f(-0.175, -0.1, -0.03);

		glEnd();
		glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(-0.175, 0.35, -0.05);
		glVertex3f(0.0, 0.35, -0.175);
		glVertex3f(0.0, 0.35, -0.125);
		glVertex3f(-0.175, 0.35, -0.03);

		glEnd();
#pragma endregion

#pragma region Thigh Back armor
		{
			glPushMatrix();
			glTranslatef(0.0, 0.35, 0.1); //upper thigh armor
			glPushMatrix();
			glRotatef(-15, 1.0, 0.0, 0.0);
			drawTrianglePrism(0.17, 0.0, -0.17, 0.0, 0.0, -0.4, 0.05);
			glPopMatrix();

			//back right
			glPushMatrix();
			glColor3f(0.0, 0.5, 1.0);
			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);

			glVertex3f(0.17, 0.0, 0.025);
			glVertex3f(0.0, -0.4, 0.14);
			glVertex3f(0.17, -0.75, 0.025);

			glEnd();

			glColor3f(0.0, 0.5, 1.0);
			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);

			glVertex3f(0.17, 0.0, 0);
			glVertex3f(0.0, -0.4, 0);
			glVertex3f(0.17, -0.75, 0);

			glEnd();

			//back left
			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);

			glVertex3f(-0.17, 0.0, 0.025);
			glVertex3f(0.0, -0.4, 0.14);
			glVertex3f(-0.17, -0.75, 0.025);

			glEnd();

			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);

			glVertex3f(-0.17, 0.0, 0);
			glVertex3f(0.0, -0.4, 0);
			glVertex3f(-0.17, -0.75, 0);

			glEnd();

			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON); //right fill
			glVertex3f(0.17, 0.0, 0.025);
			glVertex3f(0.17, 0.0, 0);
			glVertex3f(0.17, -0.75, 0);
			glVertex3f(0.17, -0.75, 0.025);
			glEnd();

			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);
			{
				glVertex3f(0.17, 0.0, 0.025);
				glVertex3f(0.17, 0.0, 0);
				glVertex3f(0.0, -0.4, 0);
				glVertex3f(0.0, -0.4, 0.14);
			}
			glEnd();

			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);
			{
				glVertex3f(0.17, -0.75, 0.025);
				glVertex3f(0.17, -0.75, 0);
				glVertex3f(0.0, -0.4, 0);
				glVertex3f(0.0, -0.4, 0.14);
			}
			glEnd();

			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON); //left fill
			glVertex3f(-0.17, 0.0, 0.025);
			glVertex3f(-0.17, 0.0, 0);
			glVertex3f(-0.17, -0.75, 0);
			glVertex3f(-0.17, -0.75, 0.025);
			glEnd();

			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);
			{
				glVertex3f(-0.17, 0.0, 0.025);
				glVertex3f(-0.17, 0.0, 0);
				glVertex3f(0.0, -0.4, 0);
				glVertex3f(0.0, -0.4, 0.14);
			}
			glEnd();

			glPolygonMode(GL_FRONT, GL_LINE);
			glBegin(GL_POLYGON);
			{
				glVertex3f(-0.17, -0.75, 0.025);
				glVertex3f(-0.17, -0.75, 0);
				glVertex3f(0.0, -0.4, 0);
				glVertex3f(0.0, -0.4, 0.14);
			}
			glEnd();

			glPopMatrix();
			glPopMatrix();

			glPopMatrix();

			glPopMatrix();
		}
#pragma endregion

#pragma region side armor
	glPushMatrix();
	glTranslatef(0.15, 0.525, 0.05);
		glColor3f(1.0, 0.5, 0.0);
		glLineWidth(3);
		drawCube(0.075, 0.45, 0.15);
		
		glPushMatrix();
			glTranslatef(0.0, -0.225, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			drawTrianglePrism(-0.075, 0.0, 0.075, 0.0, -0.075, -0.3, 0.075);
		glPopMatrix();
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.15, 0.525, 0.05);
		glColor3f(1.0, 0.5, 0.0);
		glLineWidth(3);
		drawCube(0.075, 0.45, 0.15);

		glPushMatrix();
			glTranslatef(0.0, -0.225, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			drawTrianglePrism(-0.075, 0.0, 0.075, 0.0, -0.075, -0.3, 0.075);
		glPopMatrix();
		glEnd();
	glPopMatrix();
#pragma endregion
	//ps: this took me more than 12 hours to figure things out
	glPushMatrix();
	if (AnimationControl > 0) //only bend the knees forward
	{
		glRotatef(-AnimationControl /2 , 1.0, 0.0, 0.0);
	}
	else
	{
		glRotatef(AnimationControl, 1.0, 0.0, 0.0);
	}


	glColor3f(1, 1, 1);
#pragma region Knee
	glPushMatrix();
	glLineWidth(1);
	drawSphere(0.1f);
	glPopMatrix();
#pragma endregion

#pragma region Shin
	glPushMatrix();
	glTranslatef(0.0f, -0.3f, 0.0f);
	//drawCube(0.25f, 0.5f, 0.25f);

		//Fun part here
		glPushMatrix();
		glTranslatef(0.0f, 0.2f, 0.0f);
		glColor3f(1.0, 1.0, 0.0);
		drawIrregularCube(0.2, 0.25, 0.1);

			glPushMatrix();
			glTranslatef(0.0, 0.0, 0.025);
			glScalef(0.25, 1.0, 1.0);
			glColor3f(0.0, 1.0, 1.0);
			drawIrregularCube(0.2, 0.25, 0.1);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0.0f, -0.075f, 0.0f);
		glColor3f(1.0, 1.0, 0.0);
		drawIrregularCube(0.25, 0.15, 0.45);

			glPushMatrix();
			glTranslatef(0.0, 0.0, 0.025);
			glScalef(0.25, 1.0, 1.0);
			glColor3f(0.0, 1.0, 1.0);
			drawIrregularCube(0.25, 0.15, 0.45);
			glPopMatrix();

			glPushMatrix();
			glColor3f(0.0, 1.0, 1.0);
			//glTranslatef(0.0, 0.0, 0.025);
			
			drawCube(0.20, 0.45, 0.05);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
#pragma endregion

#pragma region ankle
	glPushMatrix();
	glTranslatef(0.0f, -0.6f, 0.0f);
	glColor3f(1.0, 1.0, 1.0);
	drawCube(0.1f, 0.1f, 0.1f);
	glPopMatrix();
#pragma endregion

#pragma region Foot
	glPushMatrix(); 
	glTranslatef(0.0f, -0.725f, 0.0f);
	drawCube(0.3f, 0.15f, 0.25f);

		glPushMatrix(); //left front toe

			glTranslatef(-0.1, 0.0, -0.25);
			glRotatef(90, 0.0, 1.0, 0.0);
			drawRightTriangle(0.25, 0.15, 0.1);

		glPopMatrix();

		glPushMatrix(); //right front toe, but lazier
		glScalef(-1.0, 1.0, 1.0); //Just reflect them :DDD
		glTranslatef(-0.1, 0.0, -0.25);
		glRotatef(90, 0.0, 1.0, 0.0);
		drawRightTriangle(0.25, 0.15, 0.1);

		glPopMatrix();

		glPushMatrix(); //left back toe

			glTranslatef(-0.1, 0.0, 0.2);
			glRotatef(-90, 0.0, 1.0, 0.0);
			drawRightTriangle(0.15, 0.15, 0.1);

		glPopMatrix();

		glPushMatrix(); //right back toe, but lazier... too
			glScalef(-1.0, 1.0, 1.0); //Just reflect them :DDD
			glTranslatef(-0.1, 0.0, 0.2);
			glRotatef(-90, 0.0, 1.0, 0.0);
			drawRightTriangle(0.15, 0.15, 0.1);

		glPopMatrix();

	glPopMatrix();
#pragma endregion
	glPopMatrix();
	glPopMatrix();
}
void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f); //X axis
		drawCube(2.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f); //y axis
		drawCube(0.0f, 2.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 1.0f); //z axis
		drawCube(0.0f, 0.0f, 2.0f);
	glPopMatrix();
	//arm();
	
	
	glRotatef(armRotate, 0.0, 0.0, 1.0);
	glRotatef(armRotate2, 0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(-0.2f, 0.0f, 0.0f);
		leg(armRotate3); // left leg
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.2f, 0.0f, 0.0f);
		leg(-armRotate3); // left leg
		glPopMatrix();
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------Void End 
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
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000,
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
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
