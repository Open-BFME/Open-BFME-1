// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/dx81/include /Iinputs/toolchains/vs2003/PROGRA~1/MICROS~1.NET/Vc7/PlatformSDK/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
#include "vector3.h"
// Retail 0x003A14C0, 829 bytes, cdecl with seven arguments. The original
// function name is unproved; keep the address in this behavioral name.
// Vector3's three-float layout and inline arithmetic reproduce every retail
// operation. Each polynomial term must be a separate local to retain the
// original x87 expression evaluation order and 0x78-byte frame.
//
// Native D3DX Catmull-Rom ABI, independently proven by the vendored
// public thunk and its private dispatch-table entry (not a PE import).
#include <d3dx8math.h>
void catmullRom003A14C0(Vector3 *out, const Vector3 *p0, const Vector3 *p1, const Vector3 *p2, const Vector3 *p3, float t, bool imported)
{
    if (imported) {
        D3DXVec3CatmullRom(reinterpret_cast<D3DXVECTOR3 *>(out),
            reinterpret_cast<const D3DXVECTOR3 *>(p0),
            reinterpret_cast<const D3DXVECTOR3 *>(p1),
            reinterpret_cast<const D3DXVECTOR3 *>(p2),
            reinterpret_cast<const D3DXVECTOR3 *>(p3), t);
        return;
    }
    float t2 = t*t;
    float t3 = t*t2;
    Vector3 a = *p0, b = *p1, c = *p2, d = *p3;
    Vector3 q0 = 2.0f*b;
    Vector3 q1 = (c-a)*t;
    Vector3 q2 = (2.0f*a-5.0f*b+4.0f*c-d)*t2;
    Vector3 q3 = (3.0f*b-a-3.0f*c+d)*t3;
    *out = (q0+q1+q2+q3)*0.5f;
}
