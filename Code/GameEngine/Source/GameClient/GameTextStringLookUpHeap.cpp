// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// STLport push-heap pass for BFME's StringLookUp records.

extern const char g_bfmeEmptyAscii[];
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

struct GameTextAsciiString
{
	void *m_data;
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}
};

struct GameTextStringLookUp
{
	GameTextAsciiString *label;
	void *info;
};

void __cdecl GameTextPushHeap004373B0(
	GameTextStringLookUp *first, int holeIndex, int topIndex,
	GameTextAsciiString *label, void *info)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex
		&& _strcmpi(first[parent].label->str(), label->str()) < 0)
	{
		first[holeIndex] = first[parent];
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	first[holeIndex].label = label;
	first[holeIndex].info = info;
}
