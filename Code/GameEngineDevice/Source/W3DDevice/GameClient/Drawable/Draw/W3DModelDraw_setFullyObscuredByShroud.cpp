// cl: /DNDEBUG /MD /EHsc
// readable body of ?setFullyObscuredByShroud@W3DModelDraw@@UAEX_N@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp

// W3DModelDraw::setFullyObscuredByShroud, retail 0x007628C0.
//
// Nothing happens at all when the flag at +0x2D already holds the value asked
// for - the whole body is inside that test, including the call at the end.
//
// The two objects at +0x3C and +0x40 each carry the same flag at their own
// +0x05, and they are not written the same way: the first takes the argument
// and the second re-reads the member. That is one byte of difference in the
// source and three in the object, so it is written as retail has it rather
// than tidied into one variable.
//
// The trailing call is a plain call, not a tail jump, and passes nothing with
// `this' unchanged - a zero-argument member. It is unnamed in the image; the
// name it is pinned under here says what the call site uses it for.

typedef bool Bool;

class W3DModelDrawShroudSubObject
{
public:
	unsigned char m_unmodelled_00[5];
	Bool m_obscured;						// +0x05
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDraw
{
public:
	virtual void setFullyObscuredByShroud( Bool obscured );

private:
	void updateSubObjectsFromShroud( void );

	unsigned char m_unmodelled_04[ 0x2D - 4 ];
	Bool m_obscured;						// +0x2D
	unsigned char m_unmodelled_2E[ 0x3C - 0x2E ];
	W3DModelDrawShroudSubObject *m_first;	// +0x3C
	W3DModelDrawShroudSubObject *m_second;	// +0x40
};

// ?setFullyObscuredByShroud@W3DModelDraw@@UAEX_N@Z
void W3DModelDraw::setFullyObscuredByShroud( Bool obscured )
{
	if( m_obscured != obscured )
	{
		m_obscured = obscured;

		if( m_first )
			m_first->m_obscured = obscured;

		if( m_second )
			m_second->m_obscured = m_obscured;

		updateSubObjectsFromShroud();
	}
}
