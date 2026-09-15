// ?transformPointsAt0018F660@Gen_0018F210@@QAEXPBVMatrix3D@@@Z
// partial score=0.9 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
#include "matrix3d.h"
struct BfmeVector3BG { int x,y,z; };
class Gen_0018F210 {
public:
    void transformPointsAt0018F660(const Matrix3D *matrix);
private:
    char m_head[0x10];
    BfmeVector3BG *m_values;
    int m_count;
    int m_capacity;
    char m_gap[0x14];
    bool m_valuesDirty;
};
void Gen_0018F210::transformPointsAt0018F660(const Matrix3D *matrix)
{
    if(!matrix) return;
    for(int i=0;i<m_count;++i) {
        Vector3 input((float)m_values[i].x,(float)m_values[i].y,(float)m_values[i].z);
        Matrix3D::Transform_Vector(*matrix,input,&input);
        m_values[i].x=(int)input.X;
        m_values[i].y=(int)input.Y;
        m_values[i].z=(int)input.Z;
    }
    m_valuesDirty=true;
}
