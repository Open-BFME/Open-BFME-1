// ?rva005900C0@Rva00593E60State@@QAEXPAVRva0058BE30FourString@@@Z
// partial score=0.9921 date=2026-09-29
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x005900C0, 764 bytes. The matched Rva00593E60State::update
// establishes this owner and record ABI. Five text receivers at +14..24
// use slots +4 (UnicodeString by value) and +3C (two integer out pointers).
#include "unicode_string.h"

extern const char g_bfmeEmptyUnicode[];
template<class T> inline StringBase<T>::StringBase() : m_data(0) {}
template<class T> inline bool StringBase<T>::isEmpty() const { return !m_data || !m_data->length; }
template<class T> inline bool StringBase<T>::isNotEmpty() const { return m_data && m_data->length; }
template<class T> inline const T *StringBase<T>::str() const { return m_data ? m_data->data : (const T *)g_bfmeEmptyUnicode; }
template<class T> inline void StringBase<T>::swap(StringBase<T>& other) { Header *p=m_data; m_data=other.m_data; other.m_data=p; }
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s); }
inline UnicodeString::UnicodeString(const wchar_t *s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase((const unsigned short*)s); }
inline UnicodeString::UnicodeString(const wchar_t *s,int n) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase((const unsigned short*)s,n); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }

class Rva0058BE30FourString {
public:
    UnicodeString m_string0,m_string4,m_string8,m_stringC;
    unsigned short m_word10;
};
struct Rva005900C0TextView {
    virtual void slot00();
    virtual void slot04(UnicodeString);
    virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3C(int *,int *);
};
struct Rva005900C0GameTextView {
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24();
    virtual UnicodeString slot28(const char *,bool *);
};
class GameTextInterface;
extern GameTextInterface *TheGameText;
class BfmeVec2EV { public: float m_bfmeXEV,m_bfmeYEV; };
class BfmeHostEV { public: void bfmeExtentsEV(BfmeVec2EV *,BfmeVec2EV *,BfmeVec2EV *); };
void bfmeGo1065C(int);
class Rva00593E60State {
public:
    unsigned char m_byte0,m_byte1,m_byte2,m_pad3;
    int m_value4;
    Rva0058BE30FourString *m_ptr8,*m_ptrC;
    int m_value10;
    Rva005900C0TextView *m_ptr14,*m_ptr18,*m_ptr1C,*m_ptr20,*m_ptr24;
    void rva005900C0(Rva0058BE30FourString *);
};
void Rva00593E60State::rva005900C0(Rva0058BE30FourString *record) {
    if(m_value4<0) return;
    UnicodeString first(record->m_string4);
    UnicodeString second(record->m_string8);
    if(first.isEmpty() && second.isNotEmpty())
        ((StringBase<unsigned short>*)&first)->swap(*(StringBase<unsigned short>*)&second);
    BfmeVec2EV extents;
    { BfmeVec2EV a,b;
    ((BfmeHostEV*)this)->bfmeExtentsEV(&a,&b,&extents); }
    int width,height,firstHeight,hotkeyHeight;
    m_ptr14->slot04(record->m_string0);
    m_ptr14->slot3C(&width,&height);
    float total=(float)height;
    m_ptr18->slot04(first);
    m_ptr18->slot3C(&width,&firstHeight);
    float firstSize=(float)firstHeight;
    if(first.isNotEmpty() && extents.m_bfmeYEV>firstSize) firstSize=extents.m_bfmeYEV;
    UnicodeString hotkey;
    if(record->m_word10) {
        UnicodeString letter((const wchar_t*)&record->m_word10,1);
        hotkey.format(((Rva005900C0GameTextView*)TheGameText)->slot28("TOOLTIP:Shortcut",0),letter.str());
    }
    m_ptr20->slot04(hotkey);
    m_ptr20->slot3C(&width,&hotkeyHeight);
    float hotkeySize=(float)hotkeyHeight;
    if(record->m_word10) {
        if(first.isNotEmpty() && firstSize>hotkeySize) hotkeySize=firstSize;
    } else hotkeySize=firstSize;
    total+=hotkeySize;
    m_ptr1C->slot04(second);
    if(second.isNotEmpty()) {
        m_ptr1C->slot3C(&width,&height);
        float secondSize=(float)height;
        if(extents.m_bfmeYEV>secondSize) secondSize=extents.m_bfmeYEV;
        total+=secondSize;
    }
    m_ptr24->slot04(record->m_stringC.isEmpty()?UnicodeString(L" "):record->m_stringC);
    m_ptr24->slot3C(&width,&height);
    bfmeGo1065C((int)(total+(float)height));
    m_byte0=1;
}
