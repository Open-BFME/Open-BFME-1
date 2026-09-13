// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &source);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &source)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&source);
	}
	~AsciiString();

private:
	void *m_data;
};

typedef std::list<AsciiString> AsciiStringList;

class BfmeSlotRT : public AsciiStringList
{
};

class BfmeMapRT
{
public:
	void *bfmeFindRT(void *key);
	BfmeSlotRT *bfmeAtRT(void *key);
	void *end(void) const { return m_bfmeEnd; }

	void *m_bfmeEnd;
};

class UserPreferences
{
public:
	virtual ~UserPreferences();

private:
	unsigned char m_unreconstructed_04[0x10];
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	AsciiStringList getNicksForEmail(AsciiString email);

private:
	unsigned char m_emailPasswordMap[0x0c];
	BfmeMapRT m_emailNickMap;
};

// ?getNicksForEmail@GameSpyLoginPreferences@@QAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@VAsciiString@@@Z
AsciiStringList GameSpyLoginPreferences::getNicksForEmail(AsciiString email)
{
	if (m_emailNickMap.bfmeFindRT(&email) == m_emailNickMap.end())
	{
		AsciiStringList empty;
		return empty;
	}
	return *(AsciiStringList *)m_emailNickMap.bfmeAtRT(&email);
}
