// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// RVA 0x005F93F0, full 95-byte callback. Cylinder constructor 0x005E37C0
// installs vtable VA 0x01111964 in the subobject at +0x18. Its slot zero
// reaches this body through ILT 0x0002ED1B. The original method name and
// the semantic type of the copied third word are not established.
extern "C" double __cdecl sqrt(double value);
extern const float Rva00C75350Zero;
extern const float Rva00C75334One;

namespace FXParticleSystem {

struct Rva005F93F0Coord3D {
    Rva005F93F0Coord3D() {}
    Rva005F93F0Coord3D(const Rva005F93F0Coord3D &that)
    {
        x = that.x;
        y = that.y;
        trailingWord = that.trailingWord;
    }
    float x;
    float y;
    unsigned int trailingWord;
};

struct Rva005F93F0Input {
    float x;
    float y;
};

// A view of the +0x18 callback subobject, not the complete Cylinder object.
class Rva005F93F0CylinderCallbackView {
public:
    virtual Rva005F93F0Coord3D Rva005F93F0CylinderCallback(
        const Rva005F93F0Input *input, float scale, unsigned int trailingWord);
};

Rva005F93F0Coord3D Rva005F93F0CylinderCallbackView::Rva005F93F0CylinderCallback(
    const Rva005F93F0Input *input, float scale, unsigned int trailingWord)
{
    float x = input->x;
    float y = input->y;
    float length = (float)sqrt(y * y + x * x);
    if (length != Rva00C75350Zero) {
        float inverseLength = Rva00C75334One / length;
        x = x * inverseLength;
        y = y * inverseLength;
    }
    Rva005F93F0Coord3D result;
    result.trailingWord = trailingWord;
    result.x = x * scale;
    result.y = y * scale;
    return result;
}

}
