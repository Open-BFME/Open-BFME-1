// cl: /DNDEBUG /MD /EHs-c-

// The two BFME Drawable bodies built without unwind support:
//
//   setCustomSoundAmbientInfo  0x0041AD20  239 B  QAE (public)
//   drawCaption                0x00420150  415 B  AAE (private)
//
// They have nothing in common to look at -- one swaps a ref-counted audio
// info holder, the other draws a name plate over a unit -- and everything in
// common to declare. Both walk out through the object pointer at Drawable+0xFC
// and each described the head in front of it as one anonymous run, then
// described a different Object from its own call outwards: one knew the
// geometry pointer at +0x108, the other the draw interface at +0x200. Neither
// contradicts the other, and now neither has to be read alone.
//
// The merged Drawable head is what the two statements make together:
//
//   +0x004 m_template            +0x140 ambient sound enabled
//   +0x0fc m_object              +0x141 ... and enabled from script
//   +0x10c custom ambient info   +0x143 ... and permanent
//   +0x2d0 caption display       +0x144 ambient sound, +0x148 its alternate
//
// Two of those names are contested by DrawableBFME.cpp, which reads the same
// bytes in a different body: it calls +0x143 m_selected and +0x148
// m_damagedAmbientSound. Nothing here settles that -- both TUs match with
// their own naming, and the fields are only ever read as gates -- so this file
// keeps the names its own bodies' evidence gave them and says where the other
// reading lives.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef unsigned int Color;
typedef float Real;
typedef bool Bool;
typedef long RefCount;

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile *value );
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile *value );

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct Rva0087DC00Vec
{
	Real x;
	Real y;
	Real z;
};

class Rva0087DC00
{
	UnsignedByte m_pad[ 0x18 ];
	Rva0087DC00Vec m_center;

public:
	void get( Rva0087DC00Vec *out );
};

class ThingTemplate
{
public:
	void *m_vtable;
	ThingTemplate *m_nextOverride;
	UnsignedByte m_pad008[ 0x58 ];
	Rva0087DC00 m_geometry;						// +0x60

	ThingTemplate *getFinalOverride();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18();
	// Slot 19, vtable+0x4c. No symbol is emitted for a call through it, so the
	// name is free: DrawableBFME.cpp and DrawableVisualState.cpp call the same
	// slot removeAudioEvent.
	virtual void stopAudioEvent( UnsignedInt handle );
};

extern AudioManager *TheAudio;

class DynamicAudioEventInfo
{
public:
	virtual ~DynamicAudioEventInfo();
	RefCount m_refCount;

	void releaseRef()
	{
		if ( InterlockedDecrement( &m_refCount ) <= 0 )
			delete this;
	}
};

class BfmeAudioSlot
{
public:
	unsigned char m_head[ 0x10 ];
	UnsignedInt m_handle;						// +0x10
};

class ObjectDrawInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c();
	virtual void *getAmbientValue();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	UnsignedByte m_pad000[ 0x108 ];
	Rva0087DC00 *m_geometry;					// +0x108
	UnsignedByte m_pad10c[ 0x200 - 0x10c ];
	ObjectDrawInterface *m_drawInterface;				// +0x200
};

// These two retail callees are already identified in the BFME ledger.  The
// setter reaches them through the same Drawable storage, so only their
// established names are needed here; their bodies stay in their own TUs.
class Gen_00417cb0
{
public:
	void alt();

private:
	friend class Drawable;
	void bfmeEmit( void *value, void *param );
};

#define BFME_CAPTION_DISPLAY_SLOT(n) virtual void slot##n();

class DisplayString
{
public:
	BFME_CAPTION_DISPLAY_SLOT(00) BFME_CAPTION_DISPLAY_SLOT(01)
	BFME_CAPTION_DISPLAY_SLOT(02) BFME_CAPTION_DISPLAY_SLOT(03)
	BFME_CAPTION_DISPLAY_SLOT(04) BFME_CAPTION_DISPLAY_SLOT(05)
	BFME_CAPTION_DISPLAY_SLOT(06) BFME_CAPTION_DISPLAY_SLOT(07)
	BFME_CAPTION_DISPLAY_SLOT(08) BFME_CAPTION_DISPLAY_SLOT(09)
	virtual void setColor( Color color, Color dropColor );
	BFME_CAPTION_DISPLAY_SLOT(11) BFME_CAPTION_DISPLAY_SLOT(12)
	BFME_CAPTION_DISPLAY_SLOT(13)
	virtual void draw( Int x, Int y, Int scaleX, Int scaleY );
	virtual void getSize( Int *width, Int *height );
	virtual Int getWidth( Int line );
};

class Display
{
public:
	BFME_CAPTION_DISPLAY_SLOT(00) BFME_CAPTION_DISPLAY_SLOT(01)
	BFME_CAPTION_DISPLAY_SLOT(02) BFME_CAPTION_DISPLAY_SLOT(03)
	BFME_CAPTION_DISPLAY_SLOT(04) BFME_CAPTION_DISPLAY_SLOT(05)
	BFME_CAPTION_DISPLAY_SLOT(06) BFME_CAPTION_DISPLAY_SLOT(07)
	BFME_CAPTION_DISPLAY_SLOT(08) BFME_CAPTION_DISPLAY_SLOT(09)
	BFME_CAPTION_DISPLAY_SLOT(10) BFME_CAPTION_DISPLAY_SLOT(11)
	BFME_CAPTION_DISPLAY_SLOT(12) BFME_CAPTION_DISPLAY_SLOT(13)
	BFME_CAPTION_DISPLAY_SLOT(14) BFME_CAPTION_DISPLAY_SLOT(15)
	BFME_CAPTION_DISPLAY_SLOT(16) BFME_CAPTION_DISPLAY_SLOT(17)
	BFME_CAPTION_DISPLAY_SLOT(18) BFME_CAPTION_DISPLAY_SLOT(19)
	BFME_CAPTION_DISPLAY_SLOT(20) BFME_CAPTION_DISPLAY_SLOT(21)
	BFME_CAPTION_DISPLAY_SLOT(22) BFME_CAPTION_DISPLAY_SLOT(23)
	BFME_CAPTION_DISPLAY_SLOT(24) BFME_CAPTION_DISPLAY_SLOT(25)
	BFME_CAPTION_DISPLAY_SLOT(26) BFME_CAPTION_DISPLAY_SLOT(27)
	BFME_CAPTION_DISPLAY_SLOT(28) BFME_CAPTION_DISPLAY_SLOT(29)
	BFME_CAPTION_DISPLAY_SLOT(30) BFME_CAPTION_DISPLAY_SLOT(31)
	BFME_CAPTION_DISPLAY_SLOT(32) BFME_CAPTION_DISPLAY_SLOT(33)
	BFME_CAPTION_DISPLAY_SLOT(34) BFME_CAPTION_DISPLAY_SLOT(35)
	BFME_CAPTION_DISPLAY_SLOT(36) BFME_CAPTION_DISPLAY_SLOT(37)
	BFME_CAPTION_DISPLAY_SLOT(38) BFME_CAPTION_DISPLAY_SLOT(39)
	BFME_CAPTION_DISPLAY_SLOT(40) BFME_CAPTION_DISPLAY_SLOT(41)
	BFME_CAPTION_DISPLAY_SLOT(42) BFME_CAPTION_DISPLAY_SLOT(43)
	BFME_CAPTION_DISPLAY_SLOT(44) BFME_CAPTION_DISPLAY_SLOT(45)
	BFME_CAPTION_DISPLAY_SLOT(46)
	virtual void drawOpenRect( Real x, Real y, Real width, Real height,
		Real lineWidth, Color color );
	virtual void drawFillRect( Real x, Real y, Real width, Real height,
		Color color );
};

class TacticalView
{
public:
#define BFME_CAPTION_VIEW_SLOT(n) virtual void slot##n();
	BFME_CAPTION_VIEW_SLOT(00) BFME_CAPTION_VIEW_SLOT(01)
	BFME_CAPTION_VIEW_SLOT(02) BFME_CAPTION_VIEW_SLOT(03)
	BFME_CAPTION_VIEW_SLOT(04) BFME_CAPTION_VIEW_SLOT(05)
	BFME_CAPTION_VIEW_SLOT(06) BFME_CAPTION_VIEW_SLOT(07)
	BFME_CAPTION_VIEW_SLOT(08) BFME_CAPTION_VIEW_SLOT(09)
	BFME_CAPTION_VIEW_SLOT(10) BFME_CAPTION_VIEW_SLOT(11)
	BFME_CAPTION_VIEW_SLOT(12) BFME_CAPTION_VIEW_SLOT(13)
	BFME_CAPTION_VIEW_SLOT(14) BFME_CAPTION_VIEW_SLOT(15)
	BFME_CAPTION_VIEW_SLOT(16) BFME_CAPTION_VIEW_SLOT(17)
	BFME_CAPTION_VIEW_SLOT(18) BFME_CAPTION_VIEW_SLOT(19)
	BFME_CAPTION_VIEW_SLOT(20) BFME_CAPTION_VIEW_SLOT(21)
	BFME_CAPTION_VIEW_SLOT(22) BFME_CAPTION_VIEW_SLOT(23)
	BFME_CAPTION_VIEW_SLOT(24) BFME_CAPTION_VIEW_SLOT(25)
	BFME_CAPTION_VIEW_SLOT(26) BFME_CAPTION_VIEW_SLOT(27)
	BFME_CAPTION_VIEW_SLOT(28) BFME_CAPTION_VIEW_SLOT(29)
	BFME_CAPTION_VIEW_SLOT(30) BFME_CAPTION_VIEW_SLOT(31)
	BFME_CAPTION_VIEW_SLOT(32) BFME_CAPTION_VIEW_SLOT(33)
	BFME_CAPTION_VIEW_SLOT(34) BFME_CAPTION_VIEW_SLOT(35)
	BFME_CAPTION_VIEW_SLOT(36) BFME_CAPTION_VIEW_SLOT(37)
	BFME_CAPTION_VIEW_SLOT(38) BFME_CAPTION_VIEW_SLOT(39)
	BFME_CAPTION_VIEW_SLOT(40) BFME_CAPTION_VIEW_SLOT(41)
	BFME_CAPTION_VIEW_SLOT(42) BFME_CAPTION_VIEW_SLOT(43)
	BFME_CAPTION_VIEW_SLOT(44) BFME_CAPTION_VIEW_SLOT(45)
	BFME_CAPTION_VIEW_SLOT(46) BFME_CAPTION_VIEW_SLOT(47)
	BFME_CAPTION_VIEW_SLOT(48) BFME_CAPTION_VIEW_SLOT(49)
	BFME_CAPTION_VIEW_SLOT(50) BFME_CAPTION_VIEW_SLOT(51)
	BFME_CAPTION_VIEW_SLOT(52) BFME_CAPTION_VIEW_SLOT(53)
	BFME_CAPTION_VIEW_SLOT(54) BFME_CAPTION_VIEW_SLOT(55)
	BFME_CAPTION_VIEW_SLOT(56) BFME_CAPTION_VIEW_SLOT(57)
	BFME_CAPTION_VIEW_SLOT(58) BFME_CAPTION_VIEW_SLOT(59)
	BFME_CAPTION_VIEW_SLOT(60) BFME_CAPTION_VIEW_SLOT(61)
	BFME_CAPTION_VIEW_SLOT(62) BFME_CAPTION_VIEW_SLOT(63)
	BFME_CAPTION_VIEW_SLOT(64) BFME_CAPTION_VIEW_SLOT(65)
	BFME_CAPTION_VIEW_SLOT(66) BFME_CAPTION_VIEW_SLOT(67)
	BFME_CAPTION_VIEW_SLOT(68) BFME_CAPTION_VIEW_SLOT(69)
	BFME_CAPTION_VIEW_SLOT(70) BFME_CAPTION_VIEW_SLOT(71)
	BFME_CAPTION_VIEW_SLOT(72) BFME_CAPTION_VIEW_SLOT(73)
	BFME_CAPTION_VIEW_SLOT(74) BFME_CAPTION_VIEW_SLOT(75)
	BFME_CAPTION_VIEW_SLOT(76) BFME_CAPTION_VIEW_SLOT(77)
	BFME_CAPTION_VIEW_SLOT(78) BFME_CAPTION_VIEW_SLOT(79)
	BFME_CAPTION_VIEW_SLOT(80) BFME_CAPTION_VIEW_SLOT(81)
	BFME_CAPTION_VIEW_SLOT(82) BFME_CAPTION_VIEW_SLOT(83)
	BFME_CAPTION_VIEW_SLOT(84) BFME_CAPTION_VIEW_SLOT(85)
	BFME_CAPTION_VIEW_SLOT(86)
#undef BFME_CAPTION_VIEW_SLOT
	virtual Bool worldToScreen( Coord3D *world, ICoord2D *screen );
};

class InGameUI
{
	UnsignedByte m_pad[ 0x7d0 ];

public:
	Color m_drawableCaptionColor;
};

extern Display *TheDisplay;
extern TacticalView *TheTacticalView;
extern InGameUI *TheInGameUI;
extern void j_0003ee55();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void setCustomSoundAmbientInfo( DynamicAudioEventInfo **customAmbientInfo );
	void startAmbientSound();
	void emitAmbientValue( void *value, void *param );

private:
	void drawCaption();

	UnsignedByte m_pad000[ 4 ];
	ThingTemplate *m_template;					// +0x004
	UnsignedByte m_pad008[ 0xfc - 8 ];
	Object *m_object;						// +0x0fc
	UnsignedByte m_pad100[ 0x0c ];
	DynamicAudioEventInfo *m_customSoundAmbientInfo;		// +0x10c
	UnsignedByte m_pad110[ 0x30 ];
	UnsignedByte m_secondMaterialPassOpacity;				// +0x140
	UnsignedByte m_ambientSoundEnabledFromScript;			// +0x141
	UnsignedByte m_gap142;
	UnsignedByte m_ambientSoundPermanent;				// +0x143
	BfmeAudioSlot *m_ambientSound;					// +0x144
	BfmeAudioSlot *m_ambientSoundAlternate;				// +0x148
	UnsignedByte m_pad14c[ 0x2d0 - 0x14c ];
	DisplayString *m_captionDisplayString;				// +0x2d0
};

// ?setCustomSoundAmbientInfo@Drawable@@QAEXPAPAVDynamicAudioEventInfo@@@Z
// Retail 0x0041AD20, 239 bytes. This build has a ref-counted holder at
// +0x10c, and the setter receives the ADDRESS of the incoming holder, so the
// self-assignment check compares that address with the member slot itself.
void Drawable::setCustomSoundAmbientInfo( DynamicAudioEventInfo **customAmbientInfo )
{
	if ( m_ambientSound )
		TheAudio->stopAudioEvent( m_ambientSound->m_handle );
	if ( m_ambientSoundAlternate )
		TheAudio->stopAudioEvent( m_ambientSoundAlternate->m_handle );

	DynamicAudioEventInfo **slot = &m_customSoundAmbientInfo;
	if ( *slot )
	{
		(*slot)->releaseRef();
		*slot = 0;
	}

	if ( slot != customAmbientInfo )
	{
		DynamicAudioEventInfo *newInfo = *customAmbientInfo;
		if ( newInfo )
			InterlockedIncrement( &newInfo->m_refCount );

		if ( *slot )
			(*slot)->releaseRef();
		*slot = *customAmbientInfo;
	}

	if ( m_secondMaterialPassOpacity && m_ambientSoundEnabledFromScript && m_ambientSoundPermanent )
	{
		reinterpret_cast<Gen_00417cb0 *>( this )->alt();

		Object *object = m_object;
		void *value = 0;
		if ( object )
			value = object->m_drawInterface->getAmbientValue();
		reinterpret_cast<Gen_00417cb0 *>( this )->bfmeEmit( value, 0 );
	}
}

// ?drawCaption@Drawable@@AAEXXZ
// Retail 0x00420150, 415 bytes. The name plate: take the geometry centre
// from the object if there is one and from the final template override if
// there is not, project it to the screen, and draw the filled and open rects
// behind the text.
void Drawable::drawCaption()
{
	if ( m_captionDisplayString == 0 )
		return;

	ICoord2D screen;
	Coord3D center;
	register Object *object = m_object;
	Rva0087DC00 *geometry;
	if ( object != 0 )
	{
		geometry = object->m_geometry;
	}
	else
	{
		ThingTemplate *drawableTemplate = m_template;
		if ( drawableTemplate != 0 && drawableTemplate->m_nextOverride != 0 )
			drawableTemplate = drawableTemplate->m_nextOverride->getFinalOverride();
		geometry = &drawableTemplate->m_geometry;
	}

	geometry->get( (Rva0087DC00Vec *)&center );
	typedef const Coord3D *(__fastcall *PositionCall)( Drawable * );
	const Coord3D *position = ((PositionCall)j_0003ee55)( this );
	center.x += position->x;
	center.y += position->y;
	center.z += position->z;

	TheTacticalView->worldToScreen( &center, &screen );
	screen.x -= m_captionDisplayString->getWidth( -1 ) / 2;

	Int width, xPos;
	Int height, yPos;
	m_captionDisplayString->getSize( &width, &height );
	xPos = screen.x - 1;
	yPos = screen.y - 1;
	TheDisplay->drawFillRect( xPos, yPos,
		width + 2, height + 2, 0x7d000000 );
	TheDisplay->drawOpenRect( xPos, yPos,
		width + 2, height + 2, 1.0f, 0xff141414 );

	m_captionDisplayString->setColor( TheInGameUI->m_drawableCaptionColor, 0xff000000 );
	m_captionDisplayString->draw( screen.x, screen.y, 1, 1 );
}
