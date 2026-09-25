// ?update@Rva00593E60State@@QAEXXZ
// partial score=0.9758308157 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
#include "unicode_string.h"

// Four Unicode strings and a trailing UTF-16 code unit, witnessed by
// 0058BE30 (copy), 0058C4C0 (destruction), and 005933A0 (comparison).
class Rva0058BE30FourString {
public:
    Rva0058BE30FourString(const Rva0058BE30FourString &);
    ~Rva0058BE30FourString();
private:
    UnicodeString m_string0, m_string4, m_string8, m_stringC;
    unsigned short m_word10;
};
class Rva00564A10 { public: static void go(); };
class Rva00564A40 { public: static void go(); };
extern void __cdecl Rva00564A70(bool);
struct Rva005933A0Value;
extern int __cdecl rva005933A0Equal(const Rva005933A0Value *, const Rva005933A0Value *);
class Rva005907F0 { public: void release(); };
class BfmeRefCHB;
class BfmeThingCHB { public: void bfmeGoCHB(BfmeRefCHB *); };
// Only the observed slot is typed; this view makes no Display identity claim.
struct Rva00593E60DisplayView {
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
    virtual bool slot58();
};
class Display;
extern Display *TheDisplay;
class Rva00593E60State {
public:
    unsigned char m_byte0, m_byte1, m_byte2, m_pad3;
    int m_value4;
    Rva0058BE30FourString *m_ptr8, *m_ptrC;
    int m_value10;
    void notify(Rva0058BE30FourString *);
    void update();
};
void Rva00593E60State::update() {
    if (m_value4 < 0) {
        if (!m_byte2) { Rva00564A40::go(); m_byte2 = 1; }
        return;
    }
    if (m_byte2) { Rva00564A10::go(); m_byte2 = 0; }
    if (!m_byte0) { delete m_ptrC; m_ptrC = 0; }
    if (m_ptr8) {
        if (m_ptrC && !static_cast<unsigned char>(rva005933A0Equal(
            reinterpret_cast<Rva005933A0Value *>(m_ptr8),
            reinterpret_cast<Rva005933A0Value *>(m_ptrC)))) {
            if (m_byte0) { Rva00564A10::go(); m_byte0 = 0; }
            reinterpret_cast<Rva005907F0 *>(&m_ptrC)->release();
        }
        if (!m_ptrC) {
            Rva0058BE30FourString *entry = new Rva0058BE30FourString(*m_ptr8);
            reinterpret_cast<BfmeThingCHB *>(&m_ptrC)->bfmeGoCHB(reinterpret_cast<BfmeRefCHB *>(entry));
            notify(m_ptrC);
        }
        m_value10 = 5;
    } else if (m_ptrC && m_value10 <= 0) {
        if (m_byte0) { Rva00564A10::go(); m_byte0 = 0; }
        reinterpret_cast<Rva005907F0 *>(&m_ptrC)->release();
    } else {
        --m_value10;
    }
    if (m_byte0) {
        bool state = reinterpret_cast<Rva00593E60DisplayView *>(TheDisplay)->slot58();
        if (m_byte1 != state) { Rva00564A70(state); m_byte1 = state; }
    }
}
