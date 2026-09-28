// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: the key-map merge used by the collectors, retail 0x003D4580,
// 135 bytes. The method name is behavior-derived. Both collectors call it
// through ILT 0x00001A14 with another three-dword map.

namespace _STL
{

template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:
	void resize(unsigned int count, Type value);

protected:
	Type *m_wordsBegin;
	Type *m_wordsEnd;
	Type *m_wordsCapacity;
};

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
	unsigned int m_key;					// +0x14
	unsigned int m_useCount;				// +0x18
};

extern LargeGroupAudioKeyRecord *g_lgaKeyRecordSentinel;

class LargeGroupAudioKeyMap :
	public _STL::vector<void *, _STL::allocator<void *> >
{
public:
	void bfmeMerge(const LargeGroupAudioKeyMap &other);
};

// ?bfmeMerge@LargeGroupAudioKeyMap@@QAEXABV1@@Z
void LargeGroupAudioKeyMap::bfmeMerge(const LargeGroupAudioKeyMap &other)
{
	unsigned int otherWords = other.m_wordsEnd - other.m_wordsBegin;
	unsigned int thisWords = m_wordsEnd - m_wordsBegin;

	if (thisWords < otherWords)
		resize(otherWords, 0);

	LargeGroupAudioKeyRecord *sentinel = g_lgaKeyRecordSentinel;
	LargeGroupAudioKeyRecord *record =
		(LargeGroupAudioKeyRecord *)sentinel->m_left;

	while (record != sentinel)
	{
		unsigned int word = record->m_key >> 5;
		unsigned int mask = 1 << (record->m_key & 0x1F);

		if ((int)otherWords > (int)word &&
			(((unsigned int *)other.m_wordsBegin)[word] & mask) &&
			!(((unsigned int *)m_wordsBegin)[word] & mask))
		{
			++record->m_useCount;
			((unsigned int *)m_wordsBegin)[word] |= mask;
		}

		record = (LargeGroupAudioKeyRecord *)
			_STL::_Rb_global<bool>::_M_increment(record);
	}
}
