/* However Everyone Like Pasta May Enjoy*/

#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float Tx;
float Ty;
int SwitchNum = 0;
float SpinSpeed = 0.0f;
float MoveDirection = 1.0f;
//float OverallSpin = 0.0f;


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
			SwitchNum = SwitchNum % 2;
		}

		else if (wParam == VK_LEFT)
		{
			Tx -= 0.01;
			//SpinSpeed += 0.5f;
		}

		else if (wParam == VK_RIGHT)
		{
			Tx += 0.01;
			//SpinSpeed -= 0.5f;
		}
		//special for Q2 section
		else if (wParam == 'R')
		{
			MoveDirection *= -1;
			//Change Direction
		}
		else if (wParam == 'W')
		{
			//Accelerate 
			SpinSpeed += 0.05f;
		}
		else if (wParam == 'S')
		{
			if (SpinSpeed > 0.0f)
			{
				SpinSpeed -= 0.02f;
			}
			else if (SpinSpeed < 0.01f)
			{
				SpinSpeed = 0.0f;
			}
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
			SpinSpeed = 0.0f; //Stops Spinning

		}

		/*else if (wParam == 'R')
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
		}*/

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
void CreateQuad(float width, float height)
{
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.5f, 1.0f);
		glVertex2f(-width, height);
		glVertex2f(width, height);
		glVertex2f(width, -height);
		glVertex2f(-width, -height);
	glEnd();
}
void Practical3_Q1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		glTranslatef(Tx, Ty, 0.0f);
		CreateQuad(0.2, 0.1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-Tx, -Ty, 0.0f);
		CreateQuad(0.2, 0.1);
	}
	glPopMatrix();
}

void CreateWindBlade()
{
	glColor3f(0.0f, 0.5f, 1.0f);
	glBegin(GL_QUADS);
	{
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.5f, 0.0f);
		glVertex2f(0.5f, -0.1f);
		glVertex2f(0.0f, -0.1f);
	}
	glEnd();

	glLineWidth(5);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	{
		glVertex2f(-0.5f, 0.0f);
		glVertex2f(0.5f, 0.0f);
	}
	glEnd();
}

float DeployAngle = 0.0f;
float OverallSpin = 0.0f;
int i;
void Practical3_Q2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.7f, 0.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();//thy glass (rmb to touch them
	{
		glColor3f(0.0f, 1.0f, 0.1f);
		glBegin(GL_QUADS);
			glVertex2f(-1, -0.5);
			glVertex2f(1, -0.5);
			glVertex2f(1, -1.0);
			glVertex2f(-1, -1.0);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(0.58f, 0.3f, 0.0);
		glBegin(GL_QUADS);
			glVertex2f(-0.15f, -0.2f);
			glVertex2f(0.15f, -0.2f);
			glVertex2f(0.15f, -1.0f);
			glVertex2f(-0.15f, -1.0f);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix(); //The roof
	{
		glColor3f(0.58f, 0.3f, 0.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(-0.2f, -0.2f);
			glVertex2f(0.2f, -0.2f);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix(); //THE WINDMILL's Blade
	{
		glScalef(0.5f, 0.5f, 0.0f);
		OverallSpin += SpinSpeed * MoveDirection;
		glRotatef(OverallSpin, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		{
			for ( i = 0; i < 8; i++)
			{
				DeployAngle = (i / 8.0f) * 360.0f;
				glRotatef(DeployAngle, 0.0f, 0.0f, 1.0f);
				glPushMatrix();
				{
					glTranslatef(0.5f, 0.0f, 0.0f);
					CreateWindBlade();
				}
				glPopMatrix();
			}
		}
		glPopMatrix();
	}
	glPopMatrix();

	
}
void DemoCode()
{
	switch (SwitchNum)
	{
	case 0:
		Practical3_Q1();
		break;

	case 1:
		Practical3_Q2();
		break;

	default:
		break;
	}

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
