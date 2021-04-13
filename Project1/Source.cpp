#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>


////////////////////////////
	int stopien = 4;	 //
	int deformacja = 2;	//
/////////////////////////


void randomColor()
{
	glColor3ub(rand() % 255, rand() % 255, rand() % 255);
}

void perturbation(float &x, float &y)
{
	if (deformacja <= 0)
		return;
	x = x + rand() % deformacja;
	y = y + rand() % deformacja;
}

void draw(float x, float y, double length)
{
	glBegin(GL_POLYGON);
	randomColor();
	perturbation(x, y);
	glVertex2f(x,y);
	randomColor();
	perturbation(x, y);
	glVertex2f(x + length, y);
	randomColor();
	perturbation(x, y);
	glVertex2f(x + length, y + length);
	randomColor();
	perturbation(x, y);
	glVertex2f(x, y + length);
	glEnd();
	glFlush();
}

void create(int k, float x, float y, double len)
{
	if (k > 1)
	{
		double act_len = len / 3;
		k--;
		create(k, x, y, act_len);
		create(k, x + act_len, y, act_len);
		create(k, x + 2 * act_len, y, act_len);
		create(k, x, y + act_len, act_len);
		create(k, x + act_len * 2, y + act_len, act_len);
		create(k, x, y + 2 * act_len, act_len);
		create(k, x + act_len, y + 2 * act_len, act_len);
		create(k, x + act_len * 2, y + act_len * 2, act_len);

	}
	else
	{
		draw(x, y, len);
	}
}
/*************************************************************************************/

// Funkcaja okre�laj�ca, co ma by� rysowane 
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	create(stopien, -100,-100, 200);
}
/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania


void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wn�trza okna - ustawiono na szary
}
/*************************************************************************************/

// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okre�lenie uk�adu wsp�rz�dnych obserwatora
	glLoadIdentity();
	// Okre�lenie przestrzeni ograniczaj�cej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okre�lenie okna obserwatora. 
	// Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
	// Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okre�lenie uk�adu wsp�rz�dnych     
	glLoadIdentity();
}
/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli


void main(void)
{
	srand(time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wy�wietlania
	// GLUT_SINGLE - pojedynczy bufor wy�wietlania
	// GLUT_RGBA - model kolor�w RGB

	glutCreateWindow("Dywan Sierpinskiego");
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	// Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
	// trzeba b�dzie przerysowa� okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst�pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}
/*************************************************************************************/