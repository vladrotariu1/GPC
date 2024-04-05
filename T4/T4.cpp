#define _CRT_SECURE_NO_WARNINGS
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <list>

unsigned char prevKey;

class Point
{
private:
	int x, y;
public:
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int get_x()
	{
		return this->x;
	}
	int get_y()
	{
		return this->y;
	}
};

class CartesianGrid
{
private:
	int n, m;
public:
	CartesianGrid(int n, int m)
	{
		this->n = n;
		this->m = m;
	}

	void display()
	{
		glColor3f(0.0, 0.0, 0.0);
		for (int i = 0; i <= n; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(-1.0 * 0.9, (2.0 / n * i - 1) * 0.9);
			glVertex2f(1.0 * 0.9, (2.0 / m * i - 1) * 0.9);
			glEnd();
		}
		glColor3f(0.0, 0.0, 0.0);
		for (int i = 0; i <= m; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f((2.0 / n * i - 1) * 0.9, -1.0 * 0.9);
			glVertex2f((2.0 / m * i - 1) * 0.9, 1.0 * 0.9);
			glEnd();
		}
	}

	void createPixel(int n, int m)
	{
		float cx = adjustX(n);
		float cy = adjustY(m);
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(cx + 0.02, cy + 0.02);
		glVertex2f(cx + 0.02, cy - 0.02);
		glVertex2f(cx - 0.02, cy - 0.02);
		glVertex2f(cx - 0.02, cy + 0.02);
		glEnd();
	}

	void drawSegment(int x1, int y1, int x2, int y2, int dots)
	{
		glColor3f(1.0, 0.1, 0.1);
		glLineWidth(4.f);

		float cx1 = adjustX(x1);
		float cy1 = adjustY(y1);
		float cx2 = adjustX(x2);
		float cy2 = adjustY(y2);

		glBegin(GL_LINE_STRIP);
		glVertex2f(cx1, cy1);
		glVertex2f(cx2, cy2);
		glEnd();
		glLineWidth(1.f);

		std::list<Point> list = ScanConvertSegments3(x1, y1, x2, y2, dots);
		for (std::list<Point>::iterator it = list.begin(); it != list.end(); ++it)
			createPixel(it->get_x(), it->get_y());
	}

	std::list<Point> ScanConvertSegments3(int x1, int y1, int x2, int y2, int dots)
	{
		return ((double)y2 - (double)y1) / ((double)x2 - (double)x1) > 0 ? 
			generateLineUpPoints(x1, y1, x2, y2, dots) : 
			generateLineDownPoints(x1, y1, x2, y2, dots);
	}

	std::list<Point> generateLineUpPoints(int x1, int y1, int x2, int y2, int dots)
	{
		std::list<Point> points;

		int dy = y2 - y1;
		int dx = x2 - x1;
		int d = 2 * dy - dx;
		int dE = 2 * dy;
		int dNE = 2 * (dy - dx);

		int x = x1, y = y1;

		for (;x <= x2; x++)
		{
			points.push_back(Point(x, y));

			for (int i = 1; i <= dots / 2; i++)
			{
				points.push_back(Point(x, y - i));
				points.push_back(Point(x, y + i));
			}

			if (d > 0)
			{
				d += dNE;
				y++;
			}
			else
			{
				d += dE;
			}
		}
		return points;
	}

	std::list<Point> generateLineDownPoints(int x1, int y1, int x2, int y2, int dots)
	{
		std::list<Point> points;

		int dx = x2 - x1;
		int dy = y2 - y1;
		int d = 2 * dy + dx;
		int dE = 2 * dy;
		int dSE = 2 * (dy + dx);

		int x = x1, y = y1;

		for(; x <= x2; x++)
		{
			points.push_back(Point(x, y));

			for (int i = 1; i <= dots / 2; i++)
			{
				points.push_back(Point(x, y - i));
				points.push_back(Point(x, y + i));
			}

			if (d < 0)
			{
				d += dSE;
				y--;
			}
			else
			{
				d += dE;
			}
		}
		return points;
	}

	void displayCircle(int radius, int dots) {
		glColor3f(1.0, 0.1, 0.1);
		glLineWidth(4.f);

		float originx = adjustX(0);
		float originy = adjustY(0);

		float resx = adjustX(radius);
		float resy = originy;

		float r = resx - originx;

		float edges = 512.0;
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < edges; i++)
		{
			float x = r * cosf(0.5 * 3.1415926 * i / edges);
			float y = r * sinf(0.5 * 3.1415926 * i / edges);

			glVertex2f((float)x + originx, ((float)y + originy));

		}
		glEnd();
		glLineWidth(1.f);

		std::list<Point> list = drawCircleAlgorithm(radius, dots);

		for (std::list<Point>::iterator it = list.begin(); it != list.end(); ++it) {
			createPixel(it->get_x(), it->get_y());
		}

	}

	std::list<Point> drawCircleAlgorithm(float radius, int dots)
	{
		std::list<Point> points;

		int x = radius;
		int y = 0;
		int d = 1 - radius;
		int dN = 3;
		int dNW = -2 * radius + 5;

		points.push_back(Point(x, y));
		for (int i = 1; i <= dots / 2; i++)
		{
			points.push_back(Point(x - i, y));
			points.push_back(Point(x + i, y));
		}

		while (x > y)
		{
			if (d <= 0)
			{
				d += dN;
				dN += 2;
				dNW += 2;
			}
			else
			{
				d += dNW;
				dN += 2;
				dNW += 4;
				x--;
			}
			y++;

			points.push_back(Point(x, y));
			for (int i = 1; i <= dots / 2; i++)
			{
				points.push_back(Point(x - i, y));
				points.push_back(Point(x + i, y));
			}
		}

		return points;
	}

	float adjustX(int x) {
		return (2.0 / n * x - 1) * 0.9;
	}

	float adjustY(int y) {
		return (2.0 / m * y - 1) * 0.9;
	}
};

void Init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	glPolygonMode(GL_FRONT, GL_FILL);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	CartesianGrid cartesianGrid1 = CartesianGrid(15, 15);
	CartesianGrid cartesianGrid2 = CartesianGrid(15, 15);

	switch (prevKey)
	{
		case '1':
			cartesianGrid1.display();
			cartesianGrid1.drawSegment(0, 0, 15, 7, 1);
			cartesianGrid1.drawSegment(0, 15, 15, 10,2);
			break;
		case '2':
			cartesianGrid2.display();
			cartesianGrid2.displayCircle(7, 3);
			break;
		default:
			break;
	}

	glRasterPos2d(-0.99, -0.99);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2d(-0.99, 0.93);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');

	glRasterPos2d(0.93, -0.99);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'X');

	glFlush();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitWindowSize(300.0, 300.0);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
