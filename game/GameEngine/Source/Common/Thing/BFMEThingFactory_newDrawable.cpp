// cl: /DNDEBUG /MD /EHsc

// BFMEThingFactory::newDrawable, retail 0x001330E0. A null template is answered
// with the null it was given - retail returns the argument register rather than
// clearing one - and anything else is forwarded whole to the object at
// 0x012F1464 through its virtual slot +0x5C.
//
// The class name is this tree's, from reloc_names; only the forwarding is
// claimed here.

typedef int Int;

class Drawable;
class ThingTemplate;

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

class BFMEDrawableFactory
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_38() = 0;
	virtual void _bfme_pad_3C() = 0;
	virtual void _bfme_pad_40() = 0;
	virtual void _bfme_pad_44() = 0;
	virtual void _bfme_pad_48() = 0;
	virtual void _bfme_pad_4C() = 0;
	virtual void _bfme_pad_50() = 0;
	virtual void _bfme_pad_54() = 0;
	virtual void _bfme_pad_58() = 0;
	virtual Drawable *createDrawable( const ThingTemplate *t, DrawableStatus s, Int i ) = 0;	// +0x5C
};

extern BFMEDrawableFactory *TheBFMEDrawableFactory;		// 0x012F1464

class BFMEThingFactory
{
public:
	Drawable *newDrawable( const ThingTemplate *t, DrawableStatus s, Int i );
};

// ?newDrawable@BFMEThingFactory@@QAEPAVDrawable@@PBVThingTemplate@@W4DrawableStatus@@H@Z
Drawable *BFMEThingFactory::newDrawable( const ThingTemplate *t, DrawableStatus s, Int i )
{
	if( !t )
		return 0;

	return TheBFMEDrawableFactory->createDrawable( t, s, i );
}
