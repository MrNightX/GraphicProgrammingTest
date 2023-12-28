#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#define WINDOW_TITLE "Practical 4"
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

bool viewPrac = false;
int qNo = 1;

int rX = 0, rY = 0, rZ = 0;
float rSpeed = 0.5;

float armRotate = 0;
float armRotate2 = 0;
float armRotate3 = 0;
const float ROTATION_INCREMENT = 5.0f;
#pragma region Camera Movement
float pRX = 0.0, pRY = 0.0;
float pRSpeed = 4.0;
//	Translation
//float pTZ = -10.0;
float bPRX = 0.0;
float bPRY = 0.5;
float bPRZ = -4.0;
float pTX = bPRX;
float pTY = bPRY;
float pTZ = bPRZ;
float maxPTX = 3.0;
float minPTX = -3.0;
float maxPTY = 3.0;
float minPTY = -3.0;
float maxPTZ = -2.0;
float minPTZ = -20;
float pTSpeed = 0.2;

bool CameraMovement = true;

void resetCamera() {
	pRX = pRY = 0.0;
	pTX = bPRX;
	pTY = bPRY;
	pTZ = bPRZ;
}
#pragma endregion	


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			if (CameraMovement) {
				PostQuitMessage(0);
			}
			else {
				// Reset arm rotations if not in camera movement mode
				armRotate = armRotate2 = armRotate3 = 0;
			}
		}
		else if (CameraMovement) {
			// Handle camera movement
			switch (wParam) {
			case VK_UP: pRX -= pRSpeed; break;
			case VK_DOWN: pRX += pRSpeed; break;
			case VK_LEFT: pRY -= pRSpeed; break;
			case VK_RIGHT: pRY += pRSpeed; break;
			case VK_NUMPAD4: if (pTX < maxPTX) pTX += pTSpeed; break;
			case VK_NUMPAD6: if (pTX > minPTX) pTX -= pTSpeed; break;
			case VK_NUMPAD2: if (pTY < maxPTY) pTY += pTSpeed; break;
			case VK_NUMPAD8: if (pTY > minPTY) pTY -= pTSpeed; break;
			case 'W': if (pTZ < maxPTZ) pTZ += pTSpeed; break;
			case 'S': if (pTZ > minPTZ) pTZ -= pTSpeed; break;
			case VK_SPACE: resetCamera(); break;
			default: break;
			}
		}
		else {
			// Handle arm movements
			switch (wParam) {
			case VK_UP:
				if (armRotate < 45) armRotate += ROTATION_INCREMENT;
				break;
			case VK_DOWN:
				if (armRotate > 0) armRotate -= ROTATION_INCREMENT;
				if (armRotate < 0) armRotate = 0;
				break;
			case VK_LEFT:
				if (armRotate3 > -90) armRotate3 -= ROTATION_INCREMENT;
				if (armRotate3 < -90) armRotate3 = -90;
				break;
			case VK_RIGHT:
				if (armRotate3 < 90) armRotate3 += ROTATION_INCREMENT;
				if (armRotate3 > 90) armRotate3 = 90;
				break;
			case VK_NUMPAD6:
				if (armRotate3 < 90) armRotate3 += ROTATION_INCREMENT;
				if (armRotate3 > 90) armRotate3 = 90;
				break;
			case VK_NUMPAD4:
				if (armRotate3 > -90) armRotate3 -= ROTATION_INCREMENT;
				if (armRotate3 < -90) armRotate3 = -90;
				break;
			case VK_NUMPAD2:
				if (armRotate2 < 90) armRotate2 += ROTATION_INCREMENT;
				if (armRotate2 > 90) armRotate2 = 90;
				break;
			case VK_NUMPAD8:
				if (armRotate2 > -90) armRotate2 -= ROTATION_INCREMENT;
				if (armRotate2 < -90) armRotate2 = -90;
				break;
			case VK_SPACE:
				armRotate = armRotate2 = armRotate3 = 0;
				break;
			default:
				break;
			}
		}

		if (wParam == 'P') {
			CameraMovement = !CameraMovement;
		}
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
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
void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-8.0, 8.0, -8.0, 8.0, 1.0, 10.0);
	gluPerspective(60, 1.0, 0.6, 100.0);
	glTranslatef(pTX, pTY, pTZ);
	glRotatef(pRX, 1.0, 0.0, 0.0);
	glRotatef(pRY, 0.0, 1.0, 0.0);
}


void LeftHand() {

	glLoadIdentity();
	glPushMatrix();
	glRotatef(-90, 0.0, 0.0, 1.0);     //rotate 90 degrees so taht arm is down
	glTranslatef(-0.5, -0.8, 0.0);
	glPushMatrix();
	glRotatef(armRotate2, 0.0, 0.0, 1.0);
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.2f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.1f, 0.2f, 0.2f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.2f);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glTranslatef(0.0, -0.09, 0.0);
	glRotatef(10, 0.0, 0.0, 1.0);
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.1, 0.21, 0.0);

	//glScalef(0.9f, 0.9f, 0.9f);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glTranslatef(0.035, -0.01, 0.005);
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glTranslatef(0.249, 0.16, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	GLUquadricObj* cylinder = NULL;	//declare quadric obj pointer
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandPointerMiddle----//
	glColor3f(1, 0, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandMiddleMiddle----//
	glColor3f(0, 1, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();
	//----HandMiddleTop----// pyramid
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandPointerMiddle----//
	glColor3f(1, 0, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandPinklyMiddle----//
	glColor3f(0, 1, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();
	//----HandPinkyTop----// pyramid
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory
	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone
	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
#pragma endregion
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void RightHand() {
	glClearColor(0.0, 0.0, 0.0, 1.0);


	glLoadIdentity();
	glPushMatrix();
	glRotatef(-90, 0.0, 0.0, 1.0);     //rotate 90 degrees so taht arm is down
	glTranslatef(-0.5, 0.7, 0.0);
	glPushMatrix();
	glRotatef(-armRotate2, 0.0, 0.0, 1.0);
	glRotatef(-armRotate3, 1.0, 0.0, 0.0);
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glEnd();

	//middle hand elbow
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0.52, -0.1, 0.1);
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
	glRotatef(-armRotate, 0.0, 0.0, 0.1);
	glColor3f(0, 0, 1);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glEnd();

	//----wrist ball----//
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0.5, -0.1, 0.1);
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glVertex3f(0.1f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.1f, -0.2f, 0.2f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, -0.2f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();
#pragma endregion
#pragma region Hand Thumb
	//----HandThumbBase----//
	glPushMatrix();
	glScalef(1.1f, 1.1f, 1.1f);
	glTranslatef(0.0, -0.09, 0.0);
	glRotatef(-10, 0.0, 0.0, 1.0);
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.08, -0.07, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glRotatef(10, 0.0, 0.0, 1.0);
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.15, -0.255, 0.005);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();
	//----HandThumbTop----// Cone
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.252, -0.1655, 0.026);
	glRotatef(11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	GLUquadricObj* cylinder = NULL;	//declare quadric obj pointer
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
#pragma endregion
	glPushMatrix();
	glTranslatef(-0.02, -0.07, 0.0);
	glRotatef(10, 0.0, 0.0, 1.0);
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandPointerMiddle----//
	glColor3f(1, 0, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandMiddleMiddle----//
	glColor3f(0, 1, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();
	//----HandMiddleTop----// pyramid
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandPointerMiddle----//
	glColor3f(1, 0, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
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
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone

	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
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
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	//----HandPinklyMiddle----//
	glColor3f(0, 1, 1);
	glPushMatrix();

	glTranslatef(0.1, 0, 0.0);
	// Face 1
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 2 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glEnd();
	// Face 3 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();
	// Face 4 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 �
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.05f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 �
	glBegin(GL_QUADS);
	glVertex3f(0.1f, 0.05f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.05f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();
	//----HandPinkyTop----// pyramid
	glPushMatrix();
	glColor3f(0.5, 0.5, 1);
	glTranslatef(0.2, 0.017, 0.026);
	glRotatef(-11, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	cylinder = gluNewQuadric();		//create quadric obj in the memory
	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cone
	gluCylinder(cylinder, 0.025, 0.0, 0.027, 30, 30);	//draw cone
	gluDeleteQuadric(cylinder);	//destroy the cone

	glPopMatrix();
#pragma endregion
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void display()
{

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//----Projection View & Model View----//
	projection();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//----Final draw hand----//
	glPushMatrix();

	LeftHand();
	RightHand();
	glPopMatrix();


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