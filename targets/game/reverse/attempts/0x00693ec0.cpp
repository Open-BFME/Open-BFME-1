// ?notify@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z
// partial score=0.57 date=2026-09-21
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME5: retail 0x00693EC0 (191B).
// ?notify@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z
// Identity proven by Gen0002857E::release (Gen0002857ERelease.cpp, matched:
// "m_owner->notify(this)") and the owner's mutex at +0x48 (same
// Gen0002857EOwner layout). Guarded by the SAME mutex-guard shape as
// release() (bfmeWait1012/Rva01358ECC are separate IAT pins for
// WaitForSingleObject/ReleaseMutex, not the ones release() imports
// directly). If self->m_active (offset 0x41, same field
// Gen0002857EOwnerDestroy.cpp's Gen0002857E::m_active), build a
// {unsigned id, AsciiString name} key (Rva00691ED0Key's own shape,
// identical to RvaTreeInsertUnique006934C0Compound.cpp's Rva006934C0Key)
// from self and insert it into a set embedded at owner+0x20; otherwise
// call owner->destroy(self, 1) (Gen0002857EOwnerDestroy.cpp).
//
// PARTIAL: the guard/branch skeleton (mutex acquire through the m_active
// test, the [esp+0x30]=0 store, and the je/test/mov edi sequence) is
// byte-exact once the guard is declared before an explicit "name" local
// (matching retail's own sub esp,0x18 frame size exactly). The exact
// source of the key's "id" field and which of self's members back the
// AsciiString name are not established -- the GameSpyGroupRoom copy-ctor
// call is an ICF alias for StringBase<char>'s copy ctor, and the retail
// call sequence copy-constructs from *self (reinterpreted as
// StringBase<char>) into a stack temp, then constructs the key from
// self->field_0x38, an ABI this source approximates without independent
// proof; guard's own stack slots land 8 bytes higher than retail's
// (retail packs them below the later locals, this compile does the
// opposite) despite the frame size matching. Best score: 109/191
// matching bytes (0.57).

typedef unsigned int UnsignedInt;

__declspec(dllimport) unsigned long __stdcall bfmeWait1012(void *handle, int ms);
__declspec(dllimport) void __stdcall Rva01358ECC(void *handle);

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
	void *m_data;
};

class Gen0002857E
{
public:
	void destruct();

	AsciiString m_name;
	char m_pad04[0x38 - sizeof(AsciiString)];
	AsciiString *m_namePtr;
	char m_pad3c[0x41 - 0x3c];
	bool m_active;
};

struct Rva00691ED0Key
{
	Rva00691ED0Key(unsigned primary, AsciiString name);

	unsigned m_primary;
	AsciiString m_name;
};

class Rva00691ED0Set
{
public:
	void insert(const Rva00691ED0Key &key);
};

class Gen0002857EOwner
{
public:
	void notify(Gen0002857E *self);
	void destroy(Gen0002857E *value, int deferred);

private:
	char m_pad20[0x20];
	Rva00691ED0Set m_set;
	char m_pad48[0x48 - (0x20 + sizeof(Rva00691ED0Set))];
	void *m_mutex;
};

class Gen0002857EMutexGuard
{
public:
	Gen0002857EMutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (bfmeWait1012(handle, -1) != 0x102)
			m_owned = 1;
	}

	~Gen0002857EMutexGuard()
	{
		if (m_owned)
			Rva01358ECC(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

void Gen0002857EOwner::notify(Gen0002857E *self)
{
	Gen0002857EMutexGuard guard(m_mutex);

	if (self->m_active)
	{
		AsciiString nameCopy(*(const AsciiString *)self);
		AsciiString name(*self->m_namePtr);
		Rva00691ED0Key key(0, name);
		m_set.insert(key);
	}
	else
	{
		destroy(self, 1);
	}
}
