#include <math.h>
#include <stdlib.h>

#define mrand(min, max) \
  ((((double) max) - ((double) min)) * ((double) rand()) / (double) RAND_MAX + ((double) min))

struct CVec
{
  double x, y, z;

  CVec() {}
  CVec(double r)
  {
    // Random spherical position with constant density
    do
    {
      x = mrand(-r, r);
      y = mrand(-r, r);
      z = mrand(-r, r);
    }
    while(sqrt(x*x + y*y + z*z));
  }
};

struct CBody
{
  double Mass;
  CVec Position;
  CVec Velocity;
  CVec Magnetic;

  double Angle;
  CVec Rotation;

  double Radius;
};

const int NumBodies = 64;
CBody Bodies[NumBodies];

void Init()
{
  // Initialize random generator with constant value
  srand(1234);

  // Initialize bodies
  for(int i = 0; i < NumBodies; i++)
  {
    Bodies[i].Mass = mrand(1e30, 1e32); // kg
    Bodies[i].Position = CVec(1e18); // m
    Bodies[i].Velocity = CVec(1e6); // m/s
    Bodies[i].Magnetic = CVec(1e8); // T

    Bodies[i].Angle = mrand(0, 2 * M_PI); // rad
    Bodies[i].Rotation = CVec(1); // Hz

    Bodies[i].Radius = mrand(1e8, 1e10); // m
  }
}

void Step()
{
  // ...
}
