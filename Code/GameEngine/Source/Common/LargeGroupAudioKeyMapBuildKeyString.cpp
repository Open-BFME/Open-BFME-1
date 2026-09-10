// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LargeGroupAudioKeyMap key-string builder, retail 0x003D37E0,
// 264 bytes. The xfer method at 0x003D3930 calls this helper while saving.

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

public:
	int getLength() const { return m_data ? m_data->length : 0; }
	const T *str() const
	{
		return m_data ? &m_data->data[0] : (const T *)0x0107388b;
	}
	bool isNotEmpty() const
	{
		return m_data != 0 && m_data->length != 0;
	}
	void concat(const T *text, int length);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int getLength() const { return StringBase<char>::getLength(); }
	const char *str() const { return StringBase<char>::str(); }
	bool isNotEmpty() const { return StringBase<char>::isNotEmpty(); }
	void concat(char source) { StringBase<char>::concat(&source, 1); }
	void concat(const AsciiString &source)
	{
		StringBase<char>::concat(source.str(), source.getLength());
	}
	void concat(const char *source, int length)
	{
		StringBase<char>::concat(source, length);
	}
};

namespace _STL
{

struct _Rb_tree_node_base
{
	bool m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

}

struct LargeGroupAudioKeyRecord : _STL::_Rb_tree_node_base
{
	AsciiString m_name;
	unsigned int m_key;
	unsigned int m_useCount;
};

extern LargeGroupAudioKeyRecord *g_lgaKeyRecordSentinel;

class LargeGroupAudioKeyMap
{
public:
	AsciiString bfmeBuildKeyString();

private:
	unsigned int *m_wordsBegin;
	unsigned int *m_wordsEnd;
	unsigned int *m_wordsCapacity;
};

// ?bfmeBuildKeyString@LargeGroupAudioKeyMap@@QAE?AVAsciiString@@XZ
AsciiString LargeGroupAudioKeyMap::bfmeBuildKeyString()
{
	AsciiString result;
	LargeGroupAudioKeyRecord *record =
		(LargeGroupAudioKeyRecord *)g_lgaKeyRecordSentinel->m_left;

	while (record != g_lgaKeyRecordSentinel)
	{
		unsigned int key = record->m_key;
		unsigned int word = key >> 5;
		unsigned int mask = 1 << (key & 0x1F);
		if (m_wordsEnd - m_wordsBegin > word &&
			(m_wordsBegin[word] & mask) != 0)
		{
			if (result.isNotEmpty())
				result.concat(' ');
			result.concat(record->m_name);
		}

		record = (LargeGroupAudioKeyRecord *)
			_STL::_Rb_global<bool>::_M_increment(record);
	}

	return result;
}
