// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?setFullyObscuredByShroud@W3DTankTruckDraw@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDraw.cpp
// Open-BFME5: W3DTankTruckDraw::setFullyObscuredByShroud, retail 0x007815E0,
// zh_sweep packet 007815e0.
//
// The reference body unchanged. One offset separated it from retail:
// getFullyObscuredByShroud() inlines to a read of [this+0x2D], where the
// vendored W3DModelDraw puts the flag at +0x4D. Its own TU rather than moving
// that member under W3DTankTruckDraw.cpp's other rows.
//
// Three callees, each resolved through its ILT and pinned: tossEmitters at
// 0x00034A59, createEmitters at 0x0001ECCC, and the base
// W3DModelDraw::setFullyObscuredByShroud at 0x0003EF77, which is called from
// both arms -- the qualified call is not virtual, so it is a direct call in
// each tail.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDraw
{
public:
	virtual void setFullyObscuredByShroud( Bool fullyObscured );	///< ILT 0x0003EF77

	Bool getFullyObscuredByShroud( void ) const { return m_fullyObscuredByShroud; }

protected:
	unsigned char m_unreconstructed_04[0x2D - 4];					///< vptr at +0x00
	Bool m_fullyObscuredByShroud;									///< +0x2D
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTankTruckDraw.h
class W3DTankTruckDraw : public W3DModelDraw
{
public:
	virtual void setFullyObscuredByShroud( Bool fullyObscured );

protected:
	void createEmitters( void );									///< ILT 0x0001ECCC
	void tossEmitters( void );										///< ILT 0x00034A59
};

//-------------------------------------------------------------------------------------------------
// ?setFullyObscuredByShroud@W3DTankTruckDraw@@UAEX_N@Z
void W3DTankTruckDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (fullyObscured != getFullyObscuredByShroud())
	{
		if (fullyObscured)
			tossEmitters();
		else
			createEmitters();
	}
	W3DModelDraw::setFullyObscuredByShroud(fullyObscured);
}
