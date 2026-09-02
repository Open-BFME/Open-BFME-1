// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ??1Rva8CB6D0Derived@@UAE@XZ, retail 0x008CB790 (129 bytes).
//
// Sibling constructor is Code/Libraries/Source/WWVegas/WWLib/Rva8CB6D0CallbackCtor.cpp
// (0x008CB6D0): Rva899F00Base(0x2A, 8), then callback->vtbl[0](), store at +0x20.
// This destructor reverses that extra member and inlines the 94-byte Q4 teardown
// already landed in Code/GameEngine/Source/Common/Q4VptrPairDtors.cpp:
//   derived vptr 0x01137180
//   if ([this+0x20]) [this+0x20]->vtbl[1](); [this+0x20] = 0
//   middle vptr 0x01136058; notify(0,0); [this+0x18] = 0
//   subobject dtor at +8 (thunk 0x0089CC70); base vptr 0x01135D68
//
// Shape copied from the already-matched 134-byte
// Rva008B01E0HeaderedDeleting destructor: empty most-derived body, member
// destructor inlined at +0x20, __forceinline middle destructor that calls
// Q4Base00D35D68::notify. EH try-levels 0 then 2 then 1.

class Q4Sub00C9CC70
{
public:
	~Q4Sub00C9CC70();
};

class Q4Base00D35D68
{
public:
	void notify(int a, int b);
};

class Rva8CB6D0Root
{
public:
	virtual ~Rva8CB6D0Root() {}
};

class Rva8CB6D0Callback
{
public:
	virtual void invoke();
	virtual void release();
};

class Rva8CB6D0CallbackHolder
{
public:
	~Rva8CB6D0CallbackHolder()
	{
		if (m_callback)
			m_callback->release();
		m_callback = 0;
	}

private:
	Rva8CB6D0Callback *m_callback;
};

class Rva8CB6D0Middle : public Rva8CB6D0Root
{
public:
	__forceinline virtual ~Rva8CB6D0Middle()
	{
		((Q4Base00D35D68 *)this)->notify(0, 0);
		m_flag = 0;
	}

private:
	char m_gap0[8 - 4];
	Q4Sub00C9CC70 m_sub;
	char m_gap1[0x18 - 9];
	int m_flag;
	char m_gap2[0x20 - 0x1C];
};

class Rva8CB6D0Derived : public Rva8CB6D0Middle
{
public:
	virtual ~Rva8CB6D0Derived();

private:
	Rva8CB6D0CallbackHolder m_callback;
};

Rva8CB6D0Derived::~Rva8CB6D0Derived()
{
}
