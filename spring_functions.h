#define spring_functions

struct Spring
{
    double length;
    double k;
};

void acc(struct Sphere*, struct Spring);
void zero_acc(struct Sphere*);
void drawlines(struct Sphere sphere1, struct Sphere sphere2, struct Spring spring);


void acc(struct Sphere* sphere1, struct Sphere* sphere2, struct Spring spring)
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

void zero_acc(struct Sphere* sphere)
{
    sphere->ax = 0;
    sphere->ay = 0;
}

void drawlines(struct Sphere sphere1, struct Sphere sphere2, struct Spring spring)
{
    COLORREF OldColor = txGetColor();
            txSetColor (RGB(250,0,0));
            if (spring.k != 0)
            {
                txLine(sphere1.x, sphere1.y, sphere2.x, sphere2.y);
            }
    txSetColor(OldColor);
}
