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
float headRotate = 0;
float headRotate2 = 0;
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
			/*case VK_LEFT:
				if (armRotate3 > -90) armRotate3 -= ROTATION_INCREMENT;
				if (armRotate3 < -90) armRotate3 = -90;
				break;
			case VK_RIGHT:
				if (armRotate3 < 90) armRotate3 += ROTATION_INCREMENT;
				if (armRotate3 > 90) armRotate3 = 90;
				break;*/
			case VK_H:
				if (armRotate3 < 20) armRotate3 += ROTATION_INCREMENT;
				if (armRotate3 > 20) armRotate3 = 20;
				break;
			case VK_F:
				if (armRotate3 > -20) armRotate3 -= ROTATION_INCREMENT;
				if (armRotate3 < -20) armRotate3 = -20;
				break;
			case VK_G:
				if (armRotate2 < 40) armRotate2 += ROTATION_INCREMENT;
				if (armRotate2 > 40) armRotate2 = 40;
				break;
			case VK_T:
				if (armRotate2 > -10) armRotate2 -= ROTATION_INCREMENT;
				if (armRotate2 < -10) armRotate2 = -10;
				break;
			case VK_I:
				if (headRotate > -60) headRotate -= ROTATION_INCREMENT;
				if (headRotate < -60) headRotate = -60;
				break;
			case VK_K:
				if (headRotate < 30) headRotate += ROTATION_INCREMENT;
				if (headRotate > 30) headRotate = 30;
				break;
			case VK_J:
				if (headRotate2 > -80) headRotate2 -= ROTATION_INCREMENT;
				if (headRotate2 < -80) headRotate2 = -80;
				break;
			case VK_L:
				if (headRotate2 < 80) headRotate2 += ROTATION_INCREMENT;
				if (headRotate2 > 80) headRotate2 = 80;
				break;
			case VK_SPACE:
				armRotate = armRotate2 = armRotate3 = 0;
				headRotate = headRotate2 = 0;
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

void drawSidedTriangle(float Length, float Width, float thickness) // have centering function
{
	glPushMatrix();
	glTranslatef(0.0, -Width / 2, 0);
	//front face
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-Length / 2, 0.0, -thickness / 2);
	glVertex3f(Length / 2, 0.0, -thickness / 2);
	glVertex3f(0.0, Width, -thickness / 2);

	glEnd();

	//back face
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-Length / 2, 0.0, thickness / 2);
	glVertex3f(0.0, Width, thickness / 2);
	glVertex3f(Length / 2, 0.0, thickness / 2);


	glEnd();

	//filling
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-Length / 2, 0.0, -thickness / 2);
	glVertex3f(-Length / 2, 0.0, thickness / 2);
	glVertex3f(Length / 2, 0.0, thickness / 2);
	glVertex3f(Length / 2, 0.0, -thickness / 2);

	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(Length / 2, 0.0, -thickness / 2);
	glVertex3f(Length / 2, 0.0, thickness / 2);
	glVertex3f(0.0, Width, thickness / 2);
	glVertex3f(0.0, Width, -thickness / 2);

	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, Width, -thickness / 2);
	glVertex3f(0.0, Width, thickness / 2);
	glVertex3f(-Length / 2, 0.0, thickness / 2);
	glVertex3f(-Length / 2, 0.0, -thickness / 2);

	glEnd();

	glPopMatrix();
}

void drawRightTriangle(float OnX, float OnY, float thickness) //1st point is on the origin, have centering function
{
	glPushMatrix();
	glTranslatef(-OnX / 2, -OnY / 2, 0);
	//front face
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.0, -thickness / 2);
	glVertex3f(OnX, 0.0, -thickness / 2);
	glVertex3f(0.0, OnY, -thickness / 2);

	glEnd();

	//back face
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.0, thickness / 2);
	glVertex3f(0.0, OnY, thickness / 2);
	glVertex3f(OnX, 0.0, thickness / 2);


	glEnd();

	//filling
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.0, -thickness / 2);
	glVertex3f(0.0, 0.0, thickness / 2);
	glVertex3f(OnX, 0.0, thickness / 2);
	glVertex3f(OnX, 0.0, -thickness / 2);

	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(OnX, 0.0, -thickness / 2);
	glVertex3f(OnX, 0.0, thickness / 2);
	glVertex3f(0.0, OnY, thickness / 2);
	glVertex3f(0.0, OnY, -thickness / 2);

	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(P1x, P1y, Thickness / 2);
	glVertex3f(P2x, P2y, Thickness / 2);
	glVertex3f(P3x, P3y, Thickness / 2);

	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(P1x, P1y, Thickness / 2);
	glVertex3f(P2x, P2y, Thickness / 2);
	glVertex3f(P2x, P2y, -Thickness / 2);
	glVertex3f(P1x, P1y, -Thickness / 2);

	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(P1x, P1y, -Thickness / 2);
	glVertex3f(P2x, P2y, -Thickness / 2);
	glVertex3f(P3x, P3y, -Thickness / 2);

	glEnd();
	glPopMatrix();
}

void drawCube(float x, float y, float z) // keep in mind that the cube will always draw and center on the origin, but the z is pointing away from ... you
{
	float P_X = x / 2, P_Y = y / 2, P_Z = z / 2;
	glPushMatrix();
	glTranslatef(-P_X, -P_Y, P_Z);


	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);//ps: I made sure this can be safely converted into GL_Polygon
	glVertex3f(0, 0, 0); //front
	glVertex3f(0, y, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x, 0, 0);
	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(x, y, -z); //top
	glVertex3f(x, y, 0);
	glVertex3f(0, y, 0);
	glVertex3f(0, y, -z);
	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(x, 0, -z); //back
	glVertex3f(x, y, -z);
	glVertex3f(0, y, -z);
	glVertex3f(0, 0, -z);
	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -z);  //bottom
	glVertex3f(0, 0, 0);
	glVertex3f(x, 0, 0);
	glVertex3f(x, 0, -z);
	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	//left side
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -z);
	glVertex3f(0, y, -z);
	glVertex3f(0, y, 0);
	glEnd();

	//glPolygonMode(GL_FRONT, GL_LINE);
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
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, TopWidthSize / 2);
	glVertex3f(-TopSize / 2, height / 2, TopWidthSize / 2);

	glEnd();

	//Bottom
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, BottomWidthSize / 2);

	glEnd();

	//front
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, -TopWidthSize / 2);

	glEnd();
	//right
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(TopSize / 2, height / 2, -TopWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(TopSize / 2, height / 2, TopWidthSize / 2);

	glEnd();
	//back
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(TopSize / 2, height / 2, TopWidthSize / 2);
	glVertex3f(BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(-TopSize / 2, height / 2, TopWidthSize / 2);

	glEnd();
	//left
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-TopSize / 2, height / 2, TopWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, BottomWidthSize / 2);
	glVertex3f(-BottomSize / 2, -height / 2, -BottomWidthSize / 2);
	glVertex3f(-TopSize / 2, height / 2, -TopWidthSize / 2);

	glEnd();
	glPopMatrix(); //need to thank Jason for fixing them :)
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

void drawCylinder(float tR, float bR, float h) 
{

	GLUquadricObj* cylinder = NULL;	//declare quadric obj pointer
	cylinder = gluNewQuadric();		//create quadric obj in the memory

	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cylinder

	gluCylinder(cylinder, bR, tR, h, 30, 30);	//draw cylinder
	gluDeleteQuadric(cylinder);	//destroy the cylinder
}

void drawCircle(float x, float y) 
{

	for (float angle = 0; angle <= 3.142 * 2; angle += 3.142 * 2 / 30) {
		x = -0.6 + 0.1 * cos(angle);
		y = 0.1 * sin(angle);
		glVertex2f(x, y);
	}
}

void Head()
{
	glPushMatrix();
	glRotatef(headRotate, 1.0, 0.0, 0.0);
	glRotatef(headRotate2, 0.0, 1.0, 0.0);

	// Start Drawing Shapes
	/*glBindTexture(GL_TEXTURE_2D, textures[3]);*/

	glColor3f(0.2, 0.2, 0.2);
	drawSphere(0.25);
#pragma region Eyes
	glPushMatrix();
	glTranslatef(-0.1, 0.05, 0.25);
	glColor3f(0.5, 0.0, 0.0);
	drawSphere(0.08);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.1, 0.05, 0.25);
	glColor3f(0.5, 0.0, 0.0);
	drawSphere(0.08);

	glPopMatrix();
#pragma endregion
#pragma region Mouth
	//glBindTexture(GL_TEXTURE_2D, textures[1]);
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.22, 0.05, 0.12);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.22, -0.05, 0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.18, -0.05, 0.22);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.18, -0.1, 0.21);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.12, -0.05, 0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.12, -0.2, 0.25);

	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, -0.07, 0.35);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -0.22, 0.3);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.12, -0.05, 0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.12, -0.2, 0.25);

	glTexCoord2f(1.0, 1.0); glVertex3f(0.18, -0.05, 0.22);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.18, -0.1, 0.21);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.22, 0.05, 0.12);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.22, -0.05, 0.15);

	glEnd();

	glBegin(GL_QUAD_STRIP);

	glVertex3f(-0.22, 0.05, 0.12);
	glVertex3f(-0.2, 0.05, 0.12);
	glVertex3f(-0.18, -0.05, 0.22);
	glVertex3f(-0.15, -0.05, 0.22);

	glVertex3f(-0.12, -0.05, 0.3);
	glVertex3f(-0.1, -0.05, 0.2);

	glVertex3f(0.0, -0.07, 0.35);
	glVertex3f(0.0, -0.07, 0.2);

	glVertex3f(0.12, -0.05, 0.3);
	glVertex3f(0.1, -0.05, 0.2);

	glVertex3f(0.18, -0.05, 0.22);
	glVertex3f(0.15, -0.05, 0.22);

	glVertex3f(0.22, 0.05, 0.12);
	glVertex3f(0.2, 0.05, 0.12);

	glEnd();
	//glBindTexture(GL_TEXTURE_2D, textures[0]);

	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.25, -0.05, 0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.25, -0.15, 0.05);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.2, -0.1, 0.21);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.2, -0.2, 0.15);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.2, 0.25);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.13, -0.25, 0.2);

	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, -0.2, 0.33);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -0.3, 0.30);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.2, 0.25);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.13, -0.25, 0.2);

	glTexCoord2f(1.0, 1.0); glVertex3f(0.2, -0.1, 0.21);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.2, -0.2, 0.15);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.25, -0.05, 0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.25, -0.15, 0.05);

	glEnd();

	glBegin(GL_QUAD_STRIP);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.25, -0.05, 0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.20, -0.05, 0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.2, -0.1, 0.21);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.15, -0.1, 0.21);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.15, -0.2, 0.25);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, -0.2, 0.25);

	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, -0.2, 0.33);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -0.2, 0.3);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.15, -0.2, 0.25);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, -0.2, 0.25);

	glTexCoord2f(1.0, 1.0); glVertex3f(0.2, -0.1, 0.21);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.15, -0.1, 0.21);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.25, -0.05, 0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.20, -0.05, 0.15);

	glEnd();
#pragma endregion
#pragma region Left Face
	//	Face Side Plate 1
	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(-0.28, 0.1, -0.3);
	glRotatef(10, 0.0, 0.0, 1.0);
	glRotatef(-10, 1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, -0.05);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.4, -0.15);
	glTexCoord2f(1.0, 0.5); glVertex3f(0, 0.0, 0.45);

	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.0, 0.45);
	glTexCoord2f(1.0, 1.0); glVertex3f(0, -0.15, 0.44);
	glTexCoord2f(1.0, 0.0); glVertex3f(0, -0.3, 0.2);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0.0, 0.45);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.0, 0.45);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.1, 0.25, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0, 0.4, -0.15);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.25, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.4, -0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(0, 0, -0.05);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.1, 0, 0);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, -0.05);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0, 0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.1, 0, 0.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(0, 0, 0.05);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, -0.15, 0.44);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, -0.3, 0.2);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.1, -0.3, 0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.1, -0.15, 0.44);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, -0.15, 0.44);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, -0.15, 0.44);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.1, 0.0, 0.45);
	glTexCoord2f(1.0, 0.0); glVertex3f(0, 0.0, 0.45);

	//glBindTexture(GL_TEXTURE_2D, textures[3]);

	glColor3f(0.6, 0.6, 0.6);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.15, 0.20);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.3, 0.1, 0.25);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.3, 0, 0.45);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, -0.02, 0.45);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.15, 0.20);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.3, 0.1, 0.25);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.3, 0, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, -0.02, 0);
	glEnd();

#pragma endregion
#pragma region Right Face

	glPopMatrix();

	// Face side plate 2

	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(0.28, 0.1, -0.3);
	glRotatef(-10, 0.0, 0.0, 1.0);
	glRotatef(-10, 1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, -0.05);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.4, -0.15);
	glTexCoord2f(1.0, 0.5); glVertex3f(0, 0.0, 0.45);

	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.0, 0.45);
	glTexCoord2f(1.0, 1.0); glVertex3f(0, -0.15, 0.44);
	glTexCoord2f(1.0, 0.0); glVertex3f(0, -0.3, 0.2);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0.0, 0.45);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, 0.0, 0.45);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.1, 0.25, 0.0);
	glVertex3f(0, 0.4, -0.15);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 0.25, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.4, -0.15);
	glTexCoord2f(1.0, 1.0); glVertex3f(0, 0, -0.05);
	glVertex3f(-0.1, 0, 0);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, -0.05);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, 0, 0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.1, 0, 0.1);
	glVertex3f(0, 0, 0.05);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, -0.15, 0.44);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, -0.3, 0.2);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.1, -0.3, 0.2);
	glVertex3f(-0.1, -0.15, 0.44);

	glTexCoord2f(0.0, 0.0); glVertex3f(0, -0.15, 0.44);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, -0.15, 0.44);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.1, 0.0, 0.45);
	glVertex3f(0, 0.0, 0.45);

	glColor3f(0.6, 0.6, 0.6);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 0.15, 0.20);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.3, 0.1, 0.25);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.3, 0, 0.45);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, -0.02, 0.45);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 0.15, 0.20);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.3, 0.1, 0.25);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.3, 0, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, -0.02, 0);

	glEnd();

	glPopMatrix();
#pragma endregion 
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.22, 0.15, 0.12);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.25, 0.07, 0.05);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.22, 0.15, 0.12);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.25, 0.07, 0.05);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.22, 0.15, 0.12);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.25, 0.07, 0.05);

	glEnd();
	//right chin
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	glPushMatrix();
	glTranslatef(0.235, -0.16, -0.05);
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0, 0, -0.15);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.04, 0.3, -0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.04, 0.3, 0);
	glEnd();
	glPopMatrix();
	//left chin
	glPushMatrix();
	glTranslatef(-0.235, -0.16, -0.05);
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0, 0, -0.15);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.04, 0.3, -0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.04, 0.3, 0);
	glEnd();
	glPopMatrix();
	//back head
	glPushMatrix();
	glTranslatef(0.235, -0.16, -0.2);
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.47, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.52, 0.3, -0.15);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.05, 0.3, -0.15);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}
void Shoudler() {

#pragma region shoulder sphere
	glPushMatrix();
	glColor3f(0.6, 0, 0.6);
	glTranslatef(0.95, 0.29, 0);
	GLUquadricObj* sphere = NULL;			//declare quadric obj pointer
	sphere = gluNewQuadric();				//create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//draw using line
	gluSphere(sphere, 0.25, 30, 30);         //draw sphere
	gluDeleteQuadric(sphere);				//destroy obj
	//-------------------------------------------------------------------------------
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.6, 0, 0.6);
	glTranslatef(-0.95, 0.29, 0);
	sphere = gluNewQuadric();				//create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//draw using line
	gluSphere(sphere, 0.25, 30, 30);         //draw sphere
	gluDeleteQuadric(sphere);				//destroy obj
	//-------------------------------------------------------------------------------
	glPopMatrix();
#pragma endregion
#pragma region armpit
	//left side
	//top
	glPushMatrix();
	glScalef(1.50,1.001,1.0);
	glTranslatef(0-.1,0,0);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(1, 0.5, 0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.3, 0.5, 0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.3, 0.5, -0.20);
	glTexCoord2f(0.0, 1.0); glVertex3f(1, 0.5, -0.20);
	glEnd();
	//front
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(1, 0.5, 0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.3, 0.5, 0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.3, 0.2, 0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.8, 0.2, 0.2);
	glEnd();
	//back
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(1, 0.5, -0.20);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.3, 0.5, -0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.3, 0.2, -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.8, 0.2, -0.1);
	glEnd();
	//bottom
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.3, 0.2, 0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.8, 0.2, 0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.8, 0.2, -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.3, 0.2, -0.1);
	glEnd();
	//side
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(1, 0.5, 0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(1, 0.5, -0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.8, 0.2, -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.8, 0.2, 0.2);
	glEnd();
	glPopMatrix();
	//rightside
	//top
	glPushMatrix();
	glScalef(1.50, 1.001, 1.0);
	glTranslatef(0.1, 0, 0);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1, 0.5, 0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.3, 0.5, 0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.3, 0.5, -0.20);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1, 0.5, -0.20);
	glEnd();
	//front
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1, 0.5, 0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.3, 0.5, 0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.3, 0.2, 0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.8, 0.2, 0.2);
	glEnd();
	//back
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1, 0.5, -0.20);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.3, 0.5, -0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.3, 0.2, -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.8, 0.2, -0.1);
	glEnd();
	//bottom
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.3, 0.2, 0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.8, 0.2, 0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.8, 0.2, -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.3, 0.2, -0.1);
	glEnd();
	//side
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1, 0.5, 0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(-1, 0.5, -0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.8, 0.2, -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.8, 0.2, 0.2);
	glEnd();
	glPopMatrix();
#pragma endregion

}
void LeftHand() 
{
	glLoadIdentity();
	glPushMatrix();
	glScalef(1.4,1.4,1.8);
	glTranslatef(-0.78,0.26,-0.1);
	glRotatef(-100, 0.0, 0.0, 1.0);     //rotate 90 degrees so taht arm is down
	glPushMatrix();
	glRotatef(-armRotate2, 0.0, 0.0, 1.0);
	glRotatef(-armRotate3, 0.0, 1.0, 0.0);
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
	glLoadIdentity();
	glPushMatrix();
	glScalef(1.4, 1.4, 1.8);
	glRotatef(-80, 0.0, 0.0, 1.0);     //rotate 90 degrees so taht arm is down
	glTranslatef(-0.1, 0.8,-0.1);
	glPushMatrix();
	glRotatef(armRotate2, 0.0, 0.0, 1.0);
	glRotatef(armRotate3, 0.0, 1.0, 0.0);
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
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
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
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.5f, 0.0f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.2f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.5f, -0.2f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
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
	// Face 2 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.1f, 0.0f, 0.2f);
	glVertex3f(0.1f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glEnd();
	// Face 3 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.1f, -0.2f, 0.2f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glEnd();
	// Face 4 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 5 …
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.2f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	// Face 6 …
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
void Body() 
{
#pragma region middle sphere
	//middle sphere
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	GLUquadricObj* sphere = NULL;			//declare quadric obj pointer
	sphere = gluNewQuadric();				//create quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//draw using line
	gluSphere(sphere, 0.25, 30, 30);         //draw sphere
	gluDeleteQuadric(sphere);	//destroy obj
	glPopMatrix();
#pragma endregion
	glTranslatef(-0.5, -0.5, 0.6);

#pragma region neck
	glPushMatrix(); glRotatef(90, 1.0, 0.0, 0.0); glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.5, -0.6, -1.5);
	GLUquadricObj* cylinder = NULL;	//declare quadric obj pointer
	cylinder = gluNewQuadric();		//create quadric obj in the memory
	//gluQuadricDrawStyle(cylinder, GLU_LINE);	//draws outline on the cylinder
	gluCylinder(cylinder, 0.15, 0.15, 0.5, 30, 30);	//draw cylinder
	gluDeleteQuadric(cylinder);	//destroy the cylinder
	glPopMatrix();
#pragma endregion
#pragma region front
	//----front
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.2, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.9, 0.2, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.8, 0.8, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.2, 0.8, 0);
	glEnd();
#pragma endregion
#pragma region abs
	//----abs
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.2, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.9, 0.2, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.9, 0.05, -0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.05, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.2, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.9, 0.2, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.9, 0.05, -0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.05, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.05, -0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.1, 0.05, -0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.1, -0.45, -0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.9, -0.45, -0.2);
	glEnd();
	//abs left
	glBegin(GL_QUADS);
	glColor3f(0.6, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.05, -0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.1, 0.05, -0.7);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.1, -0.45, -0.7);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, -0.45, -0.2);
	glEnd();
	//abs right
	glBegin(GL_QUADS);
	glColor3f(0.6, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.05, -0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.9, 0.05, -0.7);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.9, -0.45, -0.7);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.9, -0.45, -0.2);
	glEnd();
	//abs back
	glBegin(GL_QUADS);
	glColor3f(0.6, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.05, -0.7);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.9, 0.05, -0.7);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.9, -0.45, -0.7);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, -0.45, -0.7);
	glEnd();
	//abs cover
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.3, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, -0.45, -0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.9, -0.45, -0.2);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.9, -0.45, -0.7);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, -0.45, -0.7);
	glEnd();
#pragma endregion
#pragma region left
	//----left
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.2, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.8, 0.8, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, -0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.1, 0.4, -0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.2, 0);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.9, 0.05, -0.2);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.1, 0.4, -0.3);
	glEnd();
#pragma endregion
#pragma region right
	//----right
	glBegin(GL_QUADS);
	glColor3f(1, 0, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.2, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.2, 0.8, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 1.0, -0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, 0.4, -0.3);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0, 0.5 );
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.2, 0);
	glTexCoord2f(0.5, 0.5); glVertex3f(-0.1, 0.4, -0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.05, -0.2);
	glEnd();
#pragma endregion	
#pragma region left side
	//----left side
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, -0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(1.1, 0.4, -0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.1, 0.4, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, -0.8);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.1, 0.4, -0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(1.1, 0.4, -0.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 0.4, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 0.4, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.05, -0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(1.0, 0.4, -0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 0.4, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.9, 0.05, -0.8);
	glEnd();
#pragma endregion
#pragma region right side
	//----right side
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 1.0, -0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.1, 0.4, -0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.1, 0.4, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 1.0, -0.8);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 0.4, -0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.1, 0.4, -0.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(0, 0.4, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.4, -0.3);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.1, 0.05, -0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(0, 0.4, -0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(0, 0.4, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.05, -0.8);
	glEnd();
#pragma endregion	
#pragma region back

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.2);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.1, 0.3, -0.8);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.1, 0.3, -0.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.1, 0.4, -0.9);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.1, 0.4, -0.9);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 0.4, -0.9);
	glTexCoord2f(0.5, 1.0); glVertex3f(1.1, 0.4, -0.9);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.1, 0.9, -0.9);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, 0.9, -0.9);
	glEnd();



	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.2);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.1, 1, -0.8);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.1, 1, -0.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.1, 0.9, -0.9);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.1, 0.9, -0.9);
	glEnd();
	//inside
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0.8);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.1, 1, -0.8);
	glTexCoord2f(0.5, 0.5); glVertex3f(1, 1, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.1, 0.4, -0.8);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0.8);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 1, -0.8);
	glTexCoord2f(0.5, 0.5); glVertex3f(0, 1, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.10, 0.4, -0.8);

	glEnd();
	//left
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.8);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.1, 1, -0.8);
	glTexCoord2f(0.5, 1.0); glVertex3f(1.1, 0.9, -0.9);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.1, 0.4, -0.9);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.1, 0.3, -0.8);
	glEnd();
	//right
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0.8);
	glTexCoord2f(0.0, 0.0); glVertex3f(-0.1, 1, -0.8);
	glTexCoord2f(0.5, 1.0); glVertex3f(-0.1, 0.9, -0.9);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.1, 0.4, -0.9);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.1, 0.3, -0.8);
	glEnd();

#pragma endregion
#pragma region inside
	//----inside
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 1.0, -0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(0, 1.0, -0.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, -0.3);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, 1.0, -0.3);
	glTexCoord2f(0.5, 1.0); glVertex3f(0, 1.0, -0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.2, 0.8, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.8, 0.8, 0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.05, -0.2);
	glTexCoord2f(0.5, 1.0); glVertex3f(1.1, 0.4, -0.3);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.1, 0.4, -0.3);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.05, -0.2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.05, -0.8);
	glTexCoord2f(0.5, 1.0); glVertex3f(1.1, 0.4, -0.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.1, 0.4, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.05, -0.8);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0); glVertex3f(0.9, 0.05, -0.7);
	glTexCoord2f(0.5, 1.0); glVertex3f(0.9, 0.05, -0.8);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.1, 0.05, -0.8);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.1, 0.05, -0.7);
	glEnd();
#pragma endregion
}
void UpperBody()
{
#pragma region UpperBody

	glPushMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.9, 0.0);
	Head();
	Shoudler();
	glPopMatrix();
	glPushMatrix();
	LeftHand();
	RightHand();
	glPopMatrix();
	glPushMatrix();
	Body();
	glPopMatrix();
	glPushMatrix();
	glPopMatrix();

	glPopMatrix();

#pragma endregion
}

void leg(float AnimationControl)
{
	glPushMatrix();

	glRotatef(AnimationControl, 1.0, 0.0, 0.0);

	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, -0.825f, 0); //original transformation

	//glTranslatef(0, -0.4f, 0.0f); //focusing on that thicc thigh
	//glTranslatef(0, 0.3f, 0.0f); // focusing on those slender shin
	//dear viewers, pls do not look at me with weird eyes, i swear im just joking... hehe
	glPushMatrix();
	glTranslatef(0.0, 0.85, 0.0);
	glScalef(-1.5, 1.0, 0.75);
	glColor3f(0.5, 0.5, 0.5);
	drawIrregularCube(0.15, 0.20, 0.2);
	glPopMatrix();

	glColor3f(1, 1, 1);
#pragma region Thigh
	glPushMatrix();

	glTranslatef(0, 0.4f, 0);
	glColor3f(0.3, 0.3, 0.3);
	drawCube(0.2f, 0.7f, 0.2f);

	//Real fun begins here
	glPushMatrix();
#pragma region Thigh front armor
	glColor3f(0.5, 0.0, 1.0);
	glLineWidth(5);
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.35, -0.175); //right frontface
	glVertex3f(0.0, -0.01, -0.225);
	glVertex3f(0.0, -0.4, -0.175);
	glVertex3f(0.175, -0.1, -0.05);
	glVertex3f(0.175, 0.35, -0.05);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.35, -0.125);
	glVertex3f(0.0, -0.01, -0.205);
	glVertex3f(0.0, -0.4, -0.125);
	glVertex3f(0.175, -0.1, -0.03);
	glVertex3f(0.175, 0.35, -0.03);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.35, -0.175);
	glVertex3f(0.0, -0.01, -0.225);
	glVertex3f(0.0, -0.01, -0.205);
	glVertex3f(0.0, 0.35, -0.125);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, -0.01, -0.225);
	glVertex3f(0.0, -0.4, -0.175);
	glVertex3f(0.0, -0.4, -0.125);
	glVertex3f(0.0, -0.01, -0.205);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, -0.4, -0.175);
	glVertex3f(0.175, -0.1, -0.05);
	glVertex3f(0.175, -0.1, -0.03);
	glVertex3f(0.0, -0.4, -0.125);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.175, -0.1, -0.05);
	glVertex3f(0.175, 0.35, -0.05);
	glVertex3f(0.175, 0.35, -0.03);
	glVertex3f(0.175, -0.1, -0.03);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.175, 0.35, -0.05);
	glVertex3f(0.0, 0.35, -0.175);
	glVertex3f(0.0, 0.35, -0.125);
	glVertex3f(0.175, 0.35, -0.03);

	glEnd();

	glColor3f(0.5, 0.0, 1.0);
	glLineWidth(5);
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.35, -0.175); //left frontface
	glVertex3f(0.0, -0.01, -0.225);
	glVertex3f(0.0, -0.4, -0.175);
	glVertex3f(-0.175, -0.1, -0.05);
	glVertex3f(-0.175, 0.35, -0.05);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.35, -0.125);
	glVertex3f(0.0, -0.01, -0.205);
	glVertex3f(0.0, -0.4, -0.125);
	glVertex3f(-0.175, -0.1, -0.03);
	glVertex3f(-0.175, 0.35, -0.03);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, 0.35, -0.175);
	glVertex3f(0.0, -0.01, -0.225);
	glVertex3f(0.0, -0.01, -0.205);
	glVertex3f(0.0, 0.35, -0.125);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, -0.01, -0.225);
	glVertex3f(0.0, -0.4, -0.175);
	glVertex3f(0.0, -0.4, -0.125);
	glVertex3f(0.0, -0.01, -0.205);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(0.0, -0.4, -0.175);
	glVertex3f(-0.175, -0.1, -0.05);
	glVertex3f(-0.175, -0.1, -0.03);
	glVertex3f(0.0, -0.4, -0.125);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex3f(-0.175, -0.1, -0.05);
	glVertex3f(-0.175, 0.35, -0.05);
	glVertex3f(-0.175, 0.35, -0.03);
	glVertex3f(-0.175, -0.1, -0.03);

	glEnd();
	//glPolygonMode(GL_FRONT, GL_LINE);
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
		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.17, 0.0, 0.025);
		glVertex3f(0.0, -0.4, 0.14);
		glVertex3f(0.17, -0.75, 0.025);

		glEnd();

		glColor3f(0.0, 0.5, 1.0);
		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(0.17, 0.0, 0);
		glVertex3f(0.0, -0.4, 0);
		glVertex3f(0.17, -0.75, 0);

		glEnd();

		//back left
		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(-0.17, 0.0, 0.025);
		glVertex3f(0.0, -0.4, 0.14);
		glVertex3f(-0.17, -0.75, 0.025);

		glEnd();

		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);

		glVertex3f(-0.17, 0.0, 0);
		glVertex3f(0.0, -0.4, 0);
		glVertex3f(-0.17, -0.75, 0);

		glEnd();

		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON); //right fill
		glVertex3f(0.17, 0.0, 0.025);
		glVertex3f(0.17, 0.0, 0);
		glVertex3f(0.17, -0.75, 0);
		glVertex3f(0.17, -0.75, 0.025);
		glEnd();

		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);
		{
			glVertex3f(0.17, 0.0, 0.025);
			glVertex3f(0.17, 0.0, 0);
			glVertex3f(0.0, -0.4, 0);
			glVertex3f(0.0, -0.4, 0.14);
		}
		glEnd();

		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);
		{
			glVertex3f(0.17, -0.75, 0.025);
			glVertex3f(0.17, -0.75, 0);
			glVertex3f(0.0, -0.4, 0);
			glVertex3f(0.0, -0.4, 0.14);
		}
		glEnd();

		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON); //left fill
		glVertex3f(-0.17, 0.0, 0.025);
		glVertex3f(-0.17, 0.0, 0);
		glVertex3f(-0.17, -0.75, 0);
		glVertex3f(-0.17, -0.75, 0.025);
		glEnd();

		//glPolygonMode(GL_FRONT, GL_LINE);
		glBegin(GL_POLYGON);
		{
			glVertex3f(-0.17, 0.0, 0.025);
			glVertex3f(-0.17, 0.0, 0);
			glVertex3f(0.0, -0.4, 0);
			glVertex3f(0.0, -0.4, 0.14);
		}
		glEnd();

		//glPolygonMode(GL_FRONT, GL_LINE);
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
		glRotatef(-AnimationControl / 2, 1.0, 0.0, 0.0);
	}
	else
	{
		glRotatef(AnimationControl, 1.0, 0.0, 0.0);
	}


	glColor3f(0.5, 0.5, 0.5);

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
	glColor3f(0.3, 0.3, 0.3);
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
	glColor3f(0.5, 0.5, 0.5);
	drawRightTriangle(0.25, 0.15, 0.1);

	glPopMatrix();

	glPushMatrix(); //right front toe, but lazier
	glScalef(-1.0, 1.0, 1.0); //Just reflect them :DDD
	glTranslatef(-0.1, 0.0, -0.25);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	drawRightTriangle(0.25, 0.15, 0.1);

	glPopMatrix();

	glPushMatrix(); //left back toe

	glTranslatef(-0.1, 0.0, 0.2);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	drawRightTriangle(0.15, 0.15, 0.1);

	glPopMatrix();

	glPushMatrix(); //right back toe, but lazier... too
	glScalef(-1.0, 1.0, 1.0); //Just reflect them :DDD
	glTranslatef(-0.1, 0.0, 0.2);
	glRotatef(-90, 0.0, 1.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	drawRightTriangle(0.15, 0.15, 0.1);

	glPopMatrix();

	glPopMatrix();
#pragma endregion
	glPopMatrix();
	glPopMatrix();
}

void RightSidedWaist() //to be reflected to the other side
{
	glPushMatrix();

	//front
	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_QUADS);

	glVertex3f(0.0f, 0.05, -0.05);
	glVertex3f(0.15f, 0.05, -0.05);
	glVertex3f(0.2f, 0.0, -0.075);
	glVertex3f(0.0f, 0.0f, -0.075);

	glEnd();

	//top
	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_QUADS);

	glVertex3f(0.0f, 0.05, -0.05);
	glVertex3f(0.0f, 0.05, 0.05);
	glVertex3f(0.15f, 0.05, 0.05);
	glVertex3f(0.15f, 0.05, -0.05);

	glEnd();

	//back
	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_QUADS);

	glVertex3f(0.15f, 0.05, 0.05);
	glVertex3f(0.0f, 0.05, 0.05);
	glVertex3f(0.0f, 0.0f, 0.075);
	glVertex3f(0.2f, 0.0, 0.075);

	glEnd();

	//side
	glColor3f(0.0, 1.0, 0.5);
	glBegin(GL_QUADS);

	glVertex3f(0.15f, 0.05, -0.05);
	glVertex3f(0.15f, 0.05, 0.05);
	glVertex3f(0.2f, 0.0, 0.075);
	glVertex3f(0.2f, 0.0, -0.075);

	glEnd();

	glPushMatrix(); //the middle D

	glTranslatef(0.025, -0.075, 0.0);
	glColor3f(0.0, 0.5, 1.0);
	drawCube(0.05, 0.15, 0.16);

	glPushMatrix(); //the outer D

	glTranslatef(-0.025, 0.025, -0.075);
	glColor3f(0.0, 0.5, 1.0);
	drawCube(0.075, 0.15, 0.05);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1, 0.05, 0.05);
	glRotatef(90, 0.0, 0.0, 1.0);
	drawIrregularCube(0.1, 0.05, 0.10);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, -0.075f, 0.0f);
	glColor3f(0.0, 1.0, 0.5);
	glScalef(1.0, 1.0, 1.5);
	glRotatef(180, 1.0, 0.0, 0.0); //flip it upside down
	drawRightTriangle(0.2, 0.15, 0.1);

	glPopMatrix();
}

void Waist()
{
	glPushMatrix();
	RightSidedWaist();
	glPopMatrix();

	glPushMatrix();
	glScalef(-1.0f, 1.0, 1.0);
	RightSidedWaist();
	glPopMatrix();
}

void LowerBody()
{
#pragma region LowerBody	

	glPushMatrix();
	glTranslatef(0.0, -1.1, 0.1);
	glScalef(3.25, 3.0, 3.25);
	glRotatef(180, 0.0, 1.0, 0.0);
		glPushMatrix();
		Waist();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0, -0.1, 0.0);
			glPushMatrix();
			glTranslatef(-0.15f, 0.0f, 0.0f);
			glColor3f(1.0, 1.0, 1.0);
			//draw the joint
				glPushMatrix();
				glTranslatef(0.02f, 0.05f, 0.0f);
				glColor3f(0.3, 0.3, 0.3);
				drawSphere(0.05f);
				glPopMatrix();

			leg(armRotate3); // left leg controller
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.15f, 0.0f, 0.0f);
			glColor3f(1.0, 1.0, 1.0);
			//draw the joint
				glPushMatrix();
				glTranslatef(-0.02f, 0.05f, 0.0f);
				glColor3f(0.3, 0.3, 0.3);
				drawSphere(0.05f);
				glPopMatrix();
			leg(-armRotate3); // right leg controller
		glPopMatrix();
	glPopMatrix();

	glPopMatrix();//i cant explain this 
#pragma endregion 
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
	
	UpperBody();
	LowerBody();
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

//Diamond
//glColor3f(0.8, 1.0, 0.8);
//
//glPushMatrix();
//glTranslatef(0.0, 0.1, 0.4);
//glRotatef(-10, 1.0, 0.0, 0.0);
//glBindTexture(GL_TEXTURE_2D, textures[4]);
//
//glBegin(GL_TRIANGLE_FAN);
//
//glTexCoord2f(0.5, 0.5); glVertex3f(0.0, 0.0, 0.02);
//
//glColor3f(0.2, 1.0, 0.5);
//glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.07, 0.0);
//glTexCoord2f(0.0, 0.1); glVertex3f(0.02, 0.0, 0.0);
//glTexCoord2f(0.1, 0.1); glVertex3f(0.0, -0.07, 0.0);
//glTexCoord2f(0.1, 0.0); glVertex3f(-0.02, 0.0, 0.0);
//glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.07, 0.0);
//
//glEnd(); */

	//	Head Pipe
	//glBindTexture(GL_TEXTURE_2D, textures[1]);

	//glColor3f(0.5, 0.5, 0.5);

	//glPushMatrix();
	//glTranslatef(-0.3, -0.15, -0.1);
	//glRotatef(10, 0.0, 0.0, 1.0);
	//glRotatef(90, 0.0, 1.0, 0.0);

	//drawCylinder(0.2, 0.2, 0.4);
	//drawCircle(0.2,0.2);

	//glColor3f(0.3, 0.3, 0.3);
	//glPushMatrix();
	//glTranslatef(0.0, 0.0, -0.001);

	//drawCircle(0.15,0.15);

	//glPopMatrix();

	//glPopMatrix();

	//glColor3f(0.5, 0.5, 0.5);

	/*glPushMatrix();
	glTranslatef(0.3, -0.15, -0.1);
	glRotatef(170, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, 0.0);

	drawCylinder(0.2, 0.2, 0.4);
	drawCircle(0.2,0.2);

	glColor3f(0.3, 0.3, 0.3);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.001);

	drawCircle(0.15,0.15);

	glPopMatrix();*/

	//	Horn
		//glBindTexture(GL_TEXTURE_2D, textures[5]);
		/*glColor3f(0.8, 0.8, 0.0);

		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(0.0, 0.0); glVertex3f(-0.25, 0.07, 0.05);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.22, 0.15, 0.12);
		glTexCoord2f(0.5, 1.0); glVertex3f(-0.2, 0, 0.3);

		glTexCoord2f(1.0, 0.0); glVertex3f(0, 0.1, 0.4);

		glTexCoord2f(0.0, 0.0); glVertex3f(0, -0.1, 0.45);

//		glEnd();*/
//glColor3f(0.6, 0.6, 0.6);
//
//glBegin(GL_TRIANGLE_FAN);
//
//glTexCoord2f(1.0, 0.5); glVertex3f(0, 0.4, 0.35);
//
//glTexCoord2f(0.0, 0.0); glVertex3f(0.22, 0.15, 0.12);
//glTexCoord2f(0.0, 1.0); glVertex3f(0, 0.1, 0.4);
//glTexCoord2f(0.0, 0.0); glVertex3f(-0.22, 0.15, 0.12);
//
//glEnd();
//
//glBegin(GL_TRIANGLE_FAN);
//
//glTexCoord2f(0.5, 1.0); glVertex3f(0, 0.6, 0.0);
//
//glTexCoord2f(1.0, 0.0); glVertex3f(0.22, 0.15, 0.12);
//glTexCoord2f(0.0, 0.0); glVertex3f(0, 0.4, 0.35);
//glTexCoord2f(1.0, 0.0); glVertex3f(-0.22, 0.15, 0.12);
//glTexCoord2f(0.0, 0.0); glVertex3f(0.22, 0.15, 0.12);
//
//glEnd();
