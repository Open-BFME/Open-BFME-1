// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2

#include "aabox.h"
#include "simplevec.h"
#include "vector3.h"

class BfmeStreakObject
{
public:
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;

private:
    unsigned char m_renderObject[0xC4];
    SimpleDynVecClass<Vector3> m_points;
    SimpleDynVecClass<float> m_widths;
    unsigned char m_rendererPrefix[8];
    float m_width;
};

void BfmeStreakObject::Get_Obj_Space_Bounding_Box(AABoxClass &box) const
{
    unsigned int count = m_points.Count();

    if (count >= 2) {
        Vector3 maximum = m_points[0];
        Vector3 minimum = m_points[0];

        for (unsigned int i = 1; i < count; ++i) {
            maximum.Update_Max(m_points[i]);
            minimum.Update_Min(m_points[i]);
        }

        float expansion = m_width * 0.5f;
        Vector3 offset(expansion, expansion, expansion);
        maximum += offset;
        minimum -= offset;
        box.Init_Min_Max(minimum, maximum);
    } else {
        box.Init(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));
    }
}
