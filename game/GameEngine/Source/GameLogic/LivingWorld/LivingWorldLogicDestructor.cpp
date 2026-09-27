// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include <list>
#include "ascii_string.h"
typedef bool Bool;
#include "GameEngine/Source/Common/System/subsystem_interface.h"
#include "GameEngine/Source/Common/System/snapshot.h"
extern "C" __declspec(dllimport) void __cdecl free(void *);
class Rva003C1A50 { public: void clearTwoVec(); void clearSingleton(); void clearOwned(); };
class LivingWorldRegionManager { public: virtual ~LivingWorldRegionManager(); };
class Gen_uw_0002a081 { public: ~Gen_uw_0002a081(); char m_00[12]; };
struct Gen_t_003c0c70_p12cd { char m_00[12]; ~Gen_t_003c0c70_p12cd(); };
class LivingWorldLogic : public SubsystemInterface, public Snapshot {
public:
    virtual ~LivingWorldLogic();
    virtual void init(); virtual bool loadIniFilesFromLegend();
    virtual void reset(); virtual void update(); virtual void draw();
    virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
    std::vector<void*> m_0C;
    char m_18[0x10]; LivingWorldRegionManager *m_28;
    char m_2C[4]; AsciiString m_30; int m_34;
    std::vector<void*> m_38;
    char m_44[0xc]; std::vector<void*> m_50,m_5C;
    Gen_uw_0002a081 m_68;
    char m_74[0x10]; std::vector<unsigned short> m_84;
    char m_90[4]; std::vector<void*> m_94;
    char m_A0[0x20]; std::list<Gen_t_003c0c70_p12cd> m_C0;
    char m_C4[0x10]; void *m_D4; int m_D8;
};
LivingWorldLogic::~LivingWorldLogic() {
    ((Rva003C1A50*)this)->clearTwoVec();
    ((Rva003C1A50*)this)->clearSingleton();
    ((Rva003C1A50*)this)->clearOwned();
    delete m_28;
    m_28=0;
    free(m_D4);
    m_D4=0;
    m_D8=0;
}
