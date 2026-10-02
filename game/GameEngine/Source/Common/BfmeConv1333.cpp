// Open-BFME5 conversions.

// Retail frees this array through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);

// Retail passes the element destructor to the CRT array-dtor iterator as
// 0x00030652, the ILT thunk whose route is the matched owning texture-handle
// destructor BfmeHandleCX::~BfmeHandleCX at 0x0005CC00
// (game/Libraries/Source/WWVegas/WW3D2/TextureHandleDestructor.cpp), and the
// element size argument is 4, which is that handle's size. Spelling the
// element type with the ledger's defined name keeps the same DIR32 operand
// and gives the link a definition to bind.
class BfmeHandleCX
{
public:
	~BfmeHandleCX();
	char m_bfmePad[4];
};

class BfmeThingUHA
{
public:
	void bfmeClearUHA();
	void *m_bfmeVft;
	BfmeHandleCX *m_bfmeArray;
	int m_bfmeCount;
	char m_bfmePad;
	char m_bfmeOwned;
};

void BfmeThingUHA::bfmeClearUHA()
{
	if (m_bfmeArray && m_bfmeOwned) {
		delete [] m_bfmeArray;
		m_bfmeArray = 0;
	}
	m_bfmeOwned = 0;
	m_bfmeCount = 0;
}
