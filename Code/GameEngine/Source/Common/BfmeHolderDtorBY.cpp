// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: a destructor at retail 0x0092A3D0, 90 bytes.  The body resets
// the holder before the eight-element array is torn down by the iterator.

class BfmeElemBY
{
public:
	~BfmeElemBY(void);

	void *m_bfmeSlotBY;
};

class BfmeHolderBY
{
public:
	~BfmeHolderBY(void);

	void bfmeResetBY(int first, int second, int third);

	char m_bfmePadBY[0x74];
	BfmeElemBY m_bfmeElemsBY[8];
};

BfmeHolderBY::~BfmeHolderBY(void)
{
	bfmeResetBY(0, 0, 0);
}

// The retail 30-byte wrapper is BfmeHolderBY's scalar-deleting destructor.
// Keep the delete expression separate from the matched body so MSVC emits
// its compiler-owned ??_G wrapper at the original address.
void Force_BfmeHolderBY_DeletingDestructor(BfmeHolderBY *value)
{
	delete value;
}
