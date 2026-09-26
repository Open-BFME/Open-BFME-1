#include <math.h>

class Rva006E1CA0Vector {
public:
    static float length(const Rva006E1CA0Vector *vector);

private:
    float m_x;
    float m_y;
    float m_z;
};

float Rva006E1CA0Vector::length(const Rva006E1CA0Vector *vector)
{
    return sqrt(vector->m_x * vector->m_x + vector->m_y * vector->m_y + vector->m_z * vector->m_z);
}
