// ?rva00412530@Drawable@@QAEXHPAXHPBURGBColor@@M@Z
// cl: /DNDEBUG /MD /EHsc
//
// Drawable's buff-effect state at this+0x3BC is a lazily allocated 0x1A0-byte
// helper: its constructor (retail 0x00045782) takes the owning Drawable, and
// its forward member (retail 0x0001FE38) takes the same five arguments this
// method receives. Identity comes from BuffNuggetFXNugget::doFXObj (retail
// 0x0042D460), whose partial stash names this exact mangled symbol here.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class Drawable;

class BfmeBuffFxState
{
public:
	BfmeBuffFxState( Drawable *owner );
	void bfmeForward( Int buffType, void *templateObject, Int count,
		const RGBColor *color, Real extrusion );

private:
	unsigned char m_bfmeBody[0x1A0];
};

class Drawable
{
public:
	void rva00412530( Int buffType, void *templateObject, Int count,
		const RGBColor *color, Real extrusion );

private:
	unsigned char m_bfmeHead[0x3BC];
	BfmeBuffFxState *m_bfmeBuffFxState;				// +0x3bc
};

// ?rva00412530@Drawable@@QAEXHPAXHPBURGBColor@@M@Z
void Drawable::rva00412530( Int buffType, void *templateObject, Int count,
	const RGBColor *color, Real extrusion )
{
	if( m_bfmeBuffFxState == 0 )
		m_bfmeBuffFxState = new BfmeBuffFxState( this );

	m_bfmeBuffFxState->bfmeForward( buffType, templateObject, count, color, extrusion );
}
