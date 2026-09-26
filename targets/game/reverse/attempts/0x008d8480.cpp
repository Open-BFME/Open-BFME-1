// ?Lerp@Matrix3D@@SAXABV1@0MAAV1@@Z
// partial score=0.17 date=2026-09-23
// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "matrix3d.h"
#include "vector3.h"
#include "quat.h"
#include <math.h>

extern float g_bfmeDefaultBU;
extern float Rva00D377C0Float;

// ?Lerp@Matrix3D@@SAXABV1@0MAAV1@@Z
void Matrix3D::Lerp(const Matrix3D &A, const Matrix3D &B, float factor, Matrix3D &result)
{
    Vector3 position;
    Vector3::Lerp(A.Get_Translation(), B.Get_Translation(), factor, &position);
    float scale = (float)sqrt(A.Row[2].X * A.Row[2].X + A.Row[2].Y * A.Row[2].Y + A.Row[2].Z * A.Row[2].Z);

    if (fabs(scale - g_bfmeDefaultBU) > Rva00D377C0Float) {
        Matrix3D scaledA = A;
        Matrix3D scaledB = B;
        float inverseScale = g_bfmeDefaultBU / scale;

        scaledA.Row[0].X *= inverseScale;
        scaledA.Row[1].X *= inverseScale;
        scaledA.Row[2].X *= inverseScale;
        scaledA.Row[0].Y *= inverseScale;
        scaledA.Row[1].Y *= inverseScale;
        scaledA.Row[2].Y *= inverseScale;
        scaledA.Row[0].Z *= inverseScale;
        scaledA.Row[1].Z *= inverseScale;
        scaledA.Row[2].Z *= inverseScale;

        scaledB.Row[0].X *= inverseScale;
        scaledB.Row[1].X *= inverseScale;
        scaledB.Row[2].X *= inverseScale;
        scaledB.Row[0].Y *= inverseScale;
        scaledB.Row[1].Y *= inverseScale;
        scaledB.Row[2].Y *= inverseScale;
        scaledB.Row[0].Z *= inverseScale;
        scaledB.Row[1].Z *= inverseScale;
        scaledB.Row[2].Z *= inverseScale;

        Quaternion rotation;
        Slerp(rotation, Build_Quaternion(scaledA), Build_Quaternion(scaledB), factor);
        result.Set_Rotation(rotation);
        result.Set_Translation(position);

        result.Row[0].X *= scale;
        result.Row[1].X *= scale;
        result.Row[2].X *= scale;
        result.Row[0].Y *= scale;
        result.Row[1].Y *= scale;
        result.Row[2].Y *= scale;
        result.Row[0].Z *= scale;
        result.Row[1].Z *= scale;
        result.Row[2].Z *= scale;
    } else {
        Quaternion rotation;
        Slerp(rotation, Build_Quaternion(A), Build_Quaternion(B), factor);
        result.Set_Rotation(rotation);
        result.Set_Translation(position);
    }
}
