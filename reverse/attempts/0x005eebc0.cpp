// ?d_005eebc0@@YAXXZ
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME: the shared four-subobject constructor at 0x005EEBC0.
//
// The retail body is reached by the named
// ConcreteModuleTemplate<DefaultModuleTag<1> >::createModule path through
// DefaultModule1Allocation, and also by an address-derived constructor in
// the neighbouring base-forwarding family.  Its first call is the matched
// BfmeHolderCU constructor.  The two four-byte regions at +0x14 and +0x18
// are polymorphic subobjects whose semantic names are not recovered; their
// retail initial vftables are nevertheless explicit in this body.  The
// subobject at +0x1c is the matched DefaultAlphaModuleInfo constructor.
// Keep those two unknown slots as local layout records rather than assigning
// an unproved class identity to them.

class BfmeListCU;
class BfmeLinkCU;

class ParticleSystem;

template <class T>
class TrackingPtr
{
	T *m_ptr;
};

class BfmeHolderCU
{
public:
	BfmeHolderCU(BfmeListCU **list, void *user);
	virtual void unknownSlot();

private:
	BfmeListCU *m_bfmeListCU;
	BfmeLinkCU *m_bfmeNextCU;
	BfmeLinkCU *m_bfmePrevCU;
	void *m_bfmeUserCU;
};

class UnknownModuleSlot14
{
public:
	virtual void unknownSlot();
	virtual __declspec(nothrow) ~UnknownModuleSlot14() {}
};

class UnknownModuleSlot18
{
public:
	virtual void unknownSlot();
	virtual __declspec(nothrow) ~UnknownModuleSlot18() {}
};

class Xfer;

struct AlphaKeyBlock
{
	unsigned int value[4];
};

class DefaultAlphaModuleInfo
{
public:
	DefaultAlphaModuleInfo();
	virtual ~DefaultAlphaModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

	AlphaKeyBlock m_alphaKey[8];
};

class T1Base_005EEBC0
	: public BfmeHolderCU,
	  public UnknownModuleSlot14,
	  public UnknownModuleSlot18,
	  public DefaultAlphaModuleInfo
{
public:
	T1Base_005EEBC0(void *first, void *second);
};

T1Base_005EEBC0::T1Base_005EEBC0(void *first, void *second)
	: BfmeHolderCU((BfmeListCU **)first, second)
{
	*(volatile unsigned int *)this = 0x01113040;
	*(volatile unsigned int *)((unsigned char *)this + 0x14) = 0x0111303c;
	*(volatile unsigned int *)((unsigned char *)this + 0x18) = 0x01113038;
	*(volatile unsigned int *)((unsigned char *)this + 0x1c) = 0x01113008;

	const DefaultAlphaModuleInfo *sourceInfo =
		(const DefaultAlphaModuleInfo *)((const unsigned char *)second + 8);
	DefaultAlphaModuleInfo *destinationInfo =
		(DefaultAlphaModuleInfo *)((unsigned char *)this + 0x1c);

	destinationInfo->m_alphaKey[0] = sourceInfo->m_alphaKey[0];
	destinationInfo->m_alphaKey[1] = sourceInfo->m_alphaKey[1];
	destinationInfo->m_alphaKey[2] = sourceInfo->m_alphaKey[2];
	destinationInfo->m_alphaKey[3] = sourceInfo->m_alphaKey[3];
	destinationInfo->m_alphaKey[4] = sourceInfo->m_alphaKey[4];
	destinationInfo->m_alphaKey[5] = sourceInfo->m_alphaKey[5];
	destinationInfo->m_alphaKey[6] = sourceInfo->m_alphaKey[6];
	destinationInfo->m_alphaKey[7] = sourceInfo->m_alphaKey[7];
}
