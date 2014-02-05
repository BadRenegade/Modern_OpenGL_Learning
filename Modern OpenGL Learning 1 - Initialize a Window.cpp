#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

int CurrentWidth = 800;
int	CurrentHeight = 600;

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);

int main(int argc, char* argv[])
{
	InitWindow(argc, argv);

	cout << "INFO: OpenGL Version:\n" << glGetString(GL_VERSION) << endl;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glutMainLoop();
	
	return 0;
}


void InitWindow(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Modern OpenGL Learning 1");

	if(glewInit()) {
		cerr<<"Unable toinitialize GLEW ... exiting" <<endl;
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glutPostRedisplay();
}