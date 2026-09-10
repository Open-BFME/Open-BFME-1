// ?d_005f3750@@YAXXZ
// partial score=0.78 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB
// stlport

// The retail ILT at 0x000391F3 names this route
// DefaultModule6CtorShim::construct and jumps to 0x005F3750.  The direct
// callers at 0x005E5840 (DefaultModule6Allocation) and 0x005E24B0
// (T1Derived_005E24B0) establish the constructor ABI.  The two list calls
// use the existing AssetList and guarded-forwarder routes; the destructor
// route remains the existing STL-tree body reached through 0x00015D7A.

class AsciiString
{
private:
	const char *m_data;
};

class ParticleSystem;

template <class T>
class TrackingPtr
{
};

class BfmeR0
{
public:
	virtual void bfmeSlot0(void);
	int m_bfmeFields[4];
};

class BfmeRA
{
public:
	virtual void bfmeSlotA(void);
};

class BfmeRMiddle : public BfmeR0, public BfmeRA
{
public:
	BfmeRMiddle(void *first, void *second);
};

namespace FXParticleSystem
{

class ParticleSystem;

class DefaultDrawModuleInfo
{
public:
	DefaultDrawModuleInfo()
	{
		*(volatile unsigned int *)this = 0x01110920;
	}
	virtual ~DefaultDrawModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(void *xfer);
};

class DefaultModule6CtorShim
{
public:
	void construct(TrackingPtr<ParticleSystem> &system, const void *source);
};

}

void *bfmeAlloc950B(unsigned int n);

struct Rva005F3750Node
{
	char m_flag;
	char m_pad[3];
	int m_value;
	Rva005F3750Node *m_next;
	Rva005F3750Node *m_prev;
};

class Rva005F3750AssetList
{
public:
	Rva005F3750AssetList()
	{
		m_head = 0;
		m_head = (Rva005F3750Node *)bfmeAlloc950B(0x14);
		m_value = 0;
		m_head->m_flag = 0;
		m_head->m_value = 0;
		m_head->m_next = m_head;
		m_head->m_prev = m_head;
		m_field0c = 0;
		*(volatile unsigned char *)((unsigned char *)this + 0x10) = 1;
	}

	~Rva005F3750AssetList();

	Rva005F3750Node *m_head;
	int m_value;
	char m_pad[4];
	volatile int m_field0c;
	char m_field10;
};

// The destructor is an unknown local ABI route, so keep its compiler symbol
// explicitly tied to the existing ILT without asserting a semantic owner.
#pragma comment(linker, "/alternatename:??1Rva005F3750AssetList@@QAE@XZ=?j_00015d7a@@YAXXZ")

struct BfmeSub934A
{
	int m_value;
};

class BfmeOther934A
{
public:
	void bfmeCall934A(BfmeSub934A *value);
};

#define FirstUpdateSubsystem (*(void **)0x0134faa0)

extern ParticleSystem *Make00001B18(void);
extern void Rva009EBAC0(int value);

class __declspec(novtable) Rva005F3750DefaultModule6
	: public BfmeRMiddle,
	  public FXParticleSystem::DefaultDrawModuleInfo
{
public:
	Rva005F3750DefaultModule6(
		TrackingPtr<FXParticleSystem::ParticleSystem> &system,
		const void *source);
};

// ??0Rva005F3750DefaultModule6@@ present-unmatched
Rva005F3750DefaultModule6::Rva005F3750DefaultModule6(
	TrackingPtr<FXParticleSystem::ParticleSystem> &system,
	const void *source)
	: BfmeRMiddle((void *)&system, (void *)source)
	, FXParticleSystem::DefaultDrawModuleInfo()
{
	*(volatile unsigned int *)this = 0x01112e78;
	*(volatile unsigned int *)((unsigned char *)this + 0x14) = 0x01112e74;
	*(volatile unsigned int *)((unsigned char *)this + 0x18) = 0x01112e60;

	if (FirstUpdateSubsystem)
	{
		Rva005F3750AssetList assets;
		if (((BfmeR0 *)this)->m_bfmeFields[0] == 0)
		{
			ParticleSystem *systemObject = Make00001B18();
			((BfmeOther934A *)&assets)->bfmeCall934A(
				(BfmeSub934A *)((unsigned char *)systemObject + 0x10));
		}
		Rva009EBAC0((int)&assets);
	}
}
