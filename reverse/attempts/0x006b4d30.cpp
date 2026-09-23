// ?xfer@MilesAudioManager@@UAEXPAVXfer@@@Z
// partial score=0.457437661221 date=2026-09-23
// cl: /O2 /Ob1 /I. /ICode/Libraries/Source/WWVegas/WWLib /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
// MilesAudioManager::xfer at RVA 006B4D30, secondary interface this = complete +8.
// Witness: 006B0E30/36 installs 0111C0C0/0111C0AC; secondary slot 2
// -> ILT 000306D4 -> 00696360 -> literal MilesAudioManager; slot 3
// -> ILT 00003080 -> this body. End: ret 4 at 006B5643, int3 006B5646.
// Reconstruction extends the original stash. Offsets are interface-relative.
#include <vector>
#include <list>
#include <deque>
#include "Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "reference/shims/stringbaseunicode/Common/UnicodeString.h"
inline AsciiString::~AsciiString(){((StringBase<char>*)this)->releaseBuffer();}
inline UnicodeString::~UnicodeString(){((StringBase<wchar_t>*)this)->releaseBuffer();}
class Xfer;
struct Rva006B4D30Version;
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);



class Rva006B4D30XferArg
{
public:
	virtual void slot00();
	virtual unsigned char slot01();
	virtual void slot02();
	virtual unsigned char slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Rva006B4D30XferArg& slot10(Rva006B4D30Version& value);
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
	virtual Rva006B4D30XferArg& slot27(float& value);
	virtual void slot28();
	virtual Rva006B4D30XferArg& slot29(unsigned int& value);
	virtual Rva006B4D30XferArg& slot30(int& value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual Rva006B4D30XferArg& slot35(unsigned char& value);
	virtual Rva006B4D30XferArg& slot36(const char *name, void *value, int size);
};

class Rva006B4D30MutexGuard
{
public:
	Rva006B4D30MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006B4D30MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};


struct Rva006B4D30Version { unsigned char first, second; };
struct Rva006B4D30Info { char pad00[0x84]; int m_84; };
struct Rva006B4D30Event {
    char pad00[8]; Rva006B4D30Info *m_08;
    char pad0c[0x28-0xc]; int m_28;
    char pad2c[0x49-0x2c]; unsigned char m_49;
};
class Rva006B4D30Ref {
public:
    virtual ~Rva006B4D30Ref();
    long m_04;
    char pad08[0xc]; Rva006B4D30Event *m_14;
    char pad18[0x34-0x18]; unsigned char m_34;
};
struct Rva006B4D30Ptr {
    Rva006B4D30Ref *value;
    Rva006B4D30Ptr():value(0) {}
    Rva006B4D30Ptr(const Rva006B4D30Ptr &rhs):value(rhs.value) {
        if(value) InterlockedIncrement(&value->m_04);
    }
    ~Rva006B4D30Ptr() {
        Rva006B4D30Ref* saved=value;
        if(saved && InterlockedDecrement(&saved->m_04)<=0) delete saved;
    }
};
struct Rva006B4D30Pair { int first; float second; };
struct Rva006B4D30Group { char pad00[0xc]; int m_0c; };
struct Rva006B4D30GroupPair { Rva006B4D30Group *first; float second; };
class Rva006ABC60 {
public: void xfer(Xfer*); char m_bytes[0x1c4];
};
class Rva006AEF20 {
public:
    void invoke(Rva006B4D30XferArg*, Rva006B4D30Ptr*, Rva006B4D30Version*);
    void rva006B2D80();
    void rva00695AB0(int);
};
Xfer* xferTree(Xfer*,void*);
Xfer* xferUnicodeStringVector(Xfer*,std::vector<UnicodeString>*);
Xfer* xferAsciiStringVector(Xfer*,std::vector<AsciiString>*);
typedef UnicodeString Rva006B4D30Wide;
typedef AsciiString Rva006B4D30Narrow;
typedef std::deque<Rva006B4D30Ptr> Rva006B4D30Deque;
typedef std::list<Rva006B4D30Ptr> Rva006B4D30List;
class MilesAudioManager {
public:
    virtual void xfer(Xfer*);
    template<class T> T& field(int offset) {return *(T*)((char*)this+offset);}
    char m_004[0x3c-4]; int m_03c; unsigned int m_040;
    char m_044[0xb0-0x44]; Rva006ABC60 m_0b0[3];
    int m_5fc; char m_600[0x14]; int m_614;
    char m_618[0x11]; unsigned char m_629;
    char m_62a; unsigned char m_62b; char m_62c[2];
    unsigned char m_62e,m_62f; int m_630; int m_634[3];
    char m_640[0x954-0x640]; void* m_mutex;
    char m_958[0x20]; std::vector<Rva006B4D30Wide> m_978;
    std::vector<Rva006B4D30Narrow> m_984;
    struct Tree { char data[12]; }; Tree m_990[3];
    char m_9b4[0x14]; Rva006B4D30List m_9c8;
    Rva006B4D30Deque m_9cc[3][2]; int m_abc[3];
    Rva006B4D30Ref* m_ac8[3];
    std::vector<Rva006B4D30GroupPair> m_ad4;
    std::vector<Rva006B4D30Pair> m_ae0;
    char m_aec[0x60]; int m_b4c; char m_b50[0x18]; unsigned char m_b68;
};
void MilesAudioManager::xfer(Xfer* argument)
{
    Rva006B4D30XferArg *xfer=(Rva006B4D30XferArg*)argument;
    if(xfer->slot03()) return;
    void *handle=m_mutex;
    Rva006B4D30MutexGuard guard(handle);
    if(xfer->slot01()) {
        m_62f=1;
        m_630=0;
    }
    Rva006B4D30Version version;
    version.first=1;version.second=4;
    xfer->slot10(version);
    int previous=m_5fc;
    xfer->slot36("AudioViewType",&m_5fc,4);
    if(previous!=m_5fc) m_629=1;
    xfer->slot36("AudioViewTypeBits",&m_614,4);
    xfer->slot35(m_62b);
    int i;
    for(i=0;i<3;++i) {
        if(i==2 && version.second>=3 && !m_b68) continue;
        xfer->slot36("MusicSystem",&m_abc[i],4);
        m_0b0[i].xfer(argument);
        xferTree(argument,&m_990[i]);
        if(version.second>=4) xfer->slot36("AudioAffect",&m_634[i],4);
    }
    if(xfer->slot01()) {
        std::vector<Rva006B4D30Pair>& pairs=m_ae0;
        pairs.erase(pairs.begin(),pairs.end());
        int count;
        xfer->slot30(count);
        while(count) {
            Rva006B4D30Pair pair;
            xfer->slot30(pair.first);
            xfer->slot27(pair.second);
            pairs.push_back(pair);
            --count;
        }
        m_62e=1;
    } else {
        std::vector<Rva006B4D30GroupPair>& groups=m_ad4;
        int count=groups.size();
        xfer->slot30(count);
        for(std::vector<Rva006B4D30GroupPair>::iterator it=groups.begin();it!=groups.end();++it) {
            int id=it->first->m_0c;
            xfer->slot30(id);
            float value=it->second;
            xfer->slot27(value);
        }
    }
    xfer->slot30(m_b4c);
    if(xfer->slot01()) field<Rva006AEF20>(-8).rva00695AB0(m_b4c);
    if(version.second>=2) xfer->slot29(m_040);
    else m_040=~0u;
    m_03c=0;
    if(xfer->slot01()) {
        int count;
        xfer->slot30(count);
        for(i=0;i<count;++i) {
            Rva006B4D30Ptr value;
            field<Rva006AEF20>(-8).invoke(xfer,&value,&version);
            field<Rva006AEF20>(-8).rva006B2D80();
        }
        for(i=0;i<3;++i) {
            if(i==2 && version.second>=3 && !m_b68) continue;
            for(int j=0;j<2;++j) {
                Rva006B4D30Deque& queue=m_9cc[i][j];
                int oldSize=queue.size();
                int count;
                xfer->slot30(count);
                for(int k=0;k<count;++k) {
                    Rva006B4D30Ptr value;
                    field<Rva006AEF20>(-8).invoke(xfer,&value,&version);
                    if(value.value && queue.size()==oldSize) queue.push_back(value);
                    oldSize=queue.size();
                }
            }
        }
        for(i=0;i<3;++i) {
            if(i==2 && version.second>=3 && !m_b68) continue;
            Rva006B4D30Ref* value=m_ac8[i];
            if(value) {
                if(InterlockedDecrement(&value->m_04)<=0) delete value;
                m_ac8[i]=0;
            }
        }
        std::vector<Rva006B4D30Wide>& wide=m_978;
        wide.erase(wide.begin(),wide.end());
        std::vector<Rva006B4D30Narrow>& narrow=m_984;
        narrow.erase(narrow.begin(),narrow.end());
    } else {
        Rva006B4D30List selected;
        Rva006B4D30List& source=m_9c8;
        for(Rva006B4D30List::iterator it=source.begin();it!=source.end();++it) {
            Rva006B4D30Ref* value=it->value;
            if(value && value->m_14 &&
               (value->m_14->m_08->m_84==0 || value->m_14->m_08->m_84==1) &&
               (value->m_14->m_28!=2 || m_b68) &&
               !value->m_34 && !value->m_14->m_49) selected.push_back(*it);
        }
        int count=selected.size();
        xfer->slot30(count);
        for(Rva006B4D30List::iterator it=selected.begin();it!=selected.end();++it)
            field<Rva006AEF20>(-8).invoke(xfer,&*it,&version);
        for(i=0;i<3;++i) {
            if(i==2 && version.second>=3 && !m_b68) continue;
            for(int j=0;j<2;++j) {
                Rva006B4D30Deque& queue=m_9cc[i][j];
                int count=queue.size();
                xfer->slot30(count);
                for(Rva006B4D30Deque::iterator it=queue.begin();it!=queue.end();++it) {
                    Rva006B4D30Ptr value=*it;
                    field<Rva006AEF20>(-8).invoke(xfer,&value,&version);
                }
            }
        }
    }
    xferUnicodeStringVector(argument,&m_978);
    xferAsciiStringVector(argument,&m_984);
}
