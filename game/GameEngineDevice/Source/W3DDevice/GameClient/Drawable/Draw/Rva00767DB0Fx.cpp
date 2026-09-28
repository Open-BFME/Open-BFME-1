// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x00767DB0, 293 bytes; generated extent ends in ret 0x14.
// Unknown owner: retain its address identity. Receiver +8 supplies a pointer
// at +0xfc; receiver +0x34 supplies virtual slot +0xcc returning a Matrix3D.
// The 20-byte value owns an AsciiString at +0x0c and an FXList pointer at +0x10.
// Do not conflate it with Open2Rec767F60: that record retains a counted pointer.
// The complete body only destroys the string. All three FX calls use existing
// ILT pins, independently backed by FXListDoFXObjStatic.cpp and the matched
// doFXObj/doFXPos bodies. Matrix3D's real header supplies its 48-byte copy.
// Inline accessors reproduce ECX for the +8/+0xfc chain; no synthetic register
// forcing or speculative class identity is needed.
#include "ascii_string.h"
#include "matrix3d.h"

template<> inline StringBase<char>::~StringBase() { releaseBuffer(); }
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }

struct Coord3D { float x, y, z; };
class Object;
class FXList {
public:
    bool bfmeIsBlocked() const;
    void doFXObj(const Object *, const Object *) const;
    void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
};
struct Rva00767DB0Value {
    int at00, at04, at08;
    AsciiString at0c;
    const FXList *at10;
};
struct Rva00767DB0Drawable {
    char pad00[0xfc];
    Object *atfc;
    Object *readAtfc() const { return atfc; }
};
class Rva00767DB0Render {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual const Matrix3D &atcc(const char *);
};
class Rva00767DB0 {
public:
    char pad00[8];
    Rva00767DB0Drawable *at08;
    char pad0c[0x28];
    Rva00767DB0Render *at34;
    Rva00767DB0Drawable *readAt08() const { return at08; }
    void invoke(Rva00767DB0Value value);
};

void Rva00767DB0::invoke(Rva00767DB0Value value)
{
    if (value.at10) {
        if (!value.at0c.isEmpty()) {
            Matrix3D matrix = at34->atcc(value.at0c.str());
            Coord3D pos;
            pos.x = matrix[0][3];
            pos.y = matrix[1][3];
            pos.z = matrix[2][3];
            const FXList *fx = value.at10;
            if (fx && !fx->bfmeIsBlocked())
                fx->doFXPos(&pos, &matrix, 0.0f, 0);
        } else {
            Object *object = readAt08()->readAtfc();
            const FXList *fx = value.at10;
            if (!fx->bfmeIsBlocked())
                fx->doFXObj(object, 0);
        }
    }
}
