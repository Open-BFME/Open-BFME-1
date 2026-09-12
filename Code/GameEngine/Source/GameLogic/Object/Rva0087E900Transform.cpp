// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

extern "C" double __cdecl sin(double angle);
extern "C" double __cdecl cos(double angle);
struct Rva0087E900Coord { float x; float y; float z; };
struct Rva0087E900Shape { char pad[0x10]; Rva0087E900Coord m_field0x10; };
void Rva0087E900(Rva0087E900Coord *out,
    const Rva0087E900Coord *position,
    const Rva0087E900Shape *shape,
    float angle)
{
    // Volatile accesses preserve retail x87 scheduling; storage itself is ordinary.
    float raw[6];
    volatile float *scratch = raw;
    float sine = (float)sin(angle);
    scratch[1] = shape->m_field0x10.y;
    scratch[2] = shape->m_field0x10.z;
    float cosine = (float)cos(angle);
    float shapeX = shape->m_field0x10.x;
    volatile float &angleRef = angle;
    angleRef = shapeX;
    float rotatedX = cosine * shapeX;
    rotatedX -= scratch[1] * sine;
    scratch[4] = position->y;
    raw[5] = position->z;
    scratch[0] = rotatedX;
    float rotatedY = angleRef * sine + scratch[1] * cosine;
    float outputX = position->x;
    outputX += scratch[0];
    scratch[3] = outputX;
    float outputY = rotatedY + scratch[4];
    float outputZ = scratch[5] + raw[2];
    out->x = scratch[3];
    out->y = outputY;
    out->z = outputZ;
}
