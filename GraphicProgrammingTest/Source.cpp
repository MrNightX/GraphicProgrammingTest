/* However Everyone Like Pasta May Enjoy*/

#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

 float Tx;
 float Ty;
 int SwitchNum = 0;

 float T_Red = 1.0f, T_Green = 0.0f, T_Blue = 0.0f;
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

			else if (wParam == VK_BACK)
			{
				SwitchNum++;
				SwitchNum = SwitchNum % 6;
			}

			else if (wParam == VK_LEFT)
			{
				Tx -= 0.01;
			}

			else if (wParam == VK_RIGHT)
			{
				Tx += 0.01;
			}

			else if (wParam == VK_UP)
			{
				Ty += 0.01;
			}

			else if (wParam == VK_DOWN)
			{
				Ty -= 0.01;
			}

			else if (wParam == VK_SPACE)
			{
				Tx = 0.0f;
				Ty = 0.0f;

				T_Red = 1.0f;
				T_Green = 1.0f;
				T_Blue = 1.0f;
			}

			else if (wParam == 'R')
			{
				T_Red = 1.0f;
				T_Green = 0.0f;
				T_Blue = 0.0f;
			}

			else if (wParam == 'G')
			{
				T_Red = 0.0f;
				T_Green = 1.0f;
				T_Blue = 0.0f;
			}

			else if (wParam == 'B')
			{
				T_Red = 0.0f;
				T_Green = 0.0f;
				T_Blue = 1.0f;
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

void PahangFlag()
{
	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, 0.0);
	glVertex2f(-0.5, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.5, 0.0);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();

	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();
}

void N9Flag()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 0.0); //YELLOW
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();

	glBegin(GL_TRIANGLES);
	{
		glColor3f(0.0, 0.0, 0.0); //Black

		glVertex2f(-0.5, 0.3);
		glVertex2f(0.0, 0.0);
		glVertex2f(-0.5, 0.0);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0, 0.0, 0.0); //RED

		glVertex2f(-0.5, 0.3);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 0.3);
	}
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();
}

void EnglandFlag()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.1, 0.1); //RED background
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();

	//White Rectangle 1
	glBegin(GL_QUADS);

	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(-0.5, 0.3);

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(-0.05, 0.3);
	
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.05, 0.05);

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(-0.5, 0.05);

	glEnd();

	//White Rectangle 2
	glBegin(GL_QUADS);

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(0.05, 0.3);

	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(0.5, 0.3);	

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(0.5, 0.05);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.05 , 0.05);

	glEnd();

	//White Rectangle 3
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.05, -0.05);

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(0.5, -0.05);

	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(0.5, -0.3);

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(0.05, -0.3);

	glEnd();

	//White Rectangle 4
	glBegin(GL_QUADS);

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(-0.5, -0.05);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.05, -0.05);

	glColor3f(0.95, 0.95, 0.95);
	glVertex2f(-0.05, -0.3);

	glColor3f(0.8, 0.8, 0.8);
	glVertex2f(-0.5, -0.3);

	glEnd();

	glLineWidth(1);
	glBegin(GL_LINE_LOOP); //the Grey Frame
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();
}

void Scotland()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS); //the Blue Box
	glColor3f(0.0, 0.4, 1.0);

	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();

	glLineWidth(100);
	glBegin(GL_LINES); //the WHITE Frame
	glColor3f(1.0, 1.0, 1.0);

	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, -0.3);

	glVertex2f(0.5, 0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();

	glLineWidth(1);
	glBegin(GL_LINE_LOOP); //the Blue Frame
	glColor3f(0.0, 0.4, 1.0);
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);

	glEnd();

}

float x;
float y;
float r = 0.2f;

void JapanFlag()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < 360; i++)
	{
		x = r * cos(i);
		y = r * sin(i);
		glVertex2f(x, y);
	}
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINE_LOOP); //the Blue Frame
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(-0.5, 0.3);
	glVertex2f(0.5, 0.3);
	glVertex2f(0.5, -0.3);
	glVertex2f(-0.5, -0.3);
	glEnd();
}

void DrawCircle(float Coordinate_X, float Coordinate_Y, float Radius, float NumOfSegments , float angle)
{
	float theta;
	float RequestedAngle = angle / 360;
	float TempX;
	float TempY;

	for (int tempNum = 0; tempNum <= NumOfSegments; tempNum++)
	{
		theta = (2.0f * RequestedAngle) * 3.1415926f * tempNum/NumOfSegments;
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

void Emoji_1()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON); //base face
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	DrawCircle(0.0f, 0.0f, 0.7f, 360, 360);
	glEnd();

	glPushMatrix();
		glBegin(GL_POLYGON); //eye left
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawCircle(-0.25f, 0.2, 0.2, 30, 180);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex2f(-0.27f, 0.23f);
		glVertex2f(-0.27f, 0.3f);
			glVertex2f(-0.23f,0.3f);
			glVertex2f(-0.23f, 0.23f);
		glEnd();

		glBegin(GL_POLYGON); //lid eye left
		glColor3f(1.0f, 1.0f, 0.0f);
		DrawCircle(-0.25f, -0.15f, 0.4, 30, 180);
		glEnd();

	glPopMatrix();

	glPushMatrix();
		glBegin(GL_POLYGON); //eye right
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawCircle(0.25f , 0.2, 0.2, 30, 180);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex2f(0.27f, 0.23f);
		glVertex2f( 0.27f, 0.3f);
		glVertex2f( 0.23f, 0.3f);
		glVertex2f( 0.23f, 0.23f);
		glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON); //lid eye right
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawCircle(0.25f, -0.15f, 0.4, 30, 180);
	glEnd();

	glPushMatrix();
	glRotatef(180, 0.0, 0.0, 1.0);

	glLineWidth(10); //the smile
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.7, 0.7);
		DrawCircle(0.0, 0.0, 0.4, 30, 180);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 0.0);
		DrawCircle(0.0, -0.1, 0.4, 30, 180);
		glEnd();
	glPopMatrix();



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

void Practical2_Q1()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(Tx, Ty, 0.0);
	glBegin(GL_TRIANGLES);
	glColor3f(T_Red, T_Green, T_Blue);
		glVertex2f(-0.5, 0.0);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.5, 0.0);
	glEnd();

}
float red = 1.0f, green = 0.0f, blue = 0.0f;
float colorSpeed = 0.0002;
float scaleFactor = 1.0f, scaleSpeed = 0.0001f;

void Practical2_Q2()
{
	glClearColor(0.0, 0.0, 0.0, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (red == 1 && green == 1 && blue == 1) 
	{
		green = 0;
		blue = 0;
	}
	if (red < 1 && blue >= 1 && green <= 0) 
	{
		red += colorSpeed;
	}
	if (red >= 1 && blue > 0 && green <= 0) 
	{
		blue -= colorSpeed;
	}
	if (red >= 1 && blue <= 0 && green < 1) 
	{
		green += colorSpeed;
	}
	if (red > 0 && blue <= 0 && green >= 1) 
	{
		red -= colorSpeed;
	}
	if (red <= 0 && blue < 1 && green >= 1) 
	{
		blue += colorSpeed;
	}
	if (red <= 0 && blue >= 1 && green > 0) 
	{
		green -= colorSpeed;
	}
	scaleFactor += scaleSpeed;
	if (scaleFactor >= 1.5 || scaleFactor <= 0.5) 
	{
		scaleSpeed = -scaleSpeed; // Reverse the scaling direction at limits
	}
	glRotatef(0.2f, 0.0, 0.0, 1.0);

	glPushMatrix();
	{
		glScalef(scaleFactor, scaleFactor, 1.0);
		glColor3f(red, green, blue);

		glBegin(GL_POLYGON);
		glColor3f(red, green, blue);

		glVertex2f(0.0, 0.5);    // Top vertex
		glVertex2f(-0.1, 0.1);   // Bottom left vertex
		glVertex2f(0.0, 0.0);    // Bot vertex
		glVertex2f(0.1, 0.1);    // Bottom right vertex
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.2, -0.5);   // Bottom vertex
		glVertex2f(-0.1, 0.1);  // Top left vertex
		glVertex2f(0.1, -0.1);   // Top right vertex
		glVertex2f(0.2, -0.5);   // Bottom vertex
		glVertex2f(-0.1, -0.1);  // Top left vertex
		glVertex2f(0.1, 0.1);   // Top right vertex
		glVertex2f(-0.5, 0.05);   // Left vertex
		glVertex2f(-0.1, -0.1);  // Bottom left vertex
		glVertex2f(-0.1, 0.1);   // Top left vertex
		glVertex2f(0.5, 0.05);    // Right vertex
		glVertex2f(0.1, -0.1);   // Bottom right vertex
		glVertex2f(0.1, 0.1);    // Top right vertex
		glEnd();
	}
	glPopMatrix();
}

float Practial_Angle = 0.0f;

void Practical2_Q3()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(Practial_Angle, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.7f, 0.0f, 0.0f);

	glPointSize(100);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.5f, 1.0f);
		glVertex2f(0.0f, 0.0f);
	glEnd();
	
	Practial_Angle += 0.1f;
}
float ScaleInput = 1.0f;

void Practical2_Q4()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glScalef(ScaleInput, ScaleInput, 1.0f);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.5f, 1.0f);
		glVertex2f(-0.1f, 0.1f);
		glVertex2f(0.1f, 0.1f);
		glVertex2f(0.1f, -0.1f);
		glVertex2f(-0.1f, -0.1f);
	glEnd();

	if (ScaleInput < 10.0f)
	{
		ScaleInput += 0.001f;
	}
	else
	{
		ScaleInput = 1.0f;
	}
}

void DemoCode()
{
	switch (SwitchNum)
	{
	case 0:
		//Emoji_1();
		Practical2_Q1();
		break;
	case 1:
		//N9Flag();
		Practical2_Q2();
		break;
	case 2:
		//EnglandFlag();
		Practical2_Q3();
		break;
	case 3:
		//Scotland();
		Practical2_Q4();
		break;

	default:
		break;
	}
	//PahangFlag();
	//N9Flag();
	//EnglandFlag();
	//Scotland();
	//JapanFlag();
	//Emoji_1();

	//Emojis

	//TransformationTesting();
	//Practical2_Q1();

	/*glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(10);
	glBegin(GL_POLYGON);

	glColor3f((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);
	glVertex2f(0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(1.0, 0.0);

	glColor3f((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);
	glVertex2f(0.0, -1.0);

	glEnd();*/
}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	DemoCode();
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
