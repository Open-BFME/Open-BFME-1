// ?rva00412530@Drawable@@QAEXHPAXHPBURGBColor@@M@Z
// cl: /DNDEBUG /MD /EHsc
//
// Drawable's buff-effect state at this+0x3BC is a lazily allocated 0x1A0-byte
// helper. Its allocation site calls the already-matched retail bodies
// ??0BuffManager@@QAE@H@Z (retail 0x0040AF50) and
// ?apply@BuffState00409E20@@QAEXHPAXHPBXM@Z (retail 0x00409E20) through the
// incremental-link ILT entries at 0x00045782 and 0x0001FE38; both callees are
// 0x1A0-byte layouts taking the same five 4-byte slots this method receives,
// so the calls respell here with no code change. Identity comes from
// BuffNuggetFXNugget::doFXObj (retail 0x0042D460), whose partial stash names
// this method's own mangled symbol here.

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

class BuffManager
{
public:
	BuffManager( int mode );

private:
	unsigned char m_body[0x1A0];
};

struct BuffState00409E20
{
	void apply( Int type, void *arg, Int count, const void *color,
		Real extrusion );
};

class Drawable
{
public:
	void rva00412530( Int buffType, void *templateObject, Int count,
		const RGBColor *color, Real extrusion );

private:
	unsigned char m_bfmeHead[0x3BC];
	BuffManager *m_bfmeBuffFxState;				// +0x3bc
};

// ?rva00412530@Drawable@@QAEXHPAXHPBURGBColor@@M@Z
void Drawable::rva00412530( Int buffType, void *templateObject, Int count,
	const RGBColor *color, Real extrusion )
{
	if( m_bfmeBuffFxState == 0 )
		m_bfmeBuffFxState = (BuffManager *)new BuffManager( (int)this );

	((BuffState00409E20 *)m_bfmeBuffFxState)->apply( buffType, templateObject, count, color, extrusion );
}
