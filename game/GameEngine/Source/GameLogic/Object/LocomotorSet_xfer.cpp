// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <map>
#include "ascii_string.h"
template <> inline StringBase<char>::~StringBase() { releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
struct LocomotorVersion001BAAA0 { unsigned char version,current; unsigned char padding[2]; };
struct LocomotorError001BAAA0 { char *text; int tag; };
extern "C" LocomotorError001BAAA0 *__cdecl bfmeFormatText(LocomotorError001BAAA0*,int,const char*,...);
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
	virtual Xfer &xferVersion(LocomotorVersion001BAAA0 &);
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
	virtual void slot24();
	virtual void slot25();
	virtual Xfer &xferAsciiString(AsciiString &);
	virtual void slot27();
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(unsigned int &);
	virtual Xfer &xferInt(int &);
	virtual Xfer &xferUnsignedShort(unsigned short &);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Xfer &xferBool(bool &);
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Locomotor;
class LocomotorTemplate;
class Rva001B6070Owner { public: AsciiString getResolvedValue() const; };
class LocomotorStore {
public:
    Locomotor *newLocomotor(const LocomotorTemplate*) const;
    const LocomotorTemplate *findLocomotorTemplate(NameKeyType key) const {
        if (key == NAMEKEY_INVALID) return 0;
        TemplateMap::const_iterator it=m_locomotorTemplates.find(key);
        if (it == m_locomotorTemplates.end()) return 0;
        return it->second;
    }
private:
    typedef _STL::map<NameKeyType,LocomotorTemplate*,_STL::less<NameKeyType> > TemplateMap;
    char m_before08[8];
    TemplateMap m_locomotorTemplates;
};
extern LocomotorStore *TheLocomotorStore;
class LocomotorSet {
    _STL::vector<Locomotor*> m_locomotors;
    int m_validLocomotorSurfaces;
    bool m_downhillOnly;
protected:
    virtual void xfer(Xfer*);
};
void LocomotorSet::xfer(Xfer *xfer) {
    if (xfer->IsLightCRC()) return;
    {
    LocomotorVersion001BAAA0 version;
    version.version=1; version.current=1;
    xfer->xferVersion(version);
    }
    unsigned short count=(unsigned short)m_locomotors.size();
    xfer->xferUnsignedShort(count);
    if (xfer->IsStoring()) {
        for (_STL::vector<Locomotor*>::iterator it=m_locomotors.begin();it!=m_locomotors.end();++it) {
            Locomotor *loco=*it;
            AsciiString name=((Rva001B6070Owner*)loco)->getResolvedValue();
            xfer->xferAsciiString(name);
            xfer->xferSnapshot(loco);
        }
    } else {
        if (!m_locomotors.empty()) {
            LocomotorError001BAAA0 error;
            bfmeFormatText(&error,4,0);
            _CxxThrowException(&error,&g_rva005c5100ThrowInfo);
        }
        for (unsigned short i=0;i<count;++i) {
            AsciiString name;
            xfer->xferAsciiString(name);
            const LocomotorTemplate *lt=TheLocomotorStore->findLocomotorTemplate(TheNameKeyGenerator->nameToKey(name.str()));
            if (!lt) {
                LocomotorError001BAAA0 error;
                bfmeFormatText(&error,5,0);
                _CxxThrowException(&error,&g_rva005c5100ThrowInfo);
            }
            Locomotor *loco=TheLocomotorStore->newLocomotor(lt);
            xfer->xferSnapshot(loco);
            m_locomotors.push_back(loco);
        }
    }
    xfer->xferInt(m_validLocomotorSurfaces);
    xfer->xferBool(m_downhillOnly);
}
