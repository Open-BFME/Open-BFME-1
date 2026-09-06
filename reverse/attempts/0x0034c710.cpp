// ?bfmeCallZC@BfmeOwnZC@@QAEXABVBfmeRoomZC@@PAX@Z (identity unknown)
// partial score=0.83 date=2026-09-06
// 30/36 at exact size. Everything matches except a two-instruction swap at
// +0x0d: retail emits the esp marker BEFORE `mov ecx,esp` (the copy ctor's
// this), MSVC after. Tried /G7 /Ob1 /Ot /Gy /Os, an explicit this-> on the
// call, no destructor (size mismatch, the marker disappears) and an inline
// empty destructor. All give the identical two-line swap.
// Copy ctor is the string_base alias pinned DIRECTLY at 0x00887B60.
class BfmeRoomZC
{
public:
	BfmeRoomZC(const BfmeRoomZC &other);
	~BfmeRoomZC();

	int m_bfmeHandleZC;
};

class BfmeOwnZC
{
public:
	void bfmeCallZC(const BfmeRoomZC &name, void *extra);
	void bfmeRunZC(BfmeRoomZC name, void *extra);
};

void BfmeOwnZC::bfmeCallZC(const BfmeRoomZC &name, void *extra)
{
	bfmeRunZC(name, extra);
}
