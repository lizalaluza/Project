#define bricks

const float DT = 0.01;


struct Brick
    {
    float x;
    float y;
    bool exist;
    };

void circleMove(float* x, float vx, float* y, float vy)
{
    *x += vx * DT;
    *y += vy * DT;
}

void checkCollision(float* x, float* vx, float* y, float* vy, int windowx, int windowy, float radius)
{
    if ((*x >= windowx - 2 * radius) or (*x <= 0))
    {
         *vx = - *vx;
    }

    if ((*y >= windowy - 2 * radius) or (*y <= 0))
    {
        *vy = - *vy;
    }
}

void resolveWallCollision(float* x, float* vx, float* y, float* vy, float radius, int windowx, int windowy)
{
    if (*x < 0)
    {
        *x += *x + radius;
    }

    if (*x + 2 * radius > windowx)
    {
        *x -= - windowx + *x + radius;
    }

    if (*y < 0)
    {
        *y += -*y + radius;
    }

    if (*y + 2 * radius > windowy)
    {
        *y -= - windowy + *y + radius;
    }
}

void collisionTablet(float stickx, float sticky, float sticklx, float x, float y, float* vy, float radius, const float DT)
{
    if ((y + 2 * radius >= sticky) and (y + 2 * radius < sticky + *vy * DT) and (x <= stickx + sticklx) and (x + 2*radius >= stickx))
    {
        *vy = -*vy;
    }

}

void brickCollision(float x, float y, float *vx, float *vy, float radius, const float DT, Brick* brick1)
{
    
        if (brick1->exist)
        {
            if ((brick1->x <= x + radius) and (brick1->x + 80 >= x + radius) and (brick1->y <= y + 2 * radius) and ( brick1->y + *vy * DT >= y + 2 * radius))
                {
                    *vy = - *vy;
                    brick1->exist = false ;
                }
            else if ((brick1->x <= x + radius) and (brick1->x + 80 >= x + radius) and ( brick1->y >= y) and ( brick1->y + *vy * DT <= y ))
                {
                    *vy = - *vy;
                    brick1->exist = false ;
                }
            else if ((brick1->x <= x + 2 * radius) and (brick1->x + *vx * DT >= x + 2 * radius) and ( brick1->y <= y + radius) and ( brick1->y + 30 >= y + radius))
                {
                    *vx = - *vx;
                    brick1->exist = false ;
                }
            else if ((brick1->x + *vx * DT <= x ) and (brick1->x + 80 >= x ) and ( brick1->y <= y + radius) and ( brick1->y + 30 >= y + radius))
                {
                    *vx = - *vx;
                    brick1->exist = false ;
                }    
        }
    
}
