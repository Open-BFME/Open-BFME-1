// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// BezierProjectileBehavior ctor 0x001F1470 installs VA 0x010A253C.
// Slot 3 -> ILT 0x00041DD0 -> this snapshot body. All member offsets below
// are witnessed by the retail loads and Xfer calls; names remain address-derived.
// stlport
#include <vector>
#include "ascii_string.h"
template <> inline StringBase<char>::~StringBase() { releaseBuffer(); }
struct ProjectileVersion001F1860 { unsigned char version,current; unsigned char padding[2]; };
struct ProjectileError001F1860 { char *text; int tag; };
extern "C" ProjectileError001F1860 *__cdecl bfmeFormatText(ProjectileError001F1860*,int,const char*,...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void*,void*);
extern "C" char g_rva005c5100ThrowInfo;
class Xfer
{
public:
	virtual void slot00();
	virtual bool IsLoading();
	virtual bool IsStoring();
	virtual bool IsCRC();
	virtual bool IsLightCRC();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Xfer &xferUser(void *, unsigned int);
	virtual Xfer &xferVersion(ProjectileVersion001F1860 &);
	virtual void slot11();
	virtual void xferSnapshot(void *);
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
	virtual Xfer &xferCoord3D(void *);
	virtual void slot25();
	virtual Xfer &xferAsciiString(AsciiString &);
	virtual Xfer &xferReal(float &);
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(unsigned int &);
	virtual Xfer &xferInt(int &);
	virtual Xfer &xferUnsignedShort(unsigned short &);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Xfer &xferBool(bool &);
};

class FlagPairTarget;
class Gen002B2080 { public: void handle(FlagPairTarget*); };
class MidVirtualSlot90Receiver;
void Rva0010C3C0(MidVirtualSlot90Receiver*,void*);
class BfmeSeedTarget;
BfmeSeedTarget *bfmeHandOver_0000FFE2(BfmeSeedTarget*,void*);
struct Coord3D;
Xfer *xferCoord3DVector(Xfer*,_STL::vector<Coord3D>*);
class Rva00034045NameAccessor { public: AsciiString getName() const; };
class WeaponTemplate;
class WeaponStore { public: const WeaponTemplate *findWeaponTemplate(AsciiString) const; };
extern WeaponStore *TheWeaponStore;
extern const AsciiString Rva01336E50EmptyString;
class BezierProjectileBehavior {
    char m_before28[0x24];
    int m_at28;
    char m_at2C[12];
    int m_at38;
    const WeaponTemplate *m_at3C;
    const WeaponTemplate *m_at40;
    char m_at44[12];
    char m_at50[12];
    char m_at5C[12];
    float m_at68;
    int m_at6C;
    int m_at70;
    unsigned int m_at74;
    int m_at78;
    int m_at7C;
    bool m_at80;
    char m_pad81[3];
    float m_at84;
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
protected:
    virtual void xfer(Xfer*);
};
void BezierProjectileBehavior::xfer(Xfer *xfer) {
    ((Gen002B2080*)this)->handle((FlagPairTarget*)xfer);
    if (xfer->IsLightCRC()) return;
    ProjectileVersion001F1860 version;
    version.version=1; version.current=2;
    xfer->xferVersion(version);
    Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&m_at28);
    Rva0010C3C0((MidVirtualSlot90Receiver*)xfer,&m_at38);
    xfer->xferInt(m_at6C);
    xfer->xferReal(m_at68);
    xfer->xferCoord3D(m_at50);
    xfer->xferCoord3D(m_at5C);
    xfer->xferBool(m_at80);
    bfmeHandOver_0000FFE2((BfmeSeedTarget*)xfer,&m_at7C);
    xfer->xferCoord3D(m_at2C);
    xferCoord3DVector(xfer,(_STL::vector<Coord3D>*)m_at44);
    if (version.current>=2) xfer->xferReal(m_at84);
    AsciiString name=Rva01336E50EmptyString;
    if (m_at40) name=((const Rva00034045NameAccessor*)m_at40)->getName();
    xfer->xferAsciiString(name);
    if (xfer->IsLoading()) {
        if (((const StringBase<char>&)name).compare(Rva01336E50EmptyString)==0) m_at40=0;
        else {
            m_at40=TheWeaponStore->findWeaponTemplate(name);
            if (!m_at40) {
                ProjectileError001F1860 error;
                bfmeFormatText(&error,5,0);
                _CxxThrowException(&error,&g_rva005c5100ThrowInfo);
            }
        }
    }
    name=Rva01336E50EmptyString;
    if (m_at3C) name=((const Rva00034045NameAccessor*)m_at3C)->getName();
    xfer->xferAsciiString(name);
    if (xfer->IsLoading()) {
        if (((const StringBase<char>&)name).compare(Rva01336E50EmptyString)==0) m_at3C=0;
        else {
            m_at3C=TheWeaponStore->findWeaponTemplate(name);
            if (!m_at3C) {
                ProjectileError001F1860 error;
                bfmeFormatText(&error,5,0);
                _CxxThrowException(&error,&g_rva005c5100ThrowInfo);
            }
        }
    }
    xfer->xferInt(m_at78);
    xfer->xferInt(m_at70);
    xfer->xferUnsignedInt(m_at74);
}
