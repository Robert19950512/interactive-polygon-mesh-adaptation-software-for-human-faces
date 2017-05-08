// minimal.cpp: Display the landmarks of a face in an image.
//              This demonstrates stasm_search_single.

//#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "opencv/highgui.h"
#include "stasm_lib.h"
#include  "minimal.h"
#include "MA.h"
// GLUT header
#include <stdlib.h>
#include <GL\glut.h>    // OpenGL GLUT Library Header

// Open file dialog
#include "LoadFileDlg.h"

// The GLM code for loading and displying OBJ mesh file
#include "glm.h"

// The trackball code for rotating the model
#include "trackball.h"

//image user load in


//cv::Mat img2;
// The size of the GLUT window
int window_width = 900;
int window_height = 600;
//size of input image
int icols=0;
int irows=0;

char path[128] = "";
char TitleName[128] = "";

// The OBJ model
GLMmodel* pModel = NULL;

// The current modelview matrix
double pModelViewMatrix[16];

// If mouse left button is pressed
bool bLeftBntDown = false;

// Old position of the mouse
int OldX = 0;
int OldY = 0;
float landmark[2 * stasm_NLANDMARKS];

//screen flag
int screen = 1;

static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)window_width / (float)window_height, 0.01f, 200.0f);

	glClearColor(0, 0, 0, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glEnable(GL_CULL_FACE);

	// Setup other misc features.
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	// Setup lighting model.
	GLfloat light_model_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light0_direction[] = { 0.0f, 0.0f, 10.0f, 0.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_model_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHT0);

	
	// Init the dlg of the open file
	PopFileInitialize(NULL);
}

/// Display the Object
void display()
{
	if(screen==1){
		glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
		//---------------------------------
		glFlush();
		glutSwapBuffers();
	}
	if(screen==2) {
		init();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslated(0.0, 0.0, -5.0);
		glMultMatrixd(pModelViewMatrix);

		if (pModel)
		{
			glmDraw(pModel, GLM_FLAT);
		}
		glFlush();
		glutSwapBuffers();


	}

}


/// Reshape the Window
void reshape(int w, int h)
{
	// Update the window's width and height
	window_width = w;
	window_height = h;

	// Reset the viewport
	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)window_width / (float)window_height, 0.01f, 200.0f);

	glutPostRedisplay();
}

/// Keyboard Messenge
void keyboard(unsigned char key, int x, int y)
{
	// The obj file will be loaded
	//char FileName[128] = "";
	//char TitleName[128] = "";

	// Center of the model
	float modelCenter[] = { 0.0f, 0.0f, 0.0f };
	
	switch (key)
	{
	case 'o':
	case 'O':
		screen = 2;
		std::cout << "o pressed" << std::endl;
	//	PopFileOpenDlg(NULL, FileName, TitleName);
		// If there is a obj model has been loaded, destroy it
		//if (pModel)
		//{
		//	glmDelete(pModel);
		//	pModel = NULL;
		//}

		//// Load the new obj model
		//pModel = glmReadOBJ("newface.obj");
		
	//	MA(landmark, pModel, &icols, &irows);
		// Generate normal for the model
		glmFacetNormals(pModel);
		std::cout << "normal calcualtion complete";
		std::cout << "vertices 1:" << pModel->vertices[3] << std::endl;
		// Scale the model to fit the screen
		glmUnitize(pModel, modelCenter);
		
		std::cout << "num of groups" << pModel->numgroups << std::endl;
		std::cout << "name of groups1:" << pModel->groups->name << std::endl;
	
		std::cout << "name of groups3:" << pModel->groups->next->next->name << std::endl;
	

		// Init the modelview matrix as an identity matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glGetDoublev(GL_MODELVIEW_MATRIX, pModelViewMatrix);

		break;

	case '+':
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixd(pModelViewMatrix);
		glScaled(1.05, 1.05, 1.05);
		glGetDoublev(GL_MODELVIEW_MATRIX, pModelViewMatrix);
		break;

	case '-':
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixd(pModelViewMatrix);
		glScaled(0.95, 0.95, 0.95);
		glGetDoublev(GL_MODELVIEW_MATRIX, pModelViewMatrix);
		break;

	case's':
	//	screen = 2;
		
		minimal(landmark,&icols,&irows);
	
		//	landmark = landmarks;
	
	//	std::cout << icols;
		break;
	case'n':
		MA(landmark, pModel, &icols, &irows);
		break;
	case 'h':
		screen = 1;
		FILE* pfile;
		pfile = fopen("lab2.bmp", "rb");
		if (pfile == 0) exit(0);
		fseek(pfile, 0x0012, SEEK_SET);
		fread(&imagewidth, sizeof(imagewidth), 1, pfile);
		fread(&imageheight, sizeof(imageheight), 1, pfile);
		//计算像素数据长度
		pixellength = imagewidth * 3;
		while (pixellength % 4 != 0)pixellength++;
		pixellength *= imageheight;
		//读取像素数据
		pixeldata = (GLubyte*)malloc(pixellength);
		if (pixeldata == 0) exit(0);
		fseek(pfile, 54, SEEK_SET);
		fread(pixeldata, pixellength, 1, pfile);

		//关闭文件
		fclose(pfile);
		glutPostRedisplay();
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

/// Mouse Messenge
void mouse(int button, int state, int x, int y)
{
	if (pModel)
	{
		if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		{
			OldX = x;
			OldY = y;
			bLeftBntDown = true;
		}
		else if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		{
			bLeftBntDown = false;
		}
	}
}

/// Motion Function
void motion(int x, int y)
{
	if (bLeftBntDown && pModel)
	{
		float fOldX = 2.0f*OldX / (float)window_width - 1.0f;
		float fOldY = -2.0f*OldY / (float)window_height + 1.0f;
		float fNewX = 2.0f*x / (float)window_width - 1.0f;
		float fNewY = -2.0f*y / (float)window_height + 1.0f;

		double pMatrix[16];
		trackball_opengl_matrix(pMatrix, fOldX, fOldY, fNewX, fNewY);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixd(pMatrix);
		glMultMatrixd(pModelViewMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, pModelViewMatrix);

		OldX = x;
		OldY = y;
		glutPostRedisplay();
	}
}

/// Idle function
void idle(void)
{
	glutPostRedisplay();
	
}


int main(int argc, char* argv[])
{
	
//	printf("press any key to select a picture\n");
//	system("pause");
	printf("interative polygon mesh adaptation software for human faces 1.1\n");
	free(pixeldata);
	FILE* pfile;
	pfile = fopen("lab1.bmp", "rb");
	if (pfile == 0) exit(0);
	fseek(pfile, 0x0012, SEEK_SET);
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	fread(&imageheight, sizeof(imageheight), 1, pfile);
	//计算像素数据长度
	pixellength = imagewidth * 3;
	while (pixellength % 4 != 0)pixellength++;
	pixellength *= imageheight;
	//读取像素数据
	pixeldata = (GLubyte*)malloc(pixellength);
	if (pixeldata == 0) exit(0);
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	//关闭文件
	fclose(pfile);

	pModel = glmReadOBJ("facede.obj");
	std::cout << "original model read in complete" << std::endl;
	//	init();
	PopFileInitialize(NULL);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("interactive polygon mesh adaptation software 1.1");
	PopFileInitialize(NULL);
//	if (screen == 2) { init(); }
	
	// Set the callback function
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
