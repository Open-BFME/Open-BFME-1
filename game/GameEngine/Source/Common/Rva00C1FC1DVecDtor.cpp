// cl: /EHsc
//
// Open-BFME: Unwind@0101fc1d retail 0x00C1FC1D size 24. Compiler generated
// `eh vector destructor iterator' body (??_M @ 0x009F6D76) that destroys 64
// already-constructed 4-byte elements at offset 0x244FC when a later member's
// constructor throws. Retail spills `this' to a fixed frame slot before the
// offset add -- the mark of a genuine compiler unwind funclet, not hand
// written cleanup code -- so this TU reproduces it as real member
// construction order rather than an explicit call. The element dtor and the
// throwing member have no recoverable identity from the Unwind@ label alone.

class BfmeElemC1FC1D
{
public:
	BfmeElemC1FC1D();
	~BfmeElemC1FC1D();
private:
	char m_bytes[4];
};

class BfmeThrowerC1FC1D
{
public:
	BfmeThrowerC1FC1D();
};

class Rva00C1FC1DHost
{
public:
	Rva00C1FC1DHost();
private:
	char m_pad[0x244FC];
	BfmeElemC1FC1D m_arr[0x40];
	BfmeThrowerC1FC1D m_tail;
};

// ??0Rva00C1FC1DHost@@QAE@XZ absent-from-retail
Rva00C1FC1DHost::Rva00C1FC1DHost()
{
}
