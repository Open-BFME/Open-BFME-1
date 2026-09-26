// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3 partial_sort algorithm; the entry identity remains neutral.
// Partial sorting over BFME's eight-byte GameText StringLookUp records.
// Retail 0x004384D0 is the partial-sort layer which shares the already-owned
// make_heap, adjust_heap, and sort_heap siblings at 0x00437D80, 0x004379B0,
// and 0x004382D0.

extern const char g_bfmeEmptyAscii[];
extern "C" __declspec(dllimport) int __cdecl _stricmp(
	const char *left, const char *right);

class AsciiStringData;
class AsciiString
{
public:
	__forceinline const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}

private:
	AsciiStringData *m_data;
};

struct StringInfo;

struct StringLookUp
{
	AsciiString *label;
	StringInfo *info;
};

struct StringLookUpCompare00437D80
{
	void *m_state;

	__forceinline bool operator()(const StringLookUp &left,
		const StringLookUp &right) const
	{
		return _stricmp(left.label->str(), right.label->str()) < 0;
	}
};

// The existing ILTs lead to the already-owned heap bodies.  Typed local
// calls state the observed caller-cleaned ABI without adding template aliases.
extern void j_00009a6b();
extern void j_00028501();
extern void j_00024686();

void Rva004384D0PartialSort(StringLookUp *first, StringLookUp *middle,
    StringLookUp *last, StringLookUp *, StringLookUpCompare00437D80 comp)
{
    typedef void (__cdecl *MakeHeap)(StringLookUp *, StringLookUp *,
        StringLookUpCompare00437D80, StringLookUp *, int *);
    union { void (*raw)(); MakeHeap typed; } make;
    make.raw = j_00009a6b;
    make.typed(first, middle, comp, 0, 0);
    for (StringLookUp *i = middle; i < last; ++i)
    {
        if (comp(*i, *first))
        {
            StringLookUp item = *i;
            *i = *first;
            typedef void (__cdecl *AdjustHeap)(StringLookUp *, int, int,
                StringLookUp, StringLookUpCompare00437D80);
            union { void (*raw)(); AdjustHeap typed; } adjust;
            adjust.raw = j_00028501;
            adjust.typed(first, 0, (int)(middle - first), item, comp);
        }
    }
    typedef void (__cdecl *SortHeap)(StringLookUp *, StringLookUp *,
        StringLookUpCompare00437D80);
    union { void (*raw)(); SortHeap typed; } sort;
    sort.raw = j_00024686;
    sort.typed(first, middle, comp);
}
