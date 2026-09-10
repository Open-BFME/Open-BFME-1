// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

// The retail ILT at 0x0003331B is the named
// DefaultModule2CtorShim::construct route and jumps to 0x005FFDB0.  Its
// callers include the real DefaultModule2Allocation constructor at
// 0x005EB510 and ConcreteModuleTemplate<DefaultModuleTag<1>>::createModule
// at 0x005EBFB0.  The semantic owner is therefore the DefaultModule2
// constructor route. Full262B ends5FFEB6CC afterret8; allocationcaller
// reserves60B. Holderbase20B plus4Bsecondary/category slices put the
// updateinfo base at1C; five12B records copy sourceC..47 tothis20..5B
// and the scalar source48 tothis5C. Constructor identity staysRVA-derived.

#include <new>

class BfmeListCU;

template <class T>
class TrackingPtr
{
};

namespace FXParticleSystem
{

class ParticleSystem;

struct RandomVariableImage
{
	unsigned int value0;
	unsigned int value1;
	unsigned int value2;
};

class DefaultUpdateModuleInfo
{
public:
	DefaultUpdateModuleInfo();
	virtual ~DefaultUpdateModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(void *xfer);

	RandomVariableImage var0;
	RandomVariableImage var1;
	RandomVariableImage var2;
	RandomVariableImage var3;
	RandomVariableImage var4;
	unsigned int extra;
};

}

class BfmeHolderCU
{
public:
	BfmeHolderCU(BfmeListCU **list, void *user);
	virtual void unusedVirtual();

	unsigned int m_storage[4];
};

namespace FXParticleSystem
{

struct DefaultModule2SourceImage
{
	unsigned char prefix[0x0c];
	RandomVariableImage var0;
	RandomVariableImage var1;
	RandomVariableImage var2;
	RandomVariableImage var3;
	RandomVariableImage var4;
	unsigned int extra;
};

class DefaultModule2SecondarySlice
{
public:
	virtual void unusedVirtual();
	virtual __declspec(nothrow) ~DefaultModule2SecondarySlice() {}
};

class DefaultModule2CategorySlice
{
public:
	virtual void unusedVirtual();
	virtual __declspec(nothrow) ~DefaultModule2CategorySlice() {}
};

}

class DefaultModule2Base
	: public BfmeHolderCU,
	  public FXParticleSystem::DefaultModule2SecondarySlice,
	  public FXParticleSystem::DefaultModule2CategorySlice
{
public:
	DefaultModule2Base(TrackingPtr<FXParticleSystem::ParticleSystem> &system,
		const void *source)
		: BfmeHolderCU((BfmeListCU **)&system, (void *)source)
	{
	}
};

class Rva005FFDB0DefaultModule2
	: public DefaultModule2Base,
	  public FXParticleSystem::DefaultUpdateModuleInfo
{
	public:
	Rva005FFDB0DefaultModule2(
		TrackingPtr<FXParticleSystem::ParticleSystem> &system,
		const void *source);
};

Rva005FFDB0DefaultModule2::Rva005FFDB0DefaultModule2(
	TrackingPtr<FXParticleSystem::ParticleSystem> &system,
	const void *source)
	: DefaultModule2Base(system, source)
	, FXParticleSystem::DefaultUpdateModuleInfo()
{
	const FXParticleSystem::DefaultModule2SourceImage *sourceImage =
		(const FXParticleSystem::DefaultModule2SourceImage *)source;
	var0 = sourceImage->var0;
	var1 = sourceImage->var1;
	var2 = sourceImage->var2;
	var3 = sourceImage->var3;
	var4 = sourceImage->var4;
	extra = sourceImage->extra;
}
