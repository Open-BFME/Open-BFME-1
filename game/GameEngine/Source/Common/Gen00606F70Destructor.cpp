// cl: /DNDEBUG /MD /EHsc
//
// Gen00606F70::~Gen00606F70 at retail 0x00606F70.
// The seven range-loop callers use this same 0x1F0-byte element layout. The
// destructor evidence fixes the 109 pointer slots at +0x28 and the
// RandomSoundSelectorMap member at +0x1DC.

class Gen00606F70Entry
{
public:
	virtual void release(bool now);
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

class Gen00606F70SoundNames
{
public:
	~Gen00606F70SoundNames()
	{
		for (int i = 0; i < 109; ++i)
		{
			Gen00606F70Entry *entry = m_entries[ i ];
			if (entry != 0)
			{
				entry->release( true );
				m_entries[ i ] = 0;
			}
		}
	}

private:
	Gen00606F70Entry *m_entries[ 109 ];
};

class Gen00606F70
{
public:
	~Gen00606F70();

private:
	unsigned char m_prefix[ 0x28 ];
	Gen00606F70SoundNames m_soundNames;
	RandomSoundSelectorMap m_soundMap;
	unsigned char m_tail[ 0x08 ];
};

// ??1Gen00606F70@@QAE@XZ
Gen00606F70::~Gen00606F70()
{
}
