// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: RandomSoundSelectorClientBehaviorModuleData::~RandomSoundSelectorClientBehaviorModuleData,
// retail 0x0012BDD0, 107 bytes.
//
// Members destruct in reverse declared order: m_soundMap first (an out-of-line
// call to retail 0x00035B34, already pinned as thunks_025.cpp), then the
// 109-slot m_soundNames array inline (`if (slot) { slot->release(true);
// slot = 0; }` per element -- BfmeBaseVUQ destructor family shape: a small
// polymorphic pointer whose vtable slot 0 is called with argument true before
// the trivial ModuleData/BfmeBaseVUQ base restores the shared folded vtable
// at 0x01073744).
//
// See RandomSoundSelectorClientBehaviorFriendNewModuleDataThunk.cpp (the
// landed neighbour that names this class and its constructor) for the sibling
// factory function; that file's RandomSoundSelectorSoundNames/-Map are
// address-placeholders too, redeclared here with the layout this destructor's
// bytes actually prove.

// Non-virtual base whose destructor manually stamps the shared folded
// vtable-shaped constant 0x01073744 -- same technique as
// Rva000A1B30VectorHolderDestructor.cpp's Rva000A1B30Base. No entry-time
// store happens for this family member (retail has none), only this single
// tail store, so this is modelled without real C++ polymorphism.
//
// 0x01073744 is the vftable retail stores here (retail 0x0012BDD0 +0x58:
// `mov dword ptr [edi], 0x1073744`), and it is the one the BfmeBaseVUQ family
// shares -- symbols.csv/dir32_addresses.csv give `??_7BfmeBaseVUQ@@6B@,
// 0x01073744`, and Rva006BCE40Destructor.cpp emits it as a COMDAT from its
// TU-local BfmeBaseVUQ. Reference the defining mangled name rather than a
// local placeholder.
extern "C" int __identifier("??_7BfmeBaseVUQ@@6B@")[];

class ModuleDataBase0012BDD0
{
public:
	~ModuleDataBase0012BDD0() { m_table = __identifier("??_7BfmeBaseVUQ@@6B@"); }
	void *m_table;
	unsigned int m_baseField;
};

class RandomSoundSelectorSoundNamesEntry
{
public:
	virtual void release(bool now) = 0;                        ///< vtable +0x00
};

class RandomSoundSelectorSoundNames
{
public:
	~RandomSoundSelectorSoundNames()
	{
		for (int i = 0; i < 109; ++i)
		{
			RandomSoundSelectorSoundNamesEntry *entry = m_values[i];
			if (entry != 0)
			{
				entry->release(true);
				m_values[i] = 0;
			}
		}
	}

private:
	RandomSoundSelectorSoundNamesEntry *m_values[109];
};

// The sound map's out-of-line destructor is reached through ILT 0x00035B34 ->
// 0x00129B20, the matched STLport tree destructor of a map<unsigned int,
// Open2State129B20 *> (Rva00129B20MapOwnerDtor.cpp). The tree type is
// declared here only to name that destructor; its 12 bytes are the header
// node pointer, the node count and the (empty, padded) comparator.
struct Open2State129B20;
namespace _STL
{
	template <class _T1, class _T2> struct pair;
	template <class _Pair> struct _Select1st;
	template <class _Tp> struct less;
	template <class _Tp> class allocator;

	template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
	class _Rb_tree
	{
	public:
		~_Rb_tree();

	private:
		void *_M_header;
		unsigned int _M_node_count;
		unsigned int _M_key_compare;
	};
}

typedef _STL::pair<const unsigned int, Open2State129B20 *> RandomSoundSelectorMapValue;
typedef _STL::_Rb_tree<unsigned int, RandomSoundSelectorMapValue,
	_STL::_Select1st<RandomSoundSelectorMapValue>, _STL::less<unsigned int>,
	_STL::allocator<RandomSoundSelectorMapValue> > RandomSoundSelectorMap;

class RandomSoundSelectorClientBehaviorModuleData : public ModuleDataBase0012BDD0
{
public:
	~RandomSoundSelectorClientBehaviorModuleData();

private:
	RandomSoundSelectorSoundNames m_soundNames;
	RandomSoundSelectorMap m_soundMap;
	float m_defaultVolume;
	unsigned int m_selectionIndex;
	bool m_shuffle;
	bool m_enabled;
	unsigned char m_pad[2];
};

// @??1RandomSoundSelectorClientBehaviorModuleData@@UAE@XZ 0x0012BDD0
RandomSoundSelectorClientBehaviorModuleData::~RandomSoundSelectorClientBehaviorModuleData()
{
}
