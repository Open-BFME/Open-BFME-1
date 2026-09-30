// ?d_006171d0@@YAXXZ
// partial score=0.5694 date=2026-09-30
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport


// Retail RVA 0x006171D0, 576 bytes. The constructor establishes a
// SubsystemInterface primary base and the shared BfmeBaseVUQ secondary base,
// then initializes the manager's observed container offsets. The most-derived
// owner and its method names remain address-derived: neither vtable has a
// witnessed owner name, and the sole caller is an anonymous thunk.
// Evidence checkpoint: t=20min model=strong-mid5.

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>
#include <map>
#include <vector>

class SubsystemInterface
{
public:
    SubsystemInterface();
    virtual ~SubsystemInterface();

private:
    unsigned int m_name;
};

class BfmeBaseVUQ
{
public:
    virtual ~BfmeBaseVUQ() { }
};

// This member is only constructed here. Its verified 0x188-byte size and
// external constructor are sufficient for the owner's observed layout.
class BfmeCloudSetEQ
{
public:
    BfmeCloudSetEQ();

private:
    unsigned char m_layout[0x188];
};

class Rva0061C1D0Object;
class Rva00615D50Object;
class BfmeItemAM;
class BfmeLivingWorldMapObject;

struct Gen_t_00616f40_p12cd
{
    int a[3];
    Gen_t_00616f40_p12cd();
    Gen_t_00616f40_p12cd(const Gen_t_00616f40_p12cd &);
    ~Gen_t_00616f40_p12cd();
    Gen_t_00616f40_p12cd &operator=(const Gen_t_00616f40_p12cd &);
};
bool operator==(const Gen_t_00616f40_p12cd &, const Gen_t_00616f40_p12cd &);
bool operator<(const Gen_t_00616f40_p12cd &, const Gen_t_00616f40_p12cd &);

// Retail clears the just-constructed five-element array through this generated
// helper specialization. The maps are empty at this point, so its value type is
// not observed; the 0x14-byte hashtable header is the shared ABI view.
struct Gen_t_00614450_m4cd
{
    int a[1];
    Gen_t_00614450_m4cd();
    Gen_t_00614450_m4cd(const Gen_t_00614450_m4cd &);
    ~Gen_t_00614450_m4cd();
    Gen_t_00614450_m4cd &operator=(const Gen_t_00614450_m4cd &);
};
bool operator==(const Gen_t_00614450_m4cd &, const Gen_t_00614450_m4cd &);
bool operator<(const Gen_t_00614450_m4cd &, const Gen_t_00614450_m4cd &);

class Rva006171D0Owner
    : public SubsystemInterface,
      public BfmeBaseVUQ
{
public:
    Rva006171D0Owner();
    virtual ~Rva006171D0Owner() = 0;

private:
    typedef _STL::hash_map<AsciiString, Rva0061C1D0Object *,
        rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Map194;
    typedef _STL::hash_map<int, Gen_t_00616f40_p12cd> ArrayMap;
    typedef _STL::hash_map<int, BfmeItemAM *> Map210;
    typedef _STL::hash_map<AsciiString, Rva00615D50Object *,
        rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Map224;
    typedef _STL::map<int, BfmeLivingWorldMapObject *> TreeMap;
    typedef _STL::hash_map<int, Gen_t_00614450_m4cd> ArrayClearView;

    BfmeCloudSetEQ m_cloud;
    Map194 m_map194;
    void *m_field1a8;
    ArrayMap m_array1ac[5];
    Map210 m_map210;
    Map224 m_map224;
    unsigned int m_field238;
    unsigned int m_field23c;
    _STL::vector<void *> m_vector240;
    _STL::vector<void *> m_vector24c;
    _STL::vector<void *> m_vector258;
    _STL::vector<void *> m_vector264;
    _STL::vector<void *> m_vector270;
    TreeMap m_tree27c;
    unsigned char m_field288;
    unsigned char m_pad289[3];
    void *m_field28c;
    int m_field290;
    unsigned char m_field294;
    unsigned char m_field295;
    unsigned char m_pad296[2];
    _STL::vector<void *> m_vector298;
};

Rva006171D0Owner::Rva006171D0Owner()
    : m_map194(100),
      m_field1a8(0),
      m_map210(100),
      m_map224(100),
      m_field238(0),
      m_field288(0),
      m_field28c(0),
      m_field290(60),
      m_field294(1),
      m_field295(0)
{
    m_field23c = 0;
    m_tree27c.clear();

    for (unsigned int i = 0; i < 5; ++i)
    {
        reinterpret_cast<ArrayClearView *>(&m_array1ac[i])->clear();
    }
    m_map210.clear();
    m_vector298 = m_vector298;
}
