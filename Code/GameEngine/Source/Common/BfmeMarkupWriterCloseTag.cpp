// stlport
// Clean C++ conversion of the writer close-tag method at retail RVA 0x009D9AD0.
// The object carries the same pending flag and STLport string stack as the
// adjacent formatter overloads at 0x009D9360..0x009D9A80.
#include <string>
#include <vector>

extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);

class Gen009D9AD0
{
public:
	virtual void closeTag(void);

private:
	bool m_pending;
	void *m_sink;
	std::vector<std::string> m_tags;
};

// ?closeTag@Gen009D9AD0@@UAEXXZ
void Gen009D9AD0::closeTag(void)
{
	if (m_tags.empty())
		return;

	std::string tag = m_tags.back();
	m_tags.pop_back();
	if (m_pending)
	{
		bfmeAppend(this, reinterpret_cast<const char *>(0x01080294));
		m_pending = false;
	}
	bfmeAppend(this, 0);
	bfmeAppend(this, reinterpret_cast<const char *>(0x01144530), tag.c_str());
}
