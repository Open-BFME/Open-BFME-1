// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Retail uses this four-subobject constructor for the DefaultModule1 path.
// The first three subobjects are the BFME holder and two unnamed polymorphic
// slices; the fourth is FXParticleSystem::DefaultAlphaModuleInfo.

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
	unsigned int value0;
	unsigned int value1;
	unsigned int value2;
	unsigned int value3;
};

struct T1BaseSourceImage_005EEBC0
{
	unsigned char prefix[0xc];
	AlphaKeyBlock m_alphaKey[8];
};

namespace FXParticleSystem {

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

}

class T1BaseForward_005EEBC0
	: public BfmeHolderCU,
	  public UnknownModuleSlot14,
	  public UnknownModuleSlot18
{
public:
	T1BaseForward_005EEBC0(void *first, const void *second)
		: BfmeHolderCU((BfmeListCU **)first, (void *)second)
	{
	}
};

class T1Base_005EEBC0
	: public T1BaseForward_005EEBC0,
	  public FXParticleSystem::DefaultAlphaModuleInfo
{
public:
	T1Base_005EEBC0(void *first, void *second);
};

T1Base_005EEBC0::T1Base_005EEBC0(void *first, void *second)
	: T1BaseForward_005EEBC0(first, second),
// ?DefaultAlphaModuleInfo@FXParticleSystem@@QAEXXZ absent-from-retail
	  FXParticleSystem::DefaultAlphaModuleInfo()
{
	const T1BaseSourceImage_005EEBC0 *sourceInfo =
		(const T1BaseSourceImage_005EEBC0 *)second;

	m_alphaKey[0] = sourceInfo->m_alphaKey[0];
	m_alphaKey[1] = sourceInfo->m_alphaKey[1];
	m_alphaKey[2] = sourceInfo->m_alphaKey[2];
	m_alphaKey[3] = sourceInfo->m_alphaKey[3];
	m_alphaKey[4] = sourceInfo->m_alphaKey[4];
	m_alphaKey[5] = sourceInfo->m_alphaKey[5];
	m_alphaKey[6] = sourceInfo->m_alphaKey[6];
	m_alphaKey[7] = sourceInfo->m_alphaKey[7];
}
