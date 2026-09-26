// ?Rva0013BE40@@YG_NHH@Z
// partial score=0.35 date=2026-09-21
// ?d_0013be40@@YAXXZ at retail RVA 0x0013BE40.
//
// A local DynamicVectorClass<StringClass> is default-constructed (size=0),
// its base ctor call resolving to the already-matched
// ??0?$VectorClass@VStringClass@@@@QAE@HPBVStringClass@@@Z at 0x0013A580
// (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp), then
// the derived ctor's vtable install (0x01091078) and GrowthStep/ActiveCount
// stores are inlined -- matching WWLib/vector.h's
// DynamicVectorClass<T>::DynamicVectorClass. A local BFMERetailAsciiString
// is zero-initialised and released (empty, so releaseBuffer is a no-op).
// Neither local is ever populated, so the trailing ~VectorClass<T> (inlined
// VectorClass<T>::Clear) never actually frees anything either; the function
// simply returns true. Its own two stack args (ret 8) are never read.

class StringClass
{
public:
	~StringClass();
};

template<class T>
class VectorClass
{
public:
	VectorClass(int size, T const *array);
	virtual ~VectorClass(void) { VectorClass<T>::Clear(); }
	virtual bool operator==(VectorClass<T> const &) const { return false; }
	virtual bool Resize(int newsize, T const *array = 0) { return false; }
	virtual void Clear(void)
	{
		if (Vector && IsAllocated)
		{
			delete[] Vector;
			Vector = 0;
		}
		IsAllocated = false;
		VectorMax = 0;
	}
	virtual int ID(T const *ptr) { return -1; }
	virtual int ID(T const &ptr) { return -1; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(unsigned size = 0, T const *array = 0);
	virtual bool Resize(int newsize, T const *array = 0) { return false; }
	virtual void Clear(void) { ActiveCount = 0; VectorClass<T>::Clear(); }
	virtual int ID(T const *ptr) { return VectorClass<T>::ID(ptr); }
	virtual int ID(T const &ptr) { return -1; }

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const *array)
	: VectorClass<T>(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_buffer(0) {}
	void releaseBuffer();

private:
	void *m_buffer;
};

// ?d_0013be40@@YAXXZ
__declspec(noinline) bool __stdcall Rva0013BE40(int unusedA, int unusedB)
{
	DynamicVectorClass<StringClass> unusedErrors;
	BFMERetailAsciiString tempStr;
	tempStr.releaseBuffer();
	return true;
}
