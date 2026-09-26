// cl: /O2 /DNDEBUG /MD
// RVA 008B8E10, 53 bytes, thiscall ret 8: grow storage to index+1, store
// the element through bfmePut1242, then raise the +28 count to index+1.
// Caller: Rva008CE1E0StoreMember (integer-keyed store on a kind-22 value).
// The count update is a conditional expression, not an if on a local:
// the local-plus-if spelling swaps this/index+1 between ESI and EDI.

class BfmeE1242;

class BfmeN1242
{
public:
	void bfmeReserve1242(int n);
	void bfmePut1242(int i, BfmeE1242 *e);
	void rva008B8E10(int i, BfmeE1242 *e);

	char m_bfmePad00[0x28];
	int m_bfme28;
};

void BfmeN1242::rva008B8E10(int i, BfmeE1242 *e)
{
	if (i >= 0)
	{
		int n = i + 1;
		bfmeReserve1242(n);
		bfmePut1242(i, e);
		m_bfme28 = n > m_bfme28 ? n : m_bfme28;
	}
}
