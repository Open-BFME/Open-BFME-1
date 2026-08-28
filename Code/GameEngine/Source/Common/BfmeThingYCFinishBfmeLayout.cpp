// BFME layout reconstruction of the list-finisher helper in
// BfmeThreeHundredSeventyFive.cpp.  The two virtual calls and both direct
// incremental-link thunks are already pinned by the retail ledger.

void j_00040ce1();
void j_00028493();

struct BfmeYCParentThunk
{
	void call();
};

struct BfmeYCFinishThunk
{
	void call(void *what);
};

class BfmeThingYC
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01C() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02C() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03C() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04C() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05C() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06C() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07C() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08C() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09C() = 0;
	virtual void slot0A0() = 0;
	virtual void slot0A4() = 0;
	virtual void slot0A8() = 0;
	virtual void slot0AC() = 0;
	virtual void slot0B0() = 0;
	virtual void slot0B4() = 0;
	virtual void slot0B8() = 0;
	virtual void slot0BC() = 0;
	virtual void slot0C0() = 0;
	virtual void slot0C4() = 0;
	virtual void slot0C8() = 0;
	virtual void slot0CC() = 0;
	virtual void slot0D0() = 0;
	virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual void slot0DC() = 0;
	virtual void slot0E0() = 0;
	virtual void slot0E4() = 0;
	virtual void slot0E8() = 0;
	virtual void slot0EC() = 0;
	virtual void slot0F0() = 0;
	virtual void slot0F4() = 0;
	virtual void slot0F8() = 0;
	virtual void slot0FC() = 0;
	virtual unsigned int slot100(int value) = 0;
	void bfmeFinishYC(void *what);
};

void BfmeThingYC::bfmeFinishYC(void *what)
{
	if (slot100(0) > 0)
	{
		typedef void (BfmeYCParentThunk::*BfmeParentAction)();
		union { void *asVoid; BfmeParentAction asMember; } parentCast;
		parentCast.asVoid = (void *)j_00040ce1;
		(reinterpret_cast<BfmeYCParentThunk *>(reinterpret_cast<unsigned char *>(this) - 0x20)->*parentCast.asMember)();
	}

	typedef void (BfmeYCFinishThunk::*BfmeFinishAction)(void *);
	union { void *asVoid; BfmeFinishAction asMember; } finishCast;
	finishCast.asVoid = (void *)j_00028493;
	(reinterpret_cast<BfmeYCFinishThunk *>(this)->*finishCast.asMember)(what);
	slot040();
}
