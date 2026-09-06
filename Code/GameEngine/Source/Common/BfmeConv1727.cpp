class BfmeRoomQR
{
public:
	BfmeRoomQR(const BfmeRoomQR &other);
	~BfmeRoomQR() throw() {}

	int m_bfmeHandleQR;
};

struct BfmeElemQR
{
	int m_bfmeAQR;
	int m_bfmeBQR;
	int m_bfmeCQR;
	BfmeRoomQR m_bfmeRoomQR;
};

void __cdecl bfmeDoQR(BfmeElemQR *slot, BfmeElemQR value, void *extra);

void __cdecl bfmeEachQR(BfmeElemQR *first, BfmeElemQR *last, int unused, void *extra)
{
	while (first != last)
	{
		bfmeDoQR(first, *first, extra);
		++first;
	}
}
