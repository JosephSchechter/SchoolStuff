#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glut.h>

const int width=640;
const int height=480;
const int xpos=100;
const int ypos=100;
float ex,ey,ez,theta,t;
float cx = 0;
float cy = 0;
float cz = 100;

void init(void)
{
}

void mykey(unsigned char key, int x, int y)
{	printf("%s %c","key pressed", key);
	switch (key) // for gluLookAt
		{ 
		case 'q':
			exit (0);
		break;
		case 'r':
			theta = theta + 10;
		break;
		case 'l':
			theta = theta - 10;
		default:break;
		}
	if (theta>360) theta=theta-360;
	else 
		if (theta<0) theta=theta+360;
	printf("%s %f","theta=", theta);
				
 glutPostRedisplay(); // ensures only 1 re-draw per eventloop
}

void myspecialkeys(int key, int x, int y)
{	// changes " LookAt " angle for all.
	switch (key) 
	{
		case GLUT_KEY_LEFT : 
			ex -=1.01f;
			break;
		case GLUT_KEY_RIGHT : 
			ex +=1.01f;
			break;
		case GLUT_KEY_UP : 
			ey += 1.01f;
			break;
		case GLUT_KEY_DOWN : 
			ey -= 1.01f;
			break;
	}
	gluLookAt(ex, ey, ez, cx, cy, cz, 0, 1, 0);
	glutPostRedisplay();
}

void myidle()
{  
	glutPostRedisplay(); // ensures only 1 re-draw per eventloop
}

void idleFuncs(void)
{
    glutPostRedisplay();
}

void draw_pentahedron() // implement the faces of the figure
	{
		glPushMatrix ();
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		//glEnable(GL_DEPTH_TEST);

	// want to rotate ONLY the pyramid
		glRotatef(theta,0,0,1); //	this rotates EVERYTHING in current stack around 0,0,0 to x,y,z
		glTranslatef(0,0,t); // this translates along z axis
		glBegin(GL_TRIANGLES);
			glColor3f(0.0, 0.0, 0.11);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 100, 0);
			glVertex3f(100, 100, 0);
			glVertex3f(100, 0, 0);
		glEnd();
		glBegin(GL_TRIANGLES);
			glColor3f(0.0, 0.5, 0.0);
			glVertex3f(100, 0, 0);
			glVertex3f(100, 100, 0);
			glVertex3f(100, 100, 100);
		glEnd();
		glBegin(GL_TRIANGLES);
			glColor3f(0.8, 0.0, 0.0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 100, 0);
			glVertex3f(100, 100, 100);
		glEnd();
		glBegin(GL_TRIANGLES);
			glColor3f( 0.0, 0.3, 0.1);
			glVertex3f(0, 0, 0);
			glVertex3f(100, 0, 0);
			glVertex3f(100, 100, 100);
		glEnd();
		glBegin(GL_TRIANGLES);
			glColor3f(0.4, 0.1, 0.7);
			glVertex3f(0, 100, 0);
			glVertex3f(100, 100, 0);
			glVertex3f(100, 100, 100);
		glEnd();	
		//glDisable(GL_DEPTH_TEST);
		glPopMatrix ();
	}	

void draw_square()
{
	glPushMatrix ();
	/* define a square */
	glBegin(GL_POLYGON);       /* 2D, floating point parameters */
		glColor3f(0.4,0.4,0.4);
		glVertex2f(-100, -100);		
		glVertex2f(-100,  100);
		glVertex2f( 100,  100);
		glVertex2f( 100, -100);
	glEnd();  /* This terminates the generation of the object */
	glPopMatrix ();
}
void draw_triangle()
{
	glPushMatrix ();
	// now define a simple triangle in ONE plane
	glBegin(GL_POLYGON); 
		glColor3f(75, 0.0, 0.0);		// all red
		glVertex3f(50, 100.0, 0.0);

		glColor3f(0.0, 75, 0.0);		// all green
		glVertex3f(50, 50, 0.0);
		
		glColor3f(0.0, 0.0, 75);		// all blue
		glVertex3f(100.0, 50, 0.0);
	glEnd();
	glPopMatrix ();
}

void draw_axes()
{	
	glPushMatrix ();
	glBegin(GL_LINES); // as pairs of points (default action of GL_LINES)
		glColor3f(0.75, 0.0, 0.0); //red
		glVertex3f(0.0, 0.0, 0.0);  //the x-axis
		glVertex3f(width, 0.0, 0.0);

		glColor3f(0.0, 0.75, 0.0); //green
		glVertex3f(0.0, 0.0, 0.0);  //the y-axis
		glVertex3f(0.0, width, 0.0);

		glColor3f(0.0, 0.00, 0.75); //blue
		glVertex3f(0.0, 0.0, 0.0);  //the z-axis
		glVertex3f(0.0, 0.0, width);
	glEnd();
	glPopMatrix ();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//           eye,          at      up
	gluLookAt(ex, ey, ez,      cx,cy,cz,   0,1,0); 

	draw_square();
	draw_triangle();
	draw_axes();
	draw_pentahedron();

    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300.0, 300.0, -200.0, 200.0, -1.0, 1.0);
	gluPerspective(90, 10, 0, 10000);
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(xpos, ypos);
    
    glutCreateWindow("Graphics Programming Basics");
	glutSpecialFunc(myspecialkeys);
	glutKeyboardFunc(mykey);	// register my keystroke-interrupt handler AFTER create window
	glutIdleFunc(myidle);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
}