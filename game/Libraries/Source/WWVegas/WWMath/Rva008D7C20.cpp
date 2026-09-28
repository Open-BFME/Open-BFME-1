// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#include "matrix4.h"
#include "matrix3d.h"
class Rva008D7C20 : public Matrix3D {
public: void inverse(Matrix3D &out) const;
};
void Rva008D7C20::inverse(Matrix3D &out) const {
    Matrix4 mat(*this);
    Matrix4 result = mat.Inverse();
    out[0][0] = result[0][0];
    out[0][1] = result[0][1];
    out[0][2] = result[0][2];
    out[0][3] = result[0][3];
    out[1][0] = result[1][0];
    out[1][1] = result[1][1];
    out[1][2] = result[1][2];
    out[1][3] = result[1][3];
    out[2][0] = result[2][0];
    out[2][1] = result[2][1];
    out[2][2] = result[2][2];
    out[2][3] = result[2][3];
}
// Proven extent: 0x008D7C20..0x008D80BF; terminal RET 4 then INT3 before the proven Multiply start. Original name remains unproven.
