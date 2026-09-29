// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: LargeGroupAudioUpdateModuleData default constructor, retail
// 0x002971F0, 142 bytes.
//
// IDENTITY.  The class name is carried by the matched copy constructor at
// 0x002972B0, the matched destructor at 0x00297390 and the matched
// scalar-deleting destructor at 0x00297410, and by the vtable this body
// installs, 0x010BFA60, which those three and nothing else writes.  The single
// caller, ?friend_newModuleData@LargeGroupAudioUpdate@@SAPAVModuleData
// (0x0011C280, which reaches this body through ILT 0x0001A98D), constructs it
// as a ModuleData.
//
// LAYOUT, from the matched copy constructor: the base's only stored state is
// +0x04, the key map sits at +0x08 and the three trailing scalars at +0x14,
// +0x18 and +0x1C (a dword, a dword and a word).
//
// The +0x14 scalar is ceil() of the double constant at .rdata 0x010BFA50
// (2.4999999441206455), passed through the MSVCR71.dll ceil import at
// 0x01359394 and truncated by __ftol2.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

// This pinned IAT slot is MSVCR71.dll!ceil (0x01359394).
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap();
	LargeGroupAudioKeyMap(const LargeGroupAudioKeyMap &other);
	~LargeGroupAudioKeyMap();

private:
	void *m_wordsBegin;
	void *m_wordsEnd;
	void *m_wordsCapacity;
};

class LargeGroupAudioUpdateModuleDataBase
{
public:
	virtual ~LargeGroupAudioUpdateModuleDataBase() {}

private:
	unsigned int m_baseValue;
};

struct Rva00296ED0Target;
typedef Rva00296ED0Target *Rva00296ED0Key;
typedef _STL::_Rb_tree<Rva00296ED0Key, Rva00296ED0Key,
	_STL::_Identity<Rva00296ED0Key>, _STL::less<Rva00296ED0Key>,
	_STL::allocator<Rva00296ED0Key> > Rva00296ED0Tree;

class LGA_Global;
extern LGA_Global g_lgaGlobal;

class LargeGroupAudioUpdateModuleData : public LargeGroupAudioUpdateModuleDataBase
{
public:
	LargeGroupAudioUpdateModuleData();

private:
	LargeGroupAudioKeyMap m_keys;
	int m_b;
	int m_a;
	unsigned short m_enabled;
};

// ??0LargeGroupAudioUpdateModuleData@@QAE@XZ
LargeGroupAudioUpdateModuleData::LargeGroupAudioUpdateModuleData() :
	m_keys(),
	m_b((int)ceil(2.4999999441206455)),
	m_a(1),
	m_enabled(1)
{
	((Rva00296ED0Tree *)&g_lgaGlobal)->insert_unique((Rva00296ED0Key)this);
}
