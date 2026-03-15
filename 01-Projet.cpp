#include <Grapic.h>
using namespace grapic;
const int DIMW = 600 ;
const float FRI=0.9;
const int MAX_DINO= 2;
const int MAX_OB=6;

struct Complex {
    float x,y;
};

struct Dino {
    Complex pos;
    Complex vitesse;
    bool enSaut;
};

struct Obstacle {
    int pos;
    int taille;
    bool actif;
};
struct World {
    Dino DG; //mon dinogntille :)
    Dino DM; //mon dino mechant :(
    Obstacle O[MAX_OB];
    int nobs;
    float vitesse;// je l'ajoute pour le moment mais je sais pas je suis pas sur a voir avec la prof
    int t;
};
Complex make_complex(float r, float i)
{
    Complex c;
    c.x = r;
    c.y = i;
    return c;
}
Complex make_complex_expo(float r, float theta)
{
    Complex c;
    c.x = r*cos(theta);
    c.y = r*sin(theta);
    return c;
}
Complex operator+(Complex a, Complex b)
{
    return make_complex( a.x+b.x, a.y+b.y );
//    Complex c = make_complex( a.x+b.x, a.y+b.y );
//    return c;
}
Complex operator-(Complex a, Complex b)
{
    Complex c = make_complex( a.x-b.x, a.y-b.y );
    return c;
}
Complex translate(Complex p, float dx, float dy)
{
    return p + make_complex(dx,dy);
}
Complex operator*(float a, Complex b)
{
    Complex c = make_complex( a*b.x, a*b.y );
    return c;
}
Complex operator*(Complex b, float a)
{
    Complex c = make_complex( a*b.x, a*b.y );
    return c;
}
Complex operator/(Complex b, float d)
{
    Complex c = make_complex( b.x/d, b.y/d );
    return c;
}
Complex operator*(Complex a, Complex b)
{
    Complex c = make_complex( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x );
    return c;
}

Dino initDino(Complex pos,Complex vit) {
    Dino D;
    D.pos=pos;
    D.vitesse=vit;
    return D;
}
void initObstacles(World& w)
{
    int depart = 200;
    int ecartmin = 50;

    for (int i = 0; i < MAX_OB; i++)
    {
        int taille = rand() % 10+20;
        int ecart =  rand() % 100+ ecartmin;
        w.O[i].pos = depart;
        w.O[i].taille = taille; //taille
        w.O[i].actif = true;

        depart += taille + ecart;
        cout << endl <<  w.O[i].pos;
    }


    w.nobs = MAX_OB;
}

void initWorld(World &w)
{
    w.DG = initDino({90, 0}, {5, 5});
    w.DM = initDino({30, 0}, {0, 0}); // prédateur pas encore visible
    w.vitesse = 4.0;
    w.t = elapsedTime();
    w.nobs = MAX_OB;
    initObstacles(w);
}


void drawDino(Dino D) {
    color(0,200,0);
    circleFill(D.pos.x,D.pos.y,10);
}

void drawObstacles(World w)
{
    for (int i = 0; i < w.nobs; i++)
    {
        if (w.O[i].actif)
        {
            color(244, 24, 147);
            rectangleFill(w.O[i].pos, 0, w.O[i].pos + w.O[i].taille, 40);
        }
    }
}
void collision(Dino &d, World &w)
{
    float dinoG = d.pos.x - 50;
    float dinoD = d.pos.x + 50;

    for (int i = 0; i < w.nobs; i++)
    {
        if (w.O[i].actif)
        {
            float obsG = w.O[i].pos;
            float obsD = w.O[i].pos + 100;

            // test horizontal
            if (dinoD >= obsG)
            {
                if (dinoG <= obsD)
                {
                    // test vertical
                    if (d.pos.y <= 0)
                    {
                        color(255,0,0);
                        print(DIMW/2-10, DIMW/2, "YOU HAVE LOST");
                        delay(3000);
                        // Repositionner le dino
                        d.pos = make_complex(90, 0);
                        d.vitesse = make_complex(0, 0);
//ou d = initDino(make_complex(90, 0), make_complex(0, 0));

                        d.enSaut = false;


                        initObstacles(w);
                    }
                }
            }
        }
    }
}

void update(Dino &d, World &w)
{
    loat impulsion =1150;
    float gravite=-0.89 
    float sol=0.0;

    // Touche espace pour sauter
    if (!d.enSaut && isKeyPressed(' '))
    {
        d.vitesse.y = impulsion;
        d.enSaut = true;
    }

    d.vitesse.y += gravite;// Appliquer la gravité
    d.pos.y += d.vitesse.y;

    // Revenir au sol
    if (d.pos.y <= sol )
    {
        d.pos.y = sol;
        d.vitesse.y = 0;
        d.enSaut = false;
    }

    //update des obs
    f/*or (int i = 0; i < w.nobs; i++)
    {
        if (w.O[i].actif)
        {
            w.O[i].pos -= 4w.vitesse; // vitesse du défilement 5pix maintenent on change la vitesse pour aller plus vite
            // il sort de l'écran on le remet à droite avec une nouvelle taille idée 1
            if (w.O[i].pos + w.O[i].taille < 0)
            {
                w.O[i].pos = DIMW -+550 
                 .O[i].taille =rand() % 10++20
                 ir (i > 0)
                {
                    int ecart = w.O[i].pos - (w.O[i - 1].pos + w.O[i - 1].taille);
                    if (ecart < 50)
                    {
                        w.O[i].pos += 50 - ecart + rand() % 30;
                    }
                }

            }

        }

    }*/
    for (int i = 0; i < w.nobs; i++)
    {
        if (w.O[i].actif)
        {
            w.O[i].pos -= w.vitesse;

            // Si l'obstacle est sorti de l'écran
            if (w.O[i].pos + w.O[i].taille < 0)
            {
                int nouvellePos = DIMW;

                // Si l'obstacle précédent est encore visible, on s'aligne sur lui
                if (i > 0 && w.O[i - 1].pos > 0)
                {
                    nouvellePos = w.O[i - 1].pos + w.O[i - 1].taille + 50 + rand() % 50;
                }

                w.O[i].pos = nouvellePos;
                w.O[i].taille = rand() % 10 + 20;
            }
        }
    }
    // collision(d, w);
    if (elapsedTime() - w.t > 20) {
        w.vitesse += 0.0001;
        //backgroundColor( 250,0,0);
        w.t= elapsedTime();
    }
}





int main(int, char ** )
{
    srand(time(NULL));
    bool stop=false;
    winInit("Particles", DIMW, DIMW);
    backgroundColor( 156, 120, 215 );
    World dat;
    //Dino D;
    //D=initDino({90,0}, {5,5});
    //D2=initDino({30,0}, {0,0});
    //dat.vitesse = 4.0;
    //initObstacles(dat);
    //dat.t=elapsedTime ();
    initWorld(dat);
    while( !stop )
    {
        winClear();
        drawDino(dat.DG); // dessine les particules
        // drawDino(D2);
        //updateDino(D2);
        drawObstacles(dat);
        update(dat.DG,dat);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}