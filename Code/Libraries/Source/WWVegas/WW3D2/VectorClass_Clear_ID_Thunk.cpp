// cl: /DNDEBUG /MD /EHsc

// Slots 3 and 5 of a VectorClass vtable whose other four slots are named:
// operator== at 1, Resize at 2, ID taking a const reference at 4. The layout the
// bodies use is the reference one -- Vector at +4, VectorMax at +8, IsValid at
// +0x0C, IsAllocated at +0x0D.
//
// This is a pointer-element instantiation, which is why ID divides by four with a
// shift rather than a reciprocal multiply, and why the same bodies are folded
// into several instantiations' vtables at once.
class FontCharsBuffer;

typedef FontCharsBuffer *FontCharsBufferPtr;

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

// ?Clear@?$VectorClass@PAVFontCharsBuffer@@@@UAEXXZ
template <class T>
void VectorClass<T>::Clear(void)
{
	if (Vector && IsAllocated) {
		delete[] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

// ?ID@?$VectorClass@PAVFontCharsBuffer@@@@UAEHPBQAVFontCharsBuffer@@@Z
template <class T>
int VectorClass<T>::ID(const T *ptr)
{
	if (!IsValid)
		return 0;
	return ((unsigned long)ptr - (unsigned long)Vector) / sizeof(T);
}

template void VectorClass<FontCharsBufferPtr>::Clear(void);
template int VectorClass<FontCharsBufferPtr>::ID(const FontCharsBufferPtr *);
