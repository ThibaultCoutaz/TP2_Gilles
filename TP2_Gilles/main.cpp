
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "struct.h"

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

#define WIDTH  600
#define HEIGHT 600

#define KEY_ESC 27

float angleX=0.0f; //angle de rotation en Y de la scene
float angleY=0.0f; //angle de rotation en X de la scene

float pasDeplacement=1.25;


//position lumiere
float xLitePos=0;
float yLitePos=10;
float zLitePos=-100;

float tx=0.0;
float ty=0.0;
float tz=0.0;

/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Si vous avez des choses à initialiser, c est ici.	
}

void drawCylindre(float r,float h,const int nbmeridiens){

	//Definir centre :
	point3 centre = point3(0.,0.,0.);

	glPushMatrix();
	glBegin(GL_TRIANGLES);	

	float angle= (2*M_PI)/nbmeridiens;

	for(int i=0;i<nbmeridiens;i++){


		//premier triangle
		point3 p = point3(r*cos(angle*i),r*sin(angle*i),h/2);
		point3 p_ = point3(r*cos(angle*i),r*sin(angle*i),-h/2);
		point3 p2 = point3(r*cos(angle*(i+1)),r*sin(angle*(i+1)),-h/2);

		glColor3f(0.7,0.7,0.7);//couleur gris
		glVertex3f(p.x,p.y, p.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p_.x,p_.y, p_.z);


		//bouchon bas
		point3 p3 = point3(centre.x,centre.y,-h/2);
		glColor3f(0.7,0.0,0.7);//couleur gris
		
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p3.x,p3.y, p3.z);
		glVertex3f(p_.x,p_.y, p_.z);	

		//Deuxiéme triangle
		p_  = point3(r*cos(angle*(i+1)),r*sin(angle*(i+1)),h/2);
	
		glColor3f(0.7,0.7,0.0); //Couleur jaune
		glVertex3f(p2.x,p2.y, p2.z);
		glVertex3f(p.x,p.y, p.z);
		glVertex3f(p_.x,p_.y,p_.z);	

		//bouchon haut
		p3.z= h/2;
		glColor3f(0.0,0.7,0.7);//couleur gris
		
		glVertex3f(p_.x,p_.y,p_.z);
		glVertex3f(p.x,p.y, p.z);
		glVertex3f(p3.x,p3.y, p3.z);	


	}

	glEnd();
	glPopMatrix();	

}

//Draw Sphere
void drawSphere(float r,float nbmeridiens,float nbparalleles){

	float anglemeridiens = (2*M_PI)/nbmeridiens;
	float angleparalleles = M_PI/nbparalleles;

	glPushMatrix();
	glBegin(GL_TRIANGLES);	

	for(float i=0;i<nbmeridiens;i++){
		for(float j=0;j<nbparalleles;j++){
			
			point3 p = point3(r*sin(angleparalleles*j)*cos(anglemeridiens*i),r*sin(angleparalleles*j)*sin(anglemeridiens*i),r*cos(angleparalleles*j));
			point3 p_ = point3(r*sin(angleparalleles*j)*cos(anglemeridiens*(i+1)),r*sin(angleparalleles*j)*sin(anglemeridiens*(i+1)),r*cos(angleparalleles*j));
			point3 p2 = point3(r*sin(angleparalleles*(j+1))*cos(anglemeridiens*i),r*sin(angleparalleles*(j+1))*sin(anglemeridiens*i),r*cos(angleparalleles*(j+1)));

			glColor3f(0.7,0.7,0.7);//couleur gris
			glVertex3f(p.x,p.y, p.z);
			glVertex3f(p2.x,p2.y,p2.z);
			glVertex3f(p_.x,p_.y, p_.z);


			p = point3(r*sin(angleparalleles*(j+1))*cos(anglemeridiens*(i+1)),r*sin(angleparalleles*(j+1))*sin(anglemeridiens*(i+1)),r*cos(angleparalleles*(j+1)));

			glColor3f(0.2,0.2,0.0);//couleur gris
			glVertex3f(p2.x,p2.y,p2.z);
			glVertex3f(p.x,p.y, p.z);
			glVertex3f(p_.x,p_.y, p_.z);

		}
	}
	glPopMatrix();	
	glEnd();
}


//Draw a Cone
void drawCone(float r1,float r2,float h,const int nbmeridiens){

	//Definir centre :
	point3 centre = point3(0.,0.,0.);

	glPushMatrix();
	
	glBegin(GL_TRIANGLES);	

	float angle= (2*M_PI)/nbmeridiens;

	for(int i=0;i<nbmeridiens;i++){


		//Prermier Triangle
		point3 p = point3(r1*cos(angle*i),r1*sin(angle*i),h/2);
		point3 p_ = point3(r2*cos(angle*i),r2*sin(angle*i),-h/2);
		point3 p2 = point3(r2*cos(angle*(i+1)),r2*sin(angle*(i+1)),-h/2);

		glColor3f(0.7,0.7,0.7);//couleur gris
		glVertex3f(p.x,p.y, p.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p_.x,p_.y, p_.z);


		//bouchon bas
		point3 p3 = point3(centre.x,centre.y,-h/2);
		glColor3f(0.7,0.0,0.7);//couleur gris
		
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p3.x,p3.y, p3.z);
		glVertex3f(p_.x,p_.y, p_.z);	

		//Deuxiéme triangle
		p_ = point3(r1*cos(angle*(i+1)),r1*sin(angle*(i+1)),h/2);

		glColor3f(0.7,0.7,0.0); //Couleur jaune
		glVertex3f(p2.x,p2.y, p2.z);
		glVertex3f(p.x,p.y, p.z);
		glVertex3f(p_.x,p_.y,p_.z);	

		//bouchon haut
		p3 = point3(centre.x,centre.y,h/2);
		glColor3f(0.0,0.7,0.7);//couleur gris
		
		glVertex3f(p_.x,p_.y,p_.z);
		glVertex3f(p.x,p.y, p.z);
		glVertex3f(p3.x,p3.y, p3.z);	


	}

	glEnd();
	glPopMatrix();	

}


/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //effacement du buffer

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//Description de la scene
	glLoadIdentity();
	//rotation de la scene suivant les mouvements de la souris
	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);
	glTranslatef(tx,ty,tz);

	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);

			
			
		//drawCylindre(2.,10.,360);	
		//drawSphere(10.,180.,180.);
		drawCone(5.0,1.5,10,360);


	//affiche les axes du repere
		glColor3f(0.0,1.0,0.0); //Y vert
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,20,0);
		glEnd();

		glColor3f(0.0,0.0,1.0); //Z bleu
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,0,20);
		glEnd();
		
		glColor3f(1.0,0.0,0.0); //X rouge
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(20,0,0);
		glEnd();

	glutSwapBuffers();// echange des buffers
}



/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-20, 20, -20, 20, -10, 10);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

GLvoid gestionSouris(int x, int y)
{
	angleX=x*720/WIDTH; //gere l'axe Oy
	angleY=-(y*180/HEIGHT-90)*4; //gere l'axe Ox

	glutPostRedisplay();
}

GLvoid gestionFleche(int key, int x, int y) 
{
	switch (key) {
		case GLUT_KEY_UP :
			tz+=int(pasDeplacement);glutPostRedisplay();
		break;

		case GLUT_KEY_DOWN :
			tz-=int(pasDeplacement);glutPostRedisplay();
		break;
	glutPostRedisplay();
	}

}

GLvoid window_key_down(unsigned char key, int x, int y)  //appuie des touches
{  
switch (key) 
{

//deplacement de la camera
	case 'z':
		ty+=int(pasDeplacement);glutPostRedisplay();
	break;

	case 's':
		ty-=int(pasDeplacement);glutPostRedisplay();
	break;

	case 'q':
		tx-=int(pasDeplacement);glutPostRedisplay();
	break;

	case 'd':
		tx+=int(pasDeplacement);glutPostRedisplay();
	break;

//sortie
	case KEY_ESC:
		exit(0);
		break;

	default:
		printf ("La touche %d non active.\n", key);
	break;
	}
glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInitWindowSize(1000, 1000);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("Mon cylindre");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(&window_key_down);
   glutDisplayFunc(display);
   glutPassiveMotionFunc(gestionSouris);
   glutSpecialFunc(&gestionFleche);
   glutMainLoop();
   return 0;
}
