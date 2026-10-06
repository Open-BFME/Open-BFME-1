// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: behavior-derived key-map retain helper, retail 0x003D3770,
// 83 bytes. It visits the global key-record tree and increments the use count
// for every registered key whose bit is present in the supplied map.

namespace _STL
{

struct _Rb_tree_node_base
{
	bool m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class Dummy>
class _Rb_global
{
public:
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

}

struct LargeGroupAudioKeyRecord : public _STL::_Rb_tree_node_base
{
	unsigned int m_bfmeUnmodelled10;
	unsigned int m_key;
	unsigned int m_useCount;
};

class LargeGroupAudioKeyMap
{
public:
	unsigned int *m_wordsBegin;
	unsigned int *m_wordsEnd;
	unsigned int *m_wordsCapacity;
};

// The key-record tree at VA 012F1050 is defined (and constructed by $E
// initializer 0x00C6B390) in Rva00C6B390StaticInitializers.cpp; its first
// word is the header node this TU walks from.
struct Rva00C6B390Init;
extern Rva00C6B390Init g_rva012F1050;
#define g_lgaKeyRecordSentinel (*reinterpret_cast<LargeGroupAudioKeyRecord **>(&g_rva012F1050))

// ?bfmeRetainMembers@@YAXPAVLargeGroupAudioKeyMap@@@Z
void bfmeRetainMembers(LargeGroupAudioKeyMap *map)
{
	LargeGroupAudioKeyRecord *record =
		(LargeGroupAudioKeyRecord *)g_lgaKeyRecordSentinel->m_left;

	while (record != g_lgaKeyRecordSentinel)
	{
		unsigned int word = record->m_key >> 5;
		unsigned int wordCount = map->m_wordsEnd - map->m_wordsBegin;

		if (wordCount > word)
		{
			unsigned int mask = 1 << (record->m_key & 0x1F);
			if (map->m_wordsBegin[word] & mask)
				++record->m_useCount;
		}

		record = (LargeGroupAudioKeyRecord *)
			_STL::_Rb_global<bool>::_M_increment(record);
	}
}
