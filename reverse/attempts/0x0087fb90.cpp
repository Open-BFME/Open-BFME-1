// ?erase@BfmeVec60@@QAEXPAUBfmeElem60@@0@Z
// partial score=0.55 date=2026-09-05
// cl: /O2 /Ob0 /G6
//
// Open-BFME5: BfmeVec60::erase(first,last) at retail 0x0087FB90, 77 bytes.
// Near-twin of the PA-style vector<T>::erase(first,last) family on
// d_003ad560.asm (see PAVectorEraseRangeFamily003AF.cpp): identical shape
// except the per-element teardown is a direct (non-virtual) call to
// BFMERetailAsciiString::releaseBuffer() instead of a vtable dispatch,
// because BfmeElem60 has no virtual destructor.

class BFMERetailAsciiString
{
public:
	__forceinline ~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

struct BfmeElem60
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BFMERetailAsciiString m_1C;
	char m_20;
	char m_pad[3];
};

class BfmeVec60
{
public:
	void erase(BfmeElem60 *first, BfmeElem60 *last);

	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

struct BfmeElemA2;

extern BfmeElemA2 *bfmeCopyA2(BfmeElemA2 *first, BfmeElemA2 *last, BfmeElemA2 *dest);

void BfmeVec60::erase(BfmeElem60 *first, BfmeElem60 *last)
{
	BfmeElem60 *newFinish = reinterpret_cast<BfmeElem60 *>(
		bfmeCopyA2(reinterpret_cast<BfmeElemA2 *>(last),
			reinterpret_cast<BfmeElemA2 *>(_M_finish),
			reinterpret_cast<BfmeElemA2 *>(first)));

	for (BfmeElem60 *p = newFinish; p != _M_finish; ++p)
		p->~BfmeElem60();

	_M_finish = newFinish;
}
