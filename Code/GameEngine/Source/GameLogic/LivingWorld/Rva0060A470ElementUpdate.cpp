// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug
#include "ascii_string.h"
#include "hanim.h"
#include "vector3.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
class Rva0060A470Target {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0(HAnimClass *, float, int);
};
class Rva0061DA30Base {
public:
    Rva0061DA30Base(AsciiString);
    void *word0, *word4;
    Rva0060A470Target *ptr8;
    char opaqueC[0xA0-0xC];
};
class Rva0060A470ObjectView {
public:
    virtual int slot0(AsciiString);
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C(Vector3);
};
class BfmeAnimationHolder { public: void applyRotationPayload(float); };
class Rva0060A470GlobalView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28(Rva0060A470Target *);
};
class BfmeHostESM;
extern BfmeHostESM *g_bfmeStateDF;
extern HAnimClass *Get_HAnim(const char *);
class Rva0060A470Element {
public:
    unsigned int word0;
    Rva0061DA30Base *ptr4;
    float float8;
    AsciiString stringC;
    bool byte10;
    char opaque11[3];
    float float14;
    AsciiString string18;
    Vector3 point1C;
    bool update();
};
// Retail 0060A470 has no arguments and returns AL. Constructor 0061DA30
// receives the string at +18 by value; initialization receives +0C. The
// position is a Vector3 copied by value at slot 1C. The scalar constant is
// retail float 01075954 (degrees to radians); the animation separator at
// 01081D4C is ".". All object pointers are reloaded after callbacks.
bool Rva0060A470Element::update()
{
    ptr4 = new Rva0061DA30Base(string18);
    if (reinterpret_cast<Rva0060A470ObjectView *>(ptr4)->slot0(stringC)) {
        reinterpret_cast<Rva0060A470ObjectView *>(ptr4)->slot1C(point1C);
        reinterpret_cast<BfmeAnimationHolder *>(ptr4)->applyRotationPayload(
            float14 * 0.01745329238474369f);
        if (ptr4->ptr8) {
            reinterpret_cast<Rva0060A470GlobalView *>(g_bfmeStateDF)->slot28(ptr4->ptr8);
            if (byte10) {
                AsciiString name(stringC);
                name.concat(".");
                name.concat(stringC);
                HAnimClass *animation = Get_HAnim(name.str());
                if (animation) {
                    int frames = animation->Get_Num_Frames();
                    float time = frames * float8;
                    ptr4->ptr8->slotB0(animation, time, 1);
                    animation->Release_Ref();
                }
            }
            return true;
        }
    }
    return false;
}
