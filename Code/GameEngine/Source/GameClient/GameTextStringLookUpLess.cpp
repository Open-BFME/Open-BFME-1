// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// StringLookUp ordering predicate used by the BFME GameTextManager sort.

extern const char g_bfmeEmptyAscii[];
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char *left, const char *right);

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}

private:
	void *m_data;
};

struct StringLookUp
{
	AsciiString *label;
	void *info;
};

bool __stdcall compareStringLookUpLess(const void *left, const void *right)
{
	const StringLookUp *lut1 = (const StringLookUp *)left;
	const StringLookUp *lut2 = (const StringLookUp *)right;
	return _stricmp(lut1->label->str(), lut2->label->str()) < 0;
}
