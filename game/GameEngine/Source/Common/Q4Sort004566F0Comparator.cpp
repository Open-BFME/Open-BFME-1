// cl: /DNDEBUG /MD /EHsc

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
	UnicodeString getFileName() const;
};

#pragma comment(linker, "/alternatename:?getFileName@MapMetaData@@QBE?AVUnicodeString@@XZ=?d_00451350@@YAXXZ")

struct Q4Sort004566F0
{
	bool operator()(int a, int b) const;
};

bool Q4Sort004566F0::operator()(int a, int b) const
{
	return ((const MapMetaData *)a)->getFileName().compareNoCase(
		((const MapMetaData *)b)->getFileName()) < 0;
}
