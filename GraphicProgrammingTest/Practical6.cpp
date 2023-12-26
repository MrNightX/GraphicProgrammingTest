/* However Everyone Like Pasta May Enjoy*/

#include <Windows.h>
#include <gl/GL.h> 
#include <math.h>
#include <gl/GLU.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"
//Common global edits
float Tx = 0.0f;
float Ty = 0.0f;
float T_Red = 0.0;
float T_Green = 1.0;
float T_Blue = 0.0;
int SwitchNum = 0;

float Tz = 0;
float T_Speed = 0.2;  //Translate for Model View
bool IsOrtho = true; // is Ortho View
float O_Near = -10.0f, O_Far = 10.0f; //Ortho near and far

float P_Near = 1.0f, P_Far = 21.0f; //Perspective Near & Far
float s1Rad = 3.0f;

//Moving the camera projection position
float P_Tx = 0, P_Ty = 0;

//Lighting Section
float AmbientLight[3]= { 1.0, 0.0, 0.0 }; //Red Color Ambient Light
float AmbientLightPos[3] = { 0.0, 0.8, 0.0 };	//Lighting Position
float AmbientMaterial[3] = { 0.0, 0.0, 1.0 }; //Ambient Material

float DiffuseLight[3] = { 0.0, 1.0, 0.0 }; 
float DiffuseLightPos[3] = { 0.8f, 0.0f, 0.0 };	//Lighting Position
float DiffuseMaterial[3] = { 0.0, 0.0, 1.0 }; //Diffuse Material

float Light_Tx = 0.0f, Light_Ty = 0.0f, Light_Tz = 0.0f;

bool IsLightOn = true;

int ShapeChoice = 0;
float RotationDirection = 1;
float j = 1.0f;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		else if (wParam == 'W')
		{
			Light_Ty += 0.1;
		}
		else if (wParam == 'S')
		{
			Light_Ty -= 0.1;
		}
		else if (wParam == 'A')
		{
			Light_Tx += 0.1;
		}
		else if (wParam == 'D')
		{

		}
		else if (wParam == 'E')
		{

		}
		else if (wParam == 'Q')
		{

		}
		else if (wParam == VK_UP)
		{
			RotationDirection = 0;
		}
		else if (wParam == VK_DOWN)
		{
			RotationDirection = 1;
		}
		else if (wParam == VK_SPACE)
		{
			IsLightOn = !IsLightOn; //Press SPACE KEY TO TURN ON/OFF LIGHTS
		}
		else if (wParam == 'O')
		{
			ShapeChoice = 0;
		}
		else if (wParam == 'P')
		{
			ShapeChoice = 1;
		}
		else if (wParam == VK_BACK)
		{
			SwitchNum++;
			SwitchNum = SwitchNum % 8;
		}
		
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


void DrawCircle(float Coordinate_X, float Coordinate_Y, float Radius, float NumOfSegments, float angle)
{
	float theta;
	float RequestedAngle = angle / 360;
	float TempX;
	float TempY;

	for (int tempNum = 0; tempNum <= NumOfSegments; tempNum++)
	{
		theta = (2.0f * RequestedAngle) * 3.1415926f * tempNum / NumOfSegments;
		TempX = Radius * cos(theta);
		TempY = Radius * sin(theta);
		glVertex2f(Coordinate_X + TempX, Coordinate_Y + TempY);
	}
}

void DrawHarderCircle(float Coordinate_X2, float Coordinate_Y2, float Radius2, float NumOfSegments2, float StartAngle, float AngleNeeded)
{
	float theta;
	float RequestedAngle = AngleNeeded / 360;
	float TempX;
	float TempY;

	for (int i = StartAngle; i <= NumOfSegments2; i++)
	{
		theta = (2.0f * RequestedAngle) * 3.1415926f * i / NumOfSegments2;
		TempX = Radius2 * cos(theta);
		TempY = Radius2 * sin(theta);
		glVertex2f(Coordinate_X2 + TempX, Coordinate_Y2 + TempY);
	}
}

void TransformationTesting()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix(); //changes Obj 1, 2 & 3
	{
		glScalef(0.5, 0.5, 0.5);
		glPushMatrix(); //changes Obj 1 & 2
		{
			glRotatef(90, 0.0f, 0.0f, 1.0f); //Rotation Anti Clockwise
			//Obj 1: Red Triangle
			glPushMatrix();
			{
				//glRotatef(90, 0.0f, 0.0f, 1.0f); //Rotation Anti Clockwise
				glTranslatef(0.0, 0.5, 0.0); //Translate along the x and y axis
				//glScalef(0.5, 0.5, 0.5); //Scale the shape 

				glBegin(GL_TRIANGLES);
				glColor3f(1.0, 0.0, 0.0);

				glVertex2f(-0.5, 0.0);
				glVertex2f(0.0, 0.5);
				glVertex2f(0.5, 0.0);
				glEnd();
				glPopMatrix();
			}
			//Obj 2: Purple Quad
			glPushMatrix(); //Reset all the transformation
			{
				glTranslatef(-0.5, 0.0, 0.0); //Translate along the x and y axis

				glBegin(GL_QUADS);
				glColor3f(1.0, 0.0, 1.0);

				glVertex2f(-0.5, 0.2);
				glVertex2f(0.5, 0.2);
				glVertex2f(0.5, -0.2);
				glVertex2f(-0.5, -0.2);
				glEnd();
				glPopMatrix();
			}
			glPopMatrix(); // close changes to Obj 1 & 2
		}
		//Obj 3: Blue QUad 
		glPushMatrix();
		{
			glTranslatef(0.5, 0.0, 0.0); //Translate along the x and y axis

			glBegin(GL_QUADS);
			glColor3f(0.0, 0.5, 1.0);

			glVertex2f(-0.5, 0.2);
			glVertex2f(0.5, 0.2);
			glVertex2f(0.5, -0.2);
			glVertex2f(-0.5, -0.2);
			glEnd();
			glPopMatrix();

			glPopMatrix();//close changes to Obj 1, 2 & 3
		}
	}
}

void DrawPyramid(float size)
{
	glTranslatef(-size, -size/2, -size);
	glBegin(GL_POLYGON);

	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0.0f, 0.0f, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0f, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0.0f, 0.0f);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0, 0, 0);

	glEnd();
	//do smtg
}

void DrawSphere(float Radius)
{
	//glRotatef(0.1, 1.0, 1.0, 1.0);

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FLAT); //change drawing style

	gluSphere(sphere, Radius, 50, 50); //DRAW the sphere

	gluDeleteQuadric(sphere); // Destroy the object

}

void DrawCylinder(float br, float tr, float h)
{
	glRotatef(0.1, 1.0, 1.0, 1.0);

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glColor3f(1.0, 0.5f, 0.0);
	glRotatef(0.1, 1.0, 1.0, 1.0);

	gluQuadricDrawStyle(cylinder, GLU_LINE); //change drawing style
	gluCylinder(cylinder, br, tr, h, 30, 30);
	gluDeleteQuadric(cylinder); // Destroy the object
}

void DrawDisk(float Inner_Radius, float Outer_Radius)
{
	glRotatef(0.1, 1.0, 1.0, 1.0);

	glPushMatrix();
	GLUquadricObj* disk = NULL;
	disk = gluNewQuadric();
	glColor3f(1.0f, 1.0f, 0.0f);

	gluQuadricDrawStyle(disk, GLU_LINE); //change drawing style
	gluDisk(disk, Inner_Radius, Outer_Radius, 30, 30);
	gluDeleteQuadric(disk); // Destroy the object
	glPopMatrix();


}

void DrawCube(float Length, float Width, float Height, float r, float g, float b)
{
	GLUquadricObj* cube = NULL;
	cube = gluNewQuadric();
	glColor3f(r, g, b);

	gluQuadricDrawStyle(cube, GLU_FLAT);

}

void Projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glTranslatef(P_Tx, P_Ty, 0.0f);
	if (IsOrtho)
	{
		//Ortho View
		glOrtho(-10.0, 10.0, -10.0, 10.0, O_Near, O_Far);
	}
	else
	{
		//Perspective view
		gluPerspective(20, 1.0f, -1.0f, 1.0f);
		glFrustum(-10.0, 10.0, -10.0, 10.0, P_Near, P_Far);
	}
	//DrawCylinder(0.5f, 0.5f, 2.0f);
}

void Lighting()
{
	if (IsLightOn)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}

void Practical6_Demo() //DEMO
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glRotatef(0.1f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_LIGHTING);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, AmbientLightPos);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, DiffuseLightPos);
	glEnable(GL_LIGHT1);

	glColor3f(0.0f, 0.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientMaterial); //blue
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseMaterial); //BLue
	DrawSphere(0.5f);
}

void Practical6_Q1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	
	if (RotationDirection == 0) //Clockwise Spinning
	{
		j--;
	}
	else if (RotationDirection == 1) //Anti Clockwise spinning
	{
		j++; //in computer, RAD spins in anti clockwise direction
	}
	glRotatef(j, 1.0f, 1.0f, 1.0f);

	if (IsLightOn)
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, AmbientLightPos);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_POSITION, DiffuseLightPos);
	glEnable(GL_LIGHT1);

	glColor3f(0.0f, 0.7f, 1.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, AmbientMaterial); //blue
	glMaterialfv(GL_FRONT, GL_DIFFUSE, DiffuseMaterial); //BLue
	
	if (ShapeChoice == 0)
	{
		DrawSphere(0.5f);
	}
	else if (ShapeChoice == 1)
	{
		DrawPyramid(0.5f);
	}
}

void DemoCode()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Projection();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(Tx, 0.0f, Tz);
	DrawCylinder(3.0f, 0.5f, 2.0f);
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	//DemoCode();
	//Practical6_Demo();
	Practical6_Q1();
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
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

	if (!RegisterClassEx(&wc))
		return false;

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
	if (!wglMakeCurrent(hdc, hglrc))
		return false;

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
