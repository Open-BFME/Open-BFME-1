// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// S4 sort compares the numbered BFME display name after it compares the
// entry count.  The count branch and the two UnicodeString temporaries match
// the comparator shared by the retail S4 insertion and heap callers.

template <typename T>
class StringBase
{
friend class UnicodeString;

public:
	__declspec(nothrow) int compareNoCase(const StringBase<T> &other) const;

private:
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}

	__declspec(nothrow) int compareNoCase(const UnicodeString &other) const
	{
		return ((const StringBase<unsigned short> *)this)->compareNoCase(
			*(const StringBase<unsigned short> *)&other);
	}
};

class MapMetaData
{
public:
	UnicodeString bfme_getDisplayName(void);

	char m_pad[0x20];
	int m_count;
};

struct S4Cmp00452A50
{
	void *m_state;
	bool operator()(int a, int b) const;
};

bool S4Cmp00452A50::operator()(int a, int b) const
{
	if (((const MapMetaData *)a)->m_count == ((const MapMetaData *)b)->m_count)
		return ((MapMetaData *)a)->bfme_getDisplayName().compareNoCase(
			((MapMetaData *)b)->bfme_getDisplayName()) < 0;

	return ((const MapMetaData *)a)->m_count < ((const MapMetaData *)b)->m_count;
}
