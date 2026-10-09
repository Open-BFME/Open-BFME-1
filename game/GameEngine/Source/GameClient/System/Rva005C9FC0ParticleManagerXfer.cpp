// cl: /O2 /Ob2 /I. /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB
#include <hash_map>
// Particle-manager transfer through the Snapshot receiver at primary +8.
// Evidence: targets/game/reverse/identity_evidence/005c9fc0-particle-manager-xfer.md.
#include "ascii_string.h"
#include "xfer.h"
// ?isEmpty@?$StringBase@D@@QBE_NXZ absent-from-retail in this TU; native inline accessor.
template<> inline bool StringBase<char>::isEmpty() const { return m_data==0 || m_data->length==0; }
#include "FXParticleSystem/fx_particle_system.h"

class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();
struct Rva005C9FC0Particle;
class ParticleSystemHandle {
public:
    ParticleSystemHandle(Rva005C9FC0Particle *);
    ~ParticleSystemHandle() throw();
    Rva005C9FC0Particle *m_system;
    ParticleSystemHandle *m_previous;
    ParticleSystemHandle *m_next;
    // ??CParticleSystemHandle@@QBEPAURva005C9FC0Particle@@XZ absent-from-retail
    Rva005C9FC0Particle *operator->() const { if(!m_system) return (Rva005C9FC0Particle *)bfmeNullSystemZA(); return m_system; }
};
struct Rva005C9FC0Particle {
    char bytes00[0x98];
    ParticleSystemHandle *m_firstHandle;
    ParticleSystemHandle *m_lastHandle;
    char bytesA0[0x19c-0xa0];
    FXParticleSystem::ParticleSystemTemplate *value19c;
    char bytes1A0[8];
    bool m_isDestroyed;
    char byte1A9;
    bool m_isSaveable;
    // ?getTemplate@Rva005C9FC0Particle@@QBEPAVParticleSystemTemplate@FXParticleSystem@@XZ absent-from-retail
    FXParticleSystem::ParticleSystemTemplate *getTemplate() const { return value19c; }
    // ?isDestroyed@Rva005C9FC0Particle@@QBE_NXZ absent-from-retail
    bool isDestroyed() const { return m_isDestroyed; }
    // ?isSaveable@Rva005C9FC0Particle@@QBE_NXZ absent-from-retail
    bool isSaveable() const { return m_isSaveable; }
};
// ??0ParticleSystemHandle@@QAE@PAURva005C9FC0Particle@@@Z absent-from-retail
inline ParticleSystemHandle::ParticleSystemHandle(Rva005C9FC0Particle *system) : m_system(system) {
    if(m_system) {
        m_previous=m_system->m_lastHandle;
        m_next=0;
        m_system->m_lastHandle=this;
        if(m_previous) m_previous->m_next=this;
        else m_system->m_firstHandle=this;
    } else { m_next=0; m_previous=0; }
}
struct Rva005C9FC0ListNode {
    Rva005C9FC0ListNode *next,*previous;
    ParticleSystemHandle value;
};
class ParticleSystemTemplate;
namespace rts { template<class T> struct hash { unsigned int operator()(T value) const; }; }
typedef _STL::hash_map<AsciiString,ParticleSystemTemplate *,rts::hash<AsciiString>,_STL::equal_to<AsciiString> > Rva005C9FC0TemplateMap;
struct BfmeFormattedText { char *text; int tag; };
extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *,int,const char *,...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *,void *);
extern int g_guardTargetTypeThrowInfo;
extern "C" void __cdecl __identifier("?j_0000240a@@YAXXZ")(Xfer *,void *);
namespace FXParticleSystem { class ParticleSystemManager {
public:
    ParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *,bool);
    char bytes00[0x9c];
    Rva005C9FC0TemplateMap value9c;
}; }
// ??0Rva005C9FC0Version@@QAE@EE@Z absent-from-retail
struct Rva005C9FC0Version : Xfer::Version { Rva005C9FC0Version(unsigned char minimum,unsigned char current) { data[0]=minimum; data[1]=current; } };
class Rva005C9FC0 {
public:
    void method(Xfer &);
    char bytes00[0x74];
    int value74;
    Rva005C9FC0ListNode *value78;
    unsigned value7c;
    unsigned value80;
    unsigned value84;
    int value88;
    unsigned value8c;
    int value90;
    char value94[16];
};

// ?method@Rva005C9FC0@@QAEXAAVXfer@@@Z
void Rva005C9FC0::method(Xfer &xfer) {
    if(xfer.IsLightCRC()) return;
    Rva005C9FC0Version version(1,2);
    xfer==version;
    __identifier("?j_0000240a@@YAXXZ")(&xfer,&value74);
    unsigned systemCount=value84;
    xfer==systemCount;
    if(version.data[1]>=2) { xfer==value88; xfer==value90; }
    if(xfer.IsStoring()) {
        for(Rva005C9FC0ListNode *it=value78->next;it!=value78;it=it->next) {
            --systemCount;
            ParticleSystemHandle system(it->value.m_system);
            if(system->isDestroyed()==true || system->isSaveable()==false) {
                AsciiString mtString="";
                xfer==mtString;
                continue;
            }
            AsciiString systemName=system->getTemplate()->getName();
            xfer==systemName;
            xfer==*(Snapshot *)system.m_system;
        }
    } else {
        for(unsigned i=0;i<systemCount;++i) {
            AsciiString systemName;
            xfer==systemName;
            if(systemName.isEmpty()) continue;
            FXParticleSystem::ParticleSystemManager *manager=(FXParticleSystem::ParticleSystemManager *)((char *)this-8);
            FXParticleSystem::ParticleSystemTemplate *systemTemplate=0;
            const Rva005C9FC0TemplateMap &table=manager->value9c;
            Rva005C9FC0TemplateMap::const_iterator find=table.find(systemName);
            if(find!=table.end()) systemTemplate=(FXParticleSystem::ParticleSystemTemplate *)find->second;
            if(!systemTemplate) {
                BfmeFormattedText exception;
                bfmeFormatText(&exception,5,0);
                _CxxThrowException(&exception,&g_guardTargetTypeThrowInfo);
            }
            ParticleSystemHandle system=manager->createParticleSystem(systemTemplate,false);
            if(!system.m_system) {
                BfmeFormattedText exception;
                bfmeFormatText(&exception,5,0);
                _CxxThrowException(&exception,&g_guardTargetTypeThrowInfo);
            }
            xfer==*(Snapshot *)system.m_system;
        }
    }
}
