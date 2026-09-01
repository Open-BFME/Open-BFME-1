// ?bfmeInsertQI@BfmeThingQI@@QAEPADPADE@Z
// partial score=0.95 date=2026-09-01
// cl: /Od
// A byte put at a place: appended when the place is the end, otherwise handed
// to the inserter. Built without optimisation; the frame holds more than this
// body names. Both callees are pinned by address.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *, const void *, unsigned int);

namespace _STL
{
template <class T> struct char_traits { };

template <> struct char_traits<char>
{
	static void assign(char &, const char &);
};

class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};
}

void *bfmeBigAllocPR(unsigned int bytes);
void *bfmeAllocPV(int one, unsigned int pointer);
void j_000159d8();
void j_0001eace();

namespace _STL
{
void *__copy_trivial(const void *first, const void *last, void *out);
}

class BfmeThingQI
{
public:
	char *bfmeSetQI(char *at, unsigned char one);

	void bfmePushQI(unsigned char one);

	char *bfmeInsertQI(char *at, unsigned char one);

	char *m_bfmeStart;			// 0x0
	char *m_bfmeEnd;			// 0x4
	char *m_bfmeLimit;			// 0x8
};

char *BfmeThingQI::bfmeSetQI(char *at, unsigned char one)
{
	unsigned char spare[0x14];

	char *end = m_bfmeEnd;

	if (at == end)
	{
		bfmePushQI(one);

		return m_bfmeEnd - 1;
	}

	return bfmeInsertQI(at, one);
}

char *BfmeThingQI::bfmeInsertQI(char *at, unsigned char one)
{
	char *result = at;

	if (m_bfmeEnd + 1 < m_bfmeLimit)
	{
		char *newEnd = m_bfmeEnd + 1;
		char zero = 0;
		*newEnd = zero;
		unsigned int bytes = (unsigned int)(m_bfmeEnd - at);
		char *after = at + 1;
		char *result;
		if (bytes == 0)
			result = after;
		else
			result = (char *)memmove(after, at, bytes);

		_STL::char_traits<char>::assign(*at, one);

		m_bfmeEnd = newEnd;
		return result;
	}

	char *oldEnd = m_bfmeEnd;
	unsigned int oldSize = (unsigned int)(oldEnd - m_bfmeStart);
	unsigned int growth = 1;
	unsigned int *growthPointer = &growth;
	if (oldSize >= growth)
		growthPointer = &oldSize;
	unsigned int newSize = oldSize + *growthPointer;
	void *newBuffer;
	if (newSize != 0)
	{
		if (newSize > 0x80)
			newBuffer = bfmeBigAllocPR(newSize);
		else
			newBuffer = _STL::__new_alloc::allocate(newSize);
	}
	else
		newBuffer = 0;

	char *newStart = (char *)newBuffer;
	char *newFinish = newStart;
	newFinish = (char *)_STL::__copy_trivial(m_bfmeStart, at, newFinish);
	char *inserted = (char *)bfmeAllocPV(1, (unsigned int)newFinish);
	if (inserted != 0)
	{
		*inserted = one;
		newFinish = inserted;
	}
	else
		newFinish = 0;

	newFinish = (char *)_STL::__copy_trivial(at, oldEnd, newFinish + 1);
	char zero = 0;
	*newFinish = zero;
	j_000159d8();
	j_0001eace();
	m_bfmeStart = newStart;
	m_bfmeEnd = newFinish;
	m_bfmeLimit = newStart + newSize;
	return at;
}
