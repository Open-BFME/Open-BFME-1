// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

struct BfmeEntVTF;

// 0x00887B60 is matched in functions.csv as the private
// StringBase<char>::StringBase(const StringBase<char> &)
// (game/Libraries/Source/string/StringBase.cpp), the body retail calls through
// AsciiString's inline copy ctor whenever a string field is copied. It is
// declared TU-locally at that spelling; the enclosing struct is the friend that
// owns the field, so it may copy it.
template <typename T>
class StringBase
{
	friend struct BfmeEntVTF;

private:
	StringBase(const StringBase &src);

	T *m_data;
};

struct BfmeEntVTF
{
	__forceinline BfmeEntVTF(const BfmeEntVTF &other)
		: m_bfme00(other.m_bfme00), m_bfme04(other.m_bfme04),
		  m_bfme08(other.m_bfme08), m_bfme0c(other.m_bfme0c)
	{
	}

	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	StringBase<char> m_bfme0c;
};

void bfmeConstructVTF(BfmeEntVTF *dest, const BfmeEntVTF *source)
{
	new (dest) BfmeEntVTF(*source);
}