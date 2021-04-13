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

// Funkcaja okreœlaj¹ca, co ma byæ rysowane 
// (zawsze wywo³ywana, gdy trzeba przerysowaæ scenê)


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	create(stopien, -100,-100, 200);
}
/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania


void MyInit(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnêtrza okna - ustawiono na szary
}
/*************************************************************************************/

// Funkcja s³u¿¹ca do kontroli zachowania proporcji rysowanych obiektów
// niezale¿nie od rozmiarów okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokoœæ i wysokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem, gdy zmieni siê rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Okreœlenie uk³adu wspó³rzêdnych obserwatora
	glLoadIdentity();
	// Okreœlenie przestrzeni ograniczaj¹cej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// okreœlenie okna obserwatora. 
	// Pozwala to zachowaæ w³aœciwe proporcje rysowanego obiektu
	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okreœlenie uk³adu wspó³rzêdnych     
	glLoadIdentity();
}
/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli


void main(void)
{
	srand(time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	// Ustawienie trybu wyœwietlania
	// GLUT_SINGLE - pojedynczy bufor wyœwietlania
	// GLUT_RGBA - model kolorów RGB

	glutCreateWindow("Dywan Sierpinskiego");
	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
	// Biblioteka GLUT bêdzie wywo³ywa³a t¹ funkcjê za ka¿dym razem, gdy
	// trzeba bêdzie przerysowaæ okno


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za
	// zmiany rozmiaru okna

	MyInit();
	// Funkcja MyInit (zdefiniowana powy¿ej) wykonuje wszelkie  
	// inicjalizacje konieczneprzed przyst¹pieniem do renderowania

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}
/*************************************************************************************/