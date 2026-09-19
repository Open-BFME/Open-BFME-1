// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class LargeGroupAudioUpdateModuleDataBase
{
public:
	virtual ~LargeGroupAudioUpdateModuleDataBase() {}

private:
	unsigned int m_baseValue;
};

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap(const LargeGroupAudioKeyMap &other);
	~LargeGroupAudioKeyMap();

private:
	void *m_wordsBegin;
	void *m_wordsEnd;
	void *m_wordsCapacity;
};

struct Rva00296ED0Target;
typedef Rva00296ED0Target *Rva00296ED0Key;
typedef _STL::_Rb_tree<Rva00296ED0Key, Rva00296ED0Key,
	_STL::_Identity<Rva00296ED0Key>, _STL::less<Rva00296ED0Key>,
	_STL::allocator<Rva00296ED0Key> > Rva00296ED0Tree;

class LargeGroupAudioUpdateModuleData : public LargeGroupAudioUpdateModuleDataBase
{
public:
	LargeGroupAudioUpdateModuleData(const LargeGroupAudioUpdateModuleData &other);

private:
	LargeGroupAudioKeyMap m_keys;
	int m_b;
	int m_a;
	unsigned short m_enabled;
};

// ??0LargeGroupAudioUpdateModuleData@@QAE@ABV0@@Z
LargeGroupAudioUpdateModuleData::LargeGroupAudioUpdateModuleData(
	const LargeGroupAudioUpdateModuleData &other) :
	LargeGroupAudioUpdateModuleDataBase(other),
	m_keys(other.m_keys),
	m_b(other.m_b),
	m_a(other.m_a),
	m_enabled(other.m_enabled)
{
	((Rva00296ED0Tree *)0x012EFFA0)->insert_unique((Rva00296ED0Key)this);
}
