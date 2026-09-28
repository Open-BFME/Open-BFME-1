// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// HordeContain constructor: retail RVA 0x0023EAF0, 819 bytes through ret 8.
// Identity: clean friend_newModuleInstance allocates 0x224 bytes and calls this
// constructor; the installed vtables also occur in HordeContainDestructors.cpp.
// Reuse that destructor's eleven-interface layout and eight STLport members.
// TransportContain's constructor is reached through retail ILT RVA 0x000023A1.
// No HordeContain twin exists in the vendored Zero Hour tree.
//
// The address-named aggregates describe observed initialization regions, not
// recovered source type identities. The three ten-word regions use memset.
// Grouping the +0x1E4..+0x210 initialization preserves retail's deferred stack
// cleanup at +0x2FD. No additional lifetime or exception cleanup is introduced.
// name_oracle reports no witnessed HordeContain member layout. Offset names
// remain opaque; m_damagePercent comes from HordeContainCreatePayload.cpp.

class Thing;
class ModuleData;

#include <string.h>
#include <list>
#include <map>
#include <set>
#include <vector>

// payload spellings from game/gen_small/tgrid_*.cpp
struct Gen_t_000ef440_k4 { int a[1]; Gen_t_000ef440_k4(); Gen_t_000ef440_k4(const Gen_t_000ef440_k4&); ~Gen_t_000ef440_k4(); Gen_t_000ef440_k4& operator=(const Gen_t_000ef440_k4&); };
bool operator==(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
bool operator<(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
struct Gen_t_00223550_p4pod { int a[1]; };
bool operator==(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
bool operator<(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
struct Gen_t_0023abb0_p16cd { int a[4]; Gen_t_0023abb0_p16cd(); Gen_t_0023abb0_p16cd(const Gen_t_0023abb0_p16cd&); ~Gen_t_0023abb0_p16cd(); Gen_t_0023abb0_p16cd& operator=(const Gen_t_0023abb0_p16cd&); };
bool operator==(const Gen_t_0023abb0_p16cd&, const Gen_t_0023abb0_p16cd&);
bool operator<(const Gen_t_0023abb0_p16cd&, const Gen_t_0023abb0_p16cd&);

// vector elements: trivially destructible, so only their size reaches the bytes
struct Gen_p16pod { int a[4]; };
struct Gen_p28pod { int a[7]; };

class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase() {}

private:
	unsigned char m_pad[8];
};

template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual ~OpenContainSecondaryBase() {}
};

class OpenContainWideSecondaryBase
{
public:
	virtual ~OpenContainWideSecondaryBase() {}

private:
	unsigned char m_pad[12];
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public:
	virtual ~OpenContain() {}

private:
	unsigned char m_pad[0x9c];					///< out to sizeof() == 0xD4
};

class SiegeEngineContainTenthBase
{
public:
	virtual ~SiegeEngineContainTenthBase() {}
};

class __declspec(novtable) TransportContain
	: public OpenContain,
	  public SiegeEngineContainTenthBase		///< vptr at 0xD4
{
public:
	TransportContain(Thing *, const ModuleData *);
	virtual ~TransportContain();

private:
	unsigned char m_pad[0x0c];					///< out to sizeof() == 0xE4
};

// This interface costs a vptr write but introduces no unwind state.
class HordeContainEleventhBase
{
public:
	virtual void slot();
};

struct Rva0023EAF0TenWords
{
 unsigned int words[10];
 Rva0023EAF0TenWords() { memset(words, 0, sizeof(words)); }
};

struct Rva0023EAF0Tail
{
 unsigned int m_1e4, m_1e8, m_1ec;
 bool m_1f0;
 int m_1f4;
 unsigned int m_1f8;
 bool m_1fc, m_1fd, m_1fe;
 int m_damagePercent;
 bool m_204, m_205;
 unsigned int m_208, m_20c;
 bool m_210;
 Rva0023EAF0Tail() : m_1e4(0), m_1e8(0), m_1ec(0), m_1f0(false), m_1f4(-1), m_1f8(0),
 m_1fc(false), m_1fd(false), m_1fe(false), m_damagePercent(100),
 m_204(false), m_205(false), m_208(0), m_20c(0), m_210(false) {}
};

typedef char Rva0023EAF0TenWordsSize[(sizeof(Rva0023EAF0TenWords) == 0x28) ? 1 : -1];
typedef char Rva0023EAF0TailSize[(sizeof(Rva0023EAF0Tail) == 0x30) ? 1 : -1];

class HordeContain
	: public TransportContain,
	  public HordeContainEleventhBase			///< vptr at 0xE4
{
public:
	HordeContain(Thing *, const ModuleData *);
	virtual ~HordeContain();

private:
 bool m_e8, m_e9;
 Rva0023EAF0TenWords m_ec;
 _STL::set<Gen_t_000ef440_k4> m_set;
 _STL::map<int, Gen_t_00223550_p4pod> m_mapA;
 _STL::vector<Gen_p16pod> m_vectorA;
 _STL::list<int> m_list;
 bool m_13c;
 unsigned int m_140;
 _STL::map<int, Gen_t_0023abb0_p16cd> m_mapB;
 unsigned int m_150, m_154;
 Rva0023EAF0TenWords m_158, m_180;
 _STL::map<int, Gen_t_00223550_p4pod> m_mapC;
 unsigned int m_1b4, m_1b8, m_1bc;
 _STL::vector<int> m_vectorB;
 unsigned int m_1cc, m_1d0, m_1d4;
 _STL::vector<Gen_p28pod> m_vectorC;
 Rva0023EAF0Tail m_tail;
 unsigned int m_214, m_218, m_21c;
 bool m_220, m_221;
};

typedef char HordeContainSize[(sizeof(HordeContain) == 0x224) ? 1 : -1];

HordeContain::HordeContain(Thing *thing, const ModuleData *moduleData)
 : TransportContain(thing, moduleData),
 m_e8(false), m_e9(false), 
 m_13c(false), m_140(0), m_150(0), m_154(0),
 m_1b4(0), m_1b8(0), m_1bc(0), m_1cc(0), m_1d0(0), m_1d4(0),
 m_214(0), m_218(0), m_21c(0), m_220(false), m_221(false)
{
}
