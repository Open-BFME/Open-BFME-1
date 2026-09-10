// cl: /DNDEBUG /MD /EHsc

// VectorClass<StringClass>::ID(const StringClass &), the value-search vtable
// slot at retail RVA 0x0013A670.  StringClass stores one character-buffer
// pointer, so this specialization compares the pointed-to strings through
// the CRT's _mbscmp import rather than comparing StringClass object pointers.
// The VectorClass layout is the retail four-byte Vector/VectorMax/flags form.

typedef char TCHAR;

extern "C" __declspec( dllimport ) int __cdecl _mbscmp(
	const unsigned char *left, const unsigned char *right );

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
