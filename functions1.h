#define functions

class Sphere
{
public:
    double radius;
    double x;
    double y;
    int N;
    double vx;
    double vy;
    double ax;
    double ay;
    int r;
    int g;
    int b;
    int m;

    void draw()
    {
        COLORREF OldFillColor = txGetFillColor();
        COLORREF OldColor = txGetColor();

        for (int i = 1; i < N; i++)
        {
            txSetFillColor(RGB(i * r / N, i * g / N, i * b / N));
            txSetColor    (RGB(i * r / N, i * g / N, i * b / N));
            txCircle(x, y, radius - radius * i / N);
        }

        txSetFillColor(OldFillColor);
        txSetColor(OldColor);

    }

    void speed(const double DT)
    {
        vx += ax * DT;
        vy += ay * DT;
    }

    void move(const double DT)
    {
        x += vx * DT;
        y += vy * DT;
    }

    bool checkTwoSpheres(Sphere sphere1, Sphere sphere2)
    {
        if (sphere1.radius + sphere2.radius > sqrt(pow(sphere1.x - sphere2.x, 2)+ pow(sphere1.y - sphere2.y, 2)))
        {
            return true;
        }
        return false;
    }

    void collisionTwoSpheres(Sphere sphere1, Sphere sphere2)
    {
        double distx = sphere1.x - sphere2.x;
        double disty = sphere1.y - sphere2.y;

        double hypotenuse = sqrt(distx * distx + disty * disty);

        double sin = distx / hypotenuse;
        double cos = disty / hypotenuse;
            if (hypotenuse < sphere1.radius + sphere2.radius)
            {
                double Vn1 = sphere2.vx * sin + sphere2.vy * cos;
                double Vn2 = sphere1.vx * sin + sphere1.vy * cos;
                double Vt1 = - sphere2.vx * cos +sphere2.vy * sin;
                double Vt2 = - sphere1.vx * cos + sphere1.vy * sin;
                double dt = (sphere2.radius + sphere1.radius - hypotenuse) / (Vn1 - Vn2);

                if (dt > 0.5)
                {
                    dt = 0.5;
                }
                if (dt < - 0.5)
                {
                    dt = - 0.5;
                }
                sphere1.x = sphere1.x - sphere1.vx * dt;
                sphere1.y = sphere1.y - sphere1.vy * dt;
                sphere2.x = sphere2.x - sphere2.vx * dt;
                sphere2.y = sphere2.y - sphere2.vy * dt;

                distx = sphere1.x - sphere2.x;
                disty = sphere1.y - sphere2.y;

                double back = Vn2;
                Vn2 = Vn1;
                Vn1 = back;


                sphere1.vx = Vn2 * sin - Vt2 * cos;
                sphere1.vy = Vn2 * cos + Vt2 * sin;
                sphere2.vx = Vn1 * sin - Vt1 * cos;
                sphere2.vy = Vn1 * cos + Vt1 * sin;
            }

    }

    void resolveWallCollision(Sphere sphere, int windowx, int windowy)
    {
        if (sphere.x < sphere.radius)
        {
            sphere.x += - sphere.x + sphere.radius;
            sphere.vx = - sphere.vx;
        }

        if (sphere.x + sphere.radius > windowx)
        {
            sphere.x -= - fabs(windowx - sphere.x) + sphere.radius;
            sphere.vx = - sphere.vx;
        }

        if (sphere.y < sphere.radius)
        {
            sphere.y += - sphere.y +sphere.radius;
            sphere.vy = - sphere.vy;
        }

        if (sphere.y + sphere.radius > windowy)
        {
            sphere.y -= - fabs(windowy - sphere.y) + sphere.radius;
            sphere.vy = - sphere.vy;
        }
    }

    void checkCollision(Sphere sphere, int windowx, int windowy)
    {

        if ((sphere.x > windowx - sphere.radius) or (sphere.x < sphere.radius))
        {
            sphere.vx = - sphere.vx;
        }

        if ((sphere.y > windowy - sphere.radius) or (sphere.y < sphere.radius))
        {
            sphere.vy = - sphere.vy;
        }
    }

    void zero_acc()
    {
        ax = 0;
        ay = 0;
    }

};

class Spring
{
public:
    double length;
    double k;

};

//void acc(struct Sphere*, struct Spring);
//void speed(struct Sphere*, double DT);
//void draw(struct Sphere);
//void drawlines(struct Sphere sphere1, struct Sphere sphere2, struct Spring spring);
//void move(struct Sphere* , double DT);
//void checkCollision(struct Sphere* , int windowx, int windowy);
//void collisionTwoSpheres(struct Sphere* , struct Sphere* );
//void resolveWallCollision(struct Sphere* , int windowx, int windowy);

void acc(Sphere* sphere1, Sphere* sphere2, Spring spring)
    {
        double dist = sqrt((sphere1->x - sphere2->x) * (sphere1->x - sphere2->x) + (sphere1->y - sphere2->y) * (sphere1->y - sphere2->y));
        if (sphere1->x < sphere2->x)
        {
            sphere1->ax += spring.k * (dist - spring.length) / sphere1->m;
            sphere2->ax -= spring.k * (dist - spring.length) / sphere2->m;
        }
        if (sphere1->x > sphere2->x)
        {
            sphere1->ax -= spring.k * (dist - spring.length) / sphere1->m;
            sphere2->ax += spring.k * (dist - spring.length) / sphere2->m;
        }
        if (sphere1->y < sphere2->y)
        {
            sphere1->ay += spring.k * (dist - spring.length) / sphere1->m;
            sphere2->ay -= spring.k * (dist - spring.length) / sphere2->m;
        }
        if (sphere1->x > sphere2->x)
        {
            sphere1->ay -= spring.k * (dist - spring.length) / sphere1->m;
            sphere2->ay += spring.k * (dist - spring.length) / sphere2->m;
        }
    }


void drawlines(Sphere sphere1, Sphere sphere2, Spring spring)
    {
        COLORREF OldColor = txGetColor();
                txSetColor (RGB(255,255,255));
                if (spring.k != 0)
                {
                    txLine(sphere1.x, sphere1.y, sphere2.x, sphere2.y);
                }
        txSetColor(OldColor);
    }

