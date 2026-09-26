// Retail 0x0078D0D0, 62 bytes, which the ledger had in FOUR pieces: the
// handler test, an eight-byte return-one arm, a byte-dump row for the
// fallback, and a second eight-byte return-one arm.
//
// Both arms return the same 1, and the two calls differ in kind. The first is
// a function pointer at +0x1E8 invoked with this and the argument through a
// cdecl frame the caller cleans. The second goes through the vftable of a
// SUB-OBJECT embedded at +0x218 -- the lea of eax+0x218 into ecx is the
// sub-object's own this -- and the callee cleans its two arguments, so that
// one is thiscall.
//
// The fallback saves esi purely to reload the argument after the pushes; the
// first arm does not need to.

class Gen_0078d0d0;

typedef void (__cdecl *BfmeDispatchHandler)(Gen_0078d0d0 *owner, void *argument);

class Gen_0078d0d0Sub
{
public:
	virtual void bfmeSlot00(void);
	virtual void bfmeApply(Gen_0078d0d0 *owner, void *argument);	// +0x04
};

class Gen_0078d0d0
{
public:
	int bfmeDispatch(void *argument);

private:
	char m_bfmeHead[0x1E8];
	BfmeDispatchHandler m_bfmeHandler;				// +0x1E8
	char m_bfmeMid[0x218 - 0x1EC];
	Gen_0078d0d0Sub m_bfmeSub;					// +0x218
};

// ?bfmeDispatch@Gen_0078d0d0@@QAEHPAX@Z
int Gen_0078d0d0::bfmeDispatch(void *argument)
{
	if (m_bfmeHandler)
	{
		m_bfmeHandler(this, argument);

		return 1;
	}

	m_bfmeSub.bfmeApply(this, argument);

	return 1;
}
