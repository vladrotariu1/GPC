// Daca se doreste utilizarea bibliotecii GLUT trebuie
// inclus fisierul header GL/glut.h (acesta va include
// la GL/gl.h si GL/glu.h, fisierele header pentru
// utilizarea bibliotecii OpenGL). Functiile din biblioteca
// OpenGL sunt prefixate cu gl, cele din GLU cu glu si
// cele din GLUT cu glut.

// #include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GLUT/glut.h>
#include <limits>

unsigned char prevKey;

void Display1() {
    double xmax, ymax, xmin, ymin;
    double a = 1, b = 2;
    double pi = 4 * atan(1);
    double ratia = 0.05;
    double t;

    // calculul valorilor maxime/minime ptr. x si y
    // aceste valori vor fi folosite ulterior la scalare
    xmax = a - b - 1;
    xmin = a + b + 1;
    ymax = ymin = 0;
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = a + b * cos(t);
        xmax = (xmax < x1) ? x1 : xmax;
        xmin = (xmin > x1) ? x1 : xmin;

        x2 = a - b * cos(t);
        xmax = (xmax < x2) ? x2 : xmax;
        xmin = (xmin > x2) ? x2 : xmin;

        y1 = a * tan(t) + b * sin(t);
        ymax = (ymax < y1) ? y1 : ymax;
        ymin = (ymin > y1) ? y1 : ymin;

        y2 = a * tan(t) - b * sin(t);
        ymax = (ymax < y2) ? y2 : ymax;
        ymin = (ymin > y2) ? y2 : ymin;
    }

    xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
    ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

    // afisarea punctelor propriu-zise precedata de scalare
    glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_LINE_STRIP);
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = (a + b * cos(t)) / xmax;
        x2 = (a - b * cos(t)) / xmax;
        y1 = (a * tan(t) + b * sin(t)) / ymax;
        y2 = (a * tan(t) - b * sin(t)) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = (a + b * cos(t)) / xmax;
        x2 = (a - b * cos(t)) / xmax;
        y1 = (a * tan(t) + b * sin(t)) / ymax;
        y2 = (a * tan(t) - b * sin(t)) / ymax;

        glVertex2f(x2, y2);
    }
    glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
    double pi = 4 * atan(1);
    double xmax = 8 * pi;
    double ymax = exp(1.1);
    double ratia = 0.05;

    // afisarea punctelor propriu-zise precedata de scalare
    glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_LINE_STRIP);
    for (double x = 0; x < xmax; x += ratia) {
        double x1, y1;
        x1 = x / xmax;
        y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();
}

void Display3() {
    double ratia = 0.05;
    double xmax = 30;
    double ymax = 1;

    glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_LINE_STRIP);
    for (double x = 0; x < xmax; x += ratia)
    {
        double x1, y1;
        if (x > 0) {

            if (x - floor(x) < ceil(x) - x)
                ymax = (x - floor(x)) / x;
            else
                ymax = (ceil(x) - x) / x;
        }
        else
            ymax = 1;

        x1 = x / xmax;
        y1 = ymax - ratia / 2;

        glVertex2f(x1, y1);
    }
    glEnd();
}

void Display4() {

    double a = 0.3;
    double b = 0.2;
    double t;
    double r = 0.05;
    double pi = 4 * atan(1);
    double x, y;

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);

    for (t = -pi; t < pi; t+= r) {
         
        x = 2 * (a * cos(t) + b) * cos(t);
        y = 2 * (a * cos(t) + b) * sin(t);

        glVertex2f(x, y);
    }
    glEnd();
}

void Display5() {

    double a = 0.2;
    double x_arr[300], y_arr[300];
    int n = 0;
    double t;
    double r = 0.005;
    double pi = 4 * atan(1);
    double x, y;

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_POINTS);

    for (t = -(pi / 2) + r; t < -(pi / 6); t += r) {           // avem nevoie doar de un triunghi, cel din stanga si de asta mergem pana la -pi/6

            
            x = a / (4 * cos(t) * cos(t) - 3);             
            y = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);
                
            x_arr[n] = x;               // adaugam in vectori, coordonatele noastre din triunghiun nostru
            y_arr[n] = y;
            n++;
              
        // glVertex2f(x, y);
    }

    glEnd();

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_TRIANGLES);

    for (auto i = 1; i < n - 1; i+=3) {                     //parcurgem vectorii din 3 in 3 la i, ca sa avem spatii intre liniile rosii
        if (!(i < 45 || i > 160)) continue;

        glVertex2f(-1.0, 1.0);
        glVertex2f(x_arr[i], y_arr[i]);        
        glVertex2f(x_arr[i + 1], y_arr[i + 1]);
    }

    glEnd();

}

void Display6() {

    double a = 0.1;
    double b = 0.2;
    double t;
    double r = 0.05;
    double pi = 4 * atan(1);
    double x, y;

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);

    for (double t = -10; t <= 10; t+=r) {

        x = a * t - b * sin(t);
        y = a - b * cos(t);

        glVertex2f(x, y);
    }
    glEnd();

    
}

void Display7() {

    double a = 0.4;
    double ratia = 0.0005;
    double t;
    double r;
    double pi = 4 * atan(1);
    double x, y;

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);

    //left
    for (t = -(pi / 4); t < pi / 4; t += ratia) {

        r = -(a * sqrt(2 * cos(2 * t)));            // ecuatii polare => calculam r conform formulei din tema, iar apoi 
        x = r * cos(t);                               //transformam  in coordonate carteziene, conform definitiei x = r * cos(t) si y = r * sin(t)
        y = r * sin(t);

        glVertex2f(x, y);
    }

    //right
    for (t = pi / 4; t > -(pi / 4); t -= ratia) {       // mergem de la dreapta la stanga ca sa putem face curba din dreapta a infinitului

        r = a * sqrt(2 * cos(2 * t));
        x = r * cos(t);
        y = r * sin(t);

        glVertex2f(x, y);
    }

    glEnd();
}

void Display8() {

    double a = 0.02;
    double ratia = 0.0005;
    double t;
    double r;
    double pi = 4 * atan(1);
    double x, y;
    double e = 2.71828;


    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);

    for (t = 0; t < 50; t += ratia) {           // variabila T apartinand (0, infinit) am dat o valoare random pentru marginea din dreapta

        r = a * exp(1+t);
        x = r * cos(t);
        y = r * sin(t);

        glVertex2f(x, y);

    }
    glEnd();
}

void Display9() {

    

}

void Display10() {

    
}

void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

    //   glPointSize(4);

    glPolygonMode(GL_FRONT, GL_LINE);
}


void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (prevKey) {
    case '1':
        Display1();
        break;
    case '2':
        Display2();
        break;
    case '3':
        Display3();
        break;
    case '4':
        Display4();
        break;
    case '5':
        Display5();
        break;
    case '6':
        Display6();
        break;
    case '7':
        Display7();
        break;
    case '8':
        Display8();
        break;
    case '9':
        Display9();
        break;
    case '0':
        Display10();
      
    default:
        break;
    }

    glFlush();
}

/*
   Parametrii w(latime) si h(inaltime) reprezinta noile
   dimensiuni ale ferestrei
*/
void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}
int main(int argc, char** argv) {
   // Initializarea bibliotecii GLUT. Argumentele argc
   // si argv sunt argumentele din linia de comanda si nu 
   // trebuie modificate inainte de apelul functiei 
   // void glutInit(int *argcp, char **argv)
   // Se recomanda ca apelul oricarei functii din biblioteca
   // GLUT sa se faca dupa apelul acestei functii.
   glutInit(&argc, argv);
   
   // Argumentele functiei
   // void glutInitWindowSize (int latime, int latime)
   // reprezinta latimea, respectiv inaltimea ferestrei
   // exprimate in pixeli. Valorile predefinite sunt 300, 300.
   glutInitWindowSize(300, 300);

   // Argumentele functiei
   // void glutInitWindowPosition (int x, int y)
   // reprezinta coordonatele varfului din stanga sus
   // al ferestrei, exprimate in pixeli. 
   // Valorile predefinite sunt -1, -1.
   glutInitWindowPosition(100, 100);

   // Functia void glutInitDisplayMode (unsigned int mode)
   // seteaza modul initial de afisare. Acesta se obtine
   // printr-un SAU pe biti intre diverse masti de display
   // (constante ale bibliotecii GLUT) :
   // 1. GLUT_SINGLE : un singur buffer de imagine. Reprezinta
   //    optiunea implicita ptr. nr. de buffere de
   //    de imagine.
   // 2. GLUT_DOUBLE : 2 buffere de imagine.
   // 3. GLUT_RGB sau GLUT_RGBA : culorile vor fi afisate in
   //    modul RGB.
   // 4. GLUT_INDEX : modul indexat de selectare al culorii.
   // etc. (vezi specificatia bibliotecii GLUT)
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   // Functia int glutCreateWindow (char *name)
   // creeaza o fereastra cu denumirea data de argumentul
   // name si intoarce un identificator de fereastra.
   glutCreateWindow (argv[0]);

   Init();

   // Functii callback : functii definite in program si 
   // inregistrate in sistem prin intermediul unor functii
   // GLUT. Ele sunt apelate de catre sistemul de opreshapeerare
   // in functie de evenimentul aparut

   // Functia 
   // void glutReshapeFunc (void (*Reshape)(int width, int height))
   // inregistreaza functia callback Reshape care este apelata
   // oridecate ori fereastra de afisare isi modifica forma.
   glutReshapeFunc(Reshape);
   
   // Functia 
   // void glutKeyboardFunc (void (*KeyboardFunc)(unsigned char,int,int))
   // inregistreaza functia callback KeyboardFunc care este apelata
   // la actionarea unei taste.
   glutKeyboardFunc(KeyboardFunc);
   
   // Functia 
   // void glutMouseFunc (void (*MouseFunc)(int,int,int,int))
   // inregistreaza functia callback MouseFunc care este apelata
   // la apasarea sau la eliberarea unui buton al mouse-ului.
   glutMouseFunc(MouseFunc);

   // Functia 
   // void glutDisplayFunc (void (*Display)(void))
   // inregistreaza functia callback Display care este apelata
   // oridecate ori este necesara desenarea ferestrei: la 
   // initializare, la modificarea dimensiunilor ferestrei
   // sau la apelul functiei
   // void glutPostRedisplay (void).
   glutDisplayFunc(Display);
   
   // Functia void glutMainLoop() lanseaza bucla de procesare
   // a evenimentelor GLUT. Din bucla se poate iesi doar prin
   // inchiderea ferestrei aplicatiei. Aceasta functie trebuie
   // apelata cel mult o singura data in program. Functiile
   // callback trebuie inregistrate inainte de apelul acestei
   // functii.
   // Cand coada de evenimente este vida atunci este executata
   // functia callback IdleFunc inregistrata prin apelul functiei
   // void glutIdleFunc (void (*IdleFunc) (void))
   glutMainLoop();

   return 0;
}
