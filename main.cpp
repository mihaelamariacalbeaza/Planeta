//Calbeaza Mihaela Maria

#include <windows.h>
#include <GL/glut.h>

void activitate();

GLfloat xRotatie, yRotatie, zRotatie;  //unghiuri de rotatie

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //curata ecranul si buffer-ele
  glMatrixMode(GL_MODELVIEW);  //specifica care matrice este utilizata
  glLoadIdentity();  //inlocuieste matricea curenta cu o matrice de identitate
  glPushMatrix();   //impinge si deschide stiva actuala a matricii
  glRotatef(xRotatie, 1.0, 0.0, 0.0);  //inmulteste matricea actuala cu o matrice de rotatie xRotatie, yRotatie, zRotatie fiind unghiurile de rotatie
  glRotatef(yRotatie, 0.0, 1.0, 0.0);
  glRotatef(zRotatie, 0.0, 0.0, 1.0);
  glScalef(1.0, 1.0, 1.0); //inmulteste matricea curenta cu o matrice de scalare

  glutSolidTorus(0.02, 1.5, 3, 100);  //creeaza inelele planetei
  glRotatef(xRotatie, 0.5, 0.0, 0.0);
  glRotatef(yRotatie, 0.0, 0.5, 0.0);
  glRotatef(zRotatie, 0.0, 0.0, 0.5);

  glutSolidTorus(0.2, 1.2, 2, 75);
  glRotatef(xRotatie, 1.5, 0.0, 0.0);
  glRotatef(yRotatie, 0.0, 1.5, 0.0);
  glRotatef(zRotatie, 0.0, 0.0, 1.5);

  glutSolidTorus(0.12, 0.85, 2, 50);

  glutSolidSphere(0.5, 30, 50);
  glPopMatrix();  //sfera a fost plasa in "interiorul" inelelor, aceeasi origine
  glutSwapBuffers();  //se foloseste metoda de intershimbare a bufferelor
  glFlush();
}

void activitate(void)
{

	xRotatie += 0.02;
	yRotatie += 0.02;
    zRotatie += 0.02;

    display();
}

void remodelare(GLint w, GLint h)
{
  glViewport(0, 0, w, h);  //seteaza punctul de vedere
  glMatrixMode(GL_PROJECTION);  //matricea curenta devine matricea de proiectie
  GLfloat aspect = GLfloat(w) / GLfloat(h);
  glLoadIdentity();

  if (w <= h)
        {
            // daca lățimea este mai mică, inaltimea se intinde
            glOrtho(-2.5, 2.5, -2.5/aspect, 2.5/aspect, -10.0, 10.0);
        }
    else
        {
            // daca inaltimea este mai mică, latimea se intinde
            glOrtho(-2.5*aspect, 2.5*aspect, -2.5, 2.5, -10.0, 10.0);
        }
}

void styles() //Styling-ul Planetei cu scopul de a creea un efect realist
{
  GLfloat negru[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat rozaliu[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat roz[] = { 1.0, 0.0, 1.0, 0.0 };
  GLfloat alb[] = { 0.0, 1.0, 1.0, 1.0 };
  GLfloat directie[] = { 1.0, 1.0, 1.0, 0.0 };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, roz); //iluminarea obiectului pe partea din fata folosind lumina ambientala
  glMaterialfv(GL_FRONT, GL_SPECULAR, alb);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);

  glLightfv(GL_LIGHT0, GL_AMBIENT, negru);  //seteaza lumina ambientala-negru(palida)
  glLightfv(GL_LIGHT0, GL_DIFFUSE, rozaliu);  //seteaza lumina difuza: rozaliu-spre mov
  glLightfv(GL_LIGHT0, GL_SPECULAR, alb);  //da stralucire obiectului
  glLightfv(GL_LIGHT0, GL_POSITION, directie);

  glEnable(GL_LIGHTING);                // openGL "afla" de conceptul de lumina
  glEnable(GL_LIGHT0);                  // se aprinde sursa de lumină cu numărul 1
  glEnable(GL_DEPTH_TEST);              // rasterizare si adancimea
}
// Configurează atribute globale: culoarea clară și culoarea desenului
int main(int argc, char** argv)
{
  glutInit(&argc, argv);  //se initializeaza libraria glut-ului
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(80, 80);
  glutCreateWindow("Planeta");
  styles(); // functie pentru stilizare este chemata
    xRotatie=40;
    yRotatie=50;
    zRotatie=60;

  glutDisplayFunc(display); //seteaza afisajul din functia display
  glutReshapeFunc(remodelare);
  glutIdleFunc(activitate);
  glutMainLoop();
  return 0;

}
