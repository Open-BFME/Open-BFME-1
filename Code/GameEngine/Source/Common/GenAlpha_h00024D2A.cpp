// cl: /DNDEBUG /MD /EHsc

// GenAlpha::h00024D2A, retail 0x007B9760, 139 bytes.
//
// Named by the already-matched S3 triple at 0x007B7680, whose REL32 lands
// on ILT 0x00024D2A and follows to this body. Scoped W3D radar lock, two
// COM Release()s on the globals at 0x01306F20 / 0x01306F1C, then
// Rva007ADB80Owner::releaseReferences on 0x01306DE8 and a thiscall back
// through ILT 0x0003139A.

typedef unsigned long ULONG;

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class BfmeRadarResetGuard
{
public:
	BfmeRadarResetGuard() { W3DRadarResetLock(); }
	~BfmeRadarResetGuard() { W3DRadarResetUnlock(); }
};

struct BfmeComUnknown
{
	virtual long __stdcall QueryInterface(void *riid, void **ppv) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
};

class Rva007ADB80Owner
{
public:
	void releaseReferences();
};

class GenAlpha
{
public:
	void h00024D2A();
	void afterRelease();
};

extern BfmeComUnknown *TheBfmeComA;			// 0x01306F20
extern BfmeComUnknown *TheBfmeComB;			// 0x01306F1C
extern Rva007ADB80Owner *TheBfmeReleaseOwner;	// 0x01306DE8

// ?h00024D2A@GenAlpha@@QAEXXZ
void GenAlpha::h00024D2A()
{
	BfmeRadarResetGuard guard;
	if (TheBfmeComA)
		TheBfmeComA->Release();
	if (TheBfmeComB)
		TheBfmeComB->Release();
	Rva007ADB80Owner *owner = TheBfmeReleaseOwner;
	TheBfmeComA = 0;
	TheBfmeComB = 0;
	if (owner)
	{
		owner->releaseReferences();
		afterRelease();
	}
}
