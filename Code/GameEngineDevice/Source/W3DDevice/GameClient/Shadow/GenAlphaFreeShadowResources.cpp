// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x007BD0C0, 19 bytes, two calls and nothing else:
//
//   mov ecx, [ecx + 8]      -- a manager held at +0x08
//   call ILT 0x00002365     -- W3DShadowGeometryManager::Free_All_Geoms
//   mov ecx, [TheW3DBufferManager]
//   jmp ILT 0x00023349      -- W3DBufferManager::freeAllBuffers
//
// The second call is a tail jump, so it is the last statement in the body.
// Its ILT is only known by address (?j_00023349@@YAXXZ), so freeAllBuffers is
// pinned there alongside the row that holds its body at 0x007ADAD0.
//
// The name is address-derived: reverse/reloc_names.csv carries it as
// h00044062@GenAlpha with identity=real but no decoded spelling.

class W3DShadowGeometryManager
{
public:
	void Free_All_Geoms(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DBufferManager.h
class W3DBufferManager
{
public:
	void freeAllBuffers(void);
};

extern W3DBufferManager *TheW3DBufferManager;

class GenAlpha
{
public:
	void h00044062(void);

private:
	char m_bfmeHead[0x08];
	W3DShadowGeometryManager *m_bfmeGeometryManager;	// +0x08
};

// ?h00044062@GenAlpha@@QAEXXZ
void GenAlpha::h00044062(void)
{
	m_bfmeGeometryManager->Free_All_Geoms();
	TheW3DBufferManager->freeAllBuffers();
}
