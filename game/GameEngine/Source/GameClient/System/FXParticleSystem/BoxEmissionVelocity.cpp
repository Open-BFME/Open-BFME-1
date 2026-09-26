// Box emission-volume callback at retail RVA 0x005F86C0.
// The Box createModule body at 0x005E9060 installs callback vptr
// 0x01112358 at complete-object +0x18.  Its slot 0 is ILT VA
// 0x00414DE9 (ILT RVA 0x00014DE9), which reaches this body.  This is a view
// of that +0x18 callback subobject, not a complete Box object.
// cl: /DNDEBUG /MD /GX- /O2 /Ob2
#include <math.h>

extern const float Rva00C75350Zero;
extern const float Rva00C75334One;

struct Rva005F86C0Coord3DBase {
    float x;
    float y;
    float z;
};

class Rva005F86C0Coord3D : public Rva005F86C0Coord3DBase {
public:
    Rva005F86C0Coord3D(const Rva005F86C0Coord3D &that) {
        x = that.x;
        y = that.y;
        z = that.z;
    }
    ~Rva005F86C0Coord3D() {}

    __forceinline float length() const {
        return (float)sqrt(x * x + y * y + z * z);
    }
    __forceinline void normalize() {
        float len = length();
        if (len != Rva00C75350Zero) {
            float inverse_length = Rva00C75334One / len;
            x *= inverse_length;
            y *= inverse_length;
            z *= inverse_length;
        }
    }
    __forceinline void scale(float value) {
        x *= value;
        y *= value;
        z *= value;
    }
};

// Address-qualified view of the virtual callback subobject at complete-object
// +0x18.  The final trailing argument is retained as an opaque unsigned word.
class Rva005F86C0BoxCallbackView {
public:
    virtual Rva005F86C0Coord3D Rva005F86C0Velocity(
        const Rva005F86C0Coord3D *position, float speed, unsigned int trailing);
};

Rva005F86C0Coord3D Rva005F86C0BoxCallbackView::Rva005F86C0Velocity(
    const Rva005F86C0Coord3D *position, float speed, unsigned int)
{
    Rva005F86C0Coord3D velocity = *position;
    velocity.normalize();
    velocity.scale(speed);
    return velocity;
}
