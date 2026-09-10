// ?ID@?$VectorClass@VStringClass@@@@UAEHABVStringClass@@@Z
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

// Slot 4 of VectorClass<StringClass>'s vtable: the by-value/content search
// overload, VectorClass<T>::ID(const T&) (find_index). Loops VectorMax
// entries; the comparison resolves through StringClass's TCHAR* conversion
// and Compare() to a direct _mbscmp call on the two 4-byte buffer pointers,
// because StringClass has no vtable and a single member (m_Buffer).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h

typedef char TCHAR;

extern "C" __declspec( dllimport ) int __cdecl _mbscmp(
	const unsigned char *left, const unsigned char *right );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	inline operator const unsigned char *(void) const { return (const unsigned char *)m_Buffer; }

private:
	TCHAR *m_Buffer;
};

template <class T>
class VectorClass
{
public:
	virtual ~VectorClass(void);
	virtual bool operator==(const VectorClass<T> &that) const;
	virtual bool Resize(int newsize, const T *array = 0);
	virtual void Clear(void);
	virtual int ID(const T &object);
	virtual int ID(const T *ptr);

	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
};

// ?ID@?$VectorClass@VStringClass@@@@UAEHABVStringClass@@@Z
template <class T>
int VectorClass<T>::ID(const T &object)
{
	if (!IsValid)
		return 0;

	for (int index = 0; index < VectorMax; index++) {
		if (_mbscmp(Vector[index], object) == 0)
			return index;
	}

	return -1;
}

template int VectorClass<StringClass>::ID(const StringClass &);
