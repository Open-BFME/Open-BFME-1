// cl: /DNDEBUG /MD /EHsc
// readable body of ??0DrawableIconInfo@@QAE@XZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?clear@DrawableIconInfo@@QAEXXZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ??1DrawableIconInfo@@MAE@XZ: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?applyTint@Drawable@@QAEXURGBColor@@IIIMM@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?setShadowsEnabled@Drawable@@QAEX_N@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?setEmoticon@Drawable@@QAEXABVAsciiString@@H@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?setDrawableHidden@Drawable@@QAEX_N@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?replaceModelConditionState@Drawable@@QAEXABVModelConditionFlags@@II@Z: Code/GameEngine/Source/GameClient/Drawable.cpp

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class AsciiString;
class Anim2DTemplate;
class Anim2DCollection;

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

// upstream vocabulary: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
// The three condition arrays are ten 32-bit words each; spelling them out keeps
// this TU independent of the reference BitFlags implementation while retaining
// the retail member offsets.
class ModelConditionFlags
{
public:
	UnsignedInt m_bits[ 10 ];

	inline Bool any() const
	{
		for( UnsignedInt i = 0; i < 10; ++i )
		{
			if( m_bits[ i ] != 0 )
				return true;
		}
		return false;
	}

	inline Bool operator==( const ModelConditionFlags &that ) const
	{
		for( UnsignedInt i = 0; i < 10; ++i )
		{
			if( m_bits[ i ] != that.m_bits[ i ] )
				return false;
		}
		return true;
	}

	void clearAndSet( const ModelConditionFlags &clear,
		const ModelConditionFlags &set );
};

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *, Anim2DCollection *);
	virtual ~Anim2D();
	UnsignedInt getCurrentFrameWidth() const;
	UnsignedInt getCurrentFrameHeight() const;
	void draw(Int x, Int y, Int width, Int height);
	void deleteInstance() { delete this; }

private:
	unsigned char m_unmodelled[0x30];
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
	virtual void removeAudioEvent( UnsignedInt event );	// slot 19, vtable+0x4c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class ObjectDrawInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18();
	virtual void replaceModelConditionState( const ModelConditionFlags &flags,
		Bool force, UnsignedInt value );		// slot 19, vtable+0x4c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual void setShadowsEnabled(Bool enable);		// slot 10, vtable+0x28
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void setHidden(Bool hidden);			// slot 32, vtable+0x80
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual ObjectDrawInterface *getObjectDrawInterface();	// slot 39, vtable+0x9c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class DynamicAudioEventRTS
{
public:
	unsigned char m_unmodelled_00[ 0x10 ];
	UnsignedInt m_playingHandle;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled[0x3C];
	UnsignedInt m_frame;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
// getIconInfo allocates 0x74 bytes including the vptr; emoticon fields are at +0x2C/+0x64.
enum { ICON_EMOTICON = 10 };

class DrawableIconInfo
{
public:
	DrawableIconInfo();
	__declspec(noinline) void clear();

	Anim2D *m_icon[14];
	UnsignedInt m_keepTillFrame[14];

	void killIcon(Int iconType)
	{
		if (m_icon[iconType])
		{
			m_icon[iconType]->deleteInstance();
			m_icon[iconType] = 0;
			m_keepTillFrame[iconType] = 0;
		}
	}

protected:
	virtual ~DrawableIconInfo();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	DrawableIconInfo *getIconInfo();
	void clearEmoticon() { if (m_iconInfo) killIcon(ICON_EMOTICON); }
	void killIcon(Int iconType) { if (m_iconInfo) m_iconInfo->killIcon(iconType); }

	void applyTint(RGBColor color, UnsignedInt preColorTime,
		UnsignedInt postColorTime, UnsignedInt sustainedColorTime,
		Real frequency, Real amplitude);
	void setShadowsEnabled(Bool enable);
	void setEmoticon(const AsciiString &name, Int duration);
	void setDrawableHidden(Bool hidden);
	void replaceModelConditionState( const ModelConditionFlags &flags,
		UnsignedInt forceReplace, UnsignedInt b );

private:
	void drawEmoticon();
	void updateHiddenStatus();
	// This no-argument member is the retail callee reached through ILT
	// 0x0002E564. Its identity is not present in the surviving symbols.
	void refreshAmbientSound();

	char m_pad000[0x6c];
	RGBColor m_tintColor;					// this+0x06c
	UnsignedInt m_preColorTime;				// this+0x078
	UnsignedInt m_postColorTime;				// this+0x07c
	UnsignedInt m_sustainedColorTime;			// this+0x080
	Real m_amplitude;					// this+0x084
	Real m_frequency;					// this+0x088
	char m_pad08c[0x110 - 0x08c];
	UnsignedInt m_status;					// this+0x110, bit 1 is shadows
	char m_pad114[0x140 - 0x114];
	unsigned char m_secondMaterialPassOpacity;				// this+0x140
	unsigned char m_flag141;				// this+0x141
	unsigned char m_pad142[0xA];
	DynamicAudioEventRTS *m_ambientSound;			// this+0x14c
	DrawModule **m_drawModules;				// this+0x150
	char m_pad154[0x250 - 0x154];
	ModelConditionFlags m_conditionState;			// this+0x250
	ModelConditionFlags m_clearMask;			// this+0x278
	ModelConditionFlags m_setMask;				// this+0x2a0
	char m_pad2c8[0x2E0 - 0x2c8];
	DrawableIconInfo *m_iconInfo;				// this+0x2e0
	char m_pad2E4[0x3B0 - 0x2E4];
	Bool m_hidden;						// this+0x3b0
	unsigned char m_pad3b1[2];
	Bool m_isModelDirty;					// this+0x3b3
	char m_pad3b4[0x3C4 - 0x3B4];
	Int m_emoticonRegionLeft;				// this+0x3c4
	char m_pad3c8[4];
	Int m_emoticonRegionRight;			// this+0x3cc
	Int m_emoticonRegionBottom;			// this+0x3d0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h
class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};

extern Anim2DCollection *TheAnim2DCollection;
extern GameLogic *TheGameLogic;
extern AudioManager *TheAudio;

// ?applyTint@Drawable@@QAEXURGBColor@@IIIMM@Z
// Retail 0x00412040, 70 bytes. Six stores and nothing else: the flash is
// driven from these fields by whoever draws next.
void Drawable::applyTint(RGBColor color, UnsignedInt preColorTime,
	UnsignedInt postColorTime, UnsignedInt sustainedColorTime,
	Real frequency, Real amplitude)
{
	m_tintColor = color;
	m_preColorTime = preColorTime;
	m_postColorTime = postColorTime;
	m_sustainedColorTime = sustainedColorTime;
	m_frequency = frequency;
	m_amplitude = amplitude;
}

// ?setShadowsEnabled@Drawable@@QAEX_N@Z
// Retail 0x004140E0, 69 bytes. The matched SlowDeathBehavior caller
// establishes the identity: set or clear bit 1 of the status word, then pass
// the flag down the draw-module array.
void Drawable::setShadowsEnabled(Bool enable)
{
	// Bound as a reference and loaded into a local before the walk, both
	// deliberately: retail stores the status word back before it loads the
	// module array, and folding either into its use swaps the two.
	UnsignedInt &status = m_status;
	if (enable)
		status |= 2;
	else
		status &= ~2;

	DrawModule **modules = m_drawModules;
	for (DrawModule **drawModule = modules; *drawModule; ++drawModule)
		(*drawModule)->setShadowsEnabled(enable);
}

// ?setEmoticon@Drawable@@QAEXABVAsciiString@@H@Z
// Retail 0x004149E0, 218 bytes. Negative durations use the distant frame
// sentinel 0x3FFFFFFF rather than a flag.
void Drawable::setEmoticon(const AsciiString &name, Int duration)
{
	clearEmoticon();
	Anim2DTemplate *animTemplate = TheAnim2DCollection->findTemplate(name);
	if (animTemplate)
	{
		if (getIconInfo()->m_icon[ICON_EMOTICON] == 0)
		{
			getIconInfo()->m_icon[ICON_EMOTICON] = new Anim2D(animTemplate, TheAnim2DCollection);
			getIconInfo()->m_keepTillFrame[ICON_EMOTICON] = duration >= 0 ? TheGameLogic->m_frame + duration : 0x3FFFFFFF;
		}
	}
}

// ?setDrawableHidden@Drawable@@QAEX_N@Z
// Retail 0x0041A230, 74 bytes. Every draw module is told, and only unhiding
// re-derives the status the other flags imply.
void Drawable::setDrawableHidden(Bool hidden)
{
	if (m_hidden != hidden)
	{
		for (DrawModule **module = m_drawModules; *module; ++module)
			(*module)->setHidden(hidden);

		m_hidden = hidden;
		if (!hidden)
			updateHiddenStatus();
	}
}

// ?replaceModelConditionState@Drawable@@QAEXABVModelConditionFlags@@II@Z
// Retail 0x0041CCD0, 323 bytes. The BFME-specific dirty-state path used by
// Object::notifyModelConditionChanged: fold in the pending masks, decide
// whether the ambient sound starts or stops on bit 0x80000 of word four, and
// either push the new state through every draw module now or mark the model
// dirty and let the next update do it.
void Drawable::replaceModelConditionState( const ModelConditionFlags &flags,
	UnsignedInt forceReplace, UnsignedInt b )
{
	ModelConditionFlags newFlags = flags;

	if( m_setMask.any() || m_clearMask.any() )
		newFlags.clearAndSet( m_clearMask, m_setMask );

	if( (unsigned char)forceReplace == 0 && m_conditionState == newFlags )
		return;

	if( (newFlags.m_bits[ 4 ] & 0x80000) != 0 )
	{
		if( (m_conditionState.m_bits[ 4 ] & 0x80000) == 0 &&
			m_flag141 != 0 && m_secondMaterialPassOpacity != 0 )
		{
			refreshAmbientSound();
		}
	}
	else if( (m_conditionState.m_bits[ 4 ] & 0x80000) != 0 )
	{
		if( m_ambientSound != 0 )
		{
			TheAudio->removeAudioEvent( m_ambientSound->m_playingHandle );
		}
	}

	m_conditionState = newFlags;

	if( (unsigned char)forceReplace == 1 )
	{
		for( DrawModule **drawModule = m_drawModules; *drawModule != 0; ++drawModule )
		{
			ObjectDrawInterface *drawInterface = (*drawModule)->getObjectDrawInterface();
			if( drawInterface != 0 )
				drawInterface->replaceModelConditionState( m_conditionState, true, b );
		}
		m_isModelDirty = false;
	}
	else
		m_isModelDirty = true;
}

// BFME releases unpooled icons through virtual delete; the pooled reference calls freeBlock.
DrawableIconInfo::DrawableIconInfo()
{
    for (int i = 0; i < 14; ++i) {
        m_icon[i] = 0;
        m_keepTillFrame[i] = 0;
    }
}
void DrawableIconInfo::clear()
{
    for (int i = 0; i < 14; ++i) {
        delete m_icon[i];
        m_icon[i] = 0;
        m_keepTillFrame[i] = 0;
    }
}
DrawableIconInfo::~DrawableIconInfo() { clear(); }

// The linker stub forwards ECX unchanged to the out-of-line clear body.
void __fastcall rva0000DBA7ClearIcons(DrawableIconInfo *icons) { icons->clear(); }

// BFME's dispatcher calls the no-argument Drawable::drawEmoticon body.
// ?drawEmoticon@Drawable@@AAEXXZ
void Drawable::drawEmoticon()
{
    if (m_iconInfo != 0 && getIconInfo()->m_icon[ICON_EMOTICON] != 0)
    {
        UnsignedInt now = TheGameLogic->m_frame;
        if (getIconInfo()->m_keepTillFrame[ICON_EMOTICON] >= now)
        {
            Int barWidth = m_emoticonRegionRight - m_emoticonRegionLeft;
            Int frameWidth = getIconInfo()->m_icon[ICON_EMOTICON]->getCurrentFrameWidth();
            Int frameHeight = getIconInfo()->m_icon[ICON_EMOTICON]->getCurrentFrameHeight();
            Int screenX = (Int)(m_emoticonRegionLeft + (barWidth * 0.5f) - (frameWidth * 0.5f));
            Int screenY = m_emoticonRegionBottom - frameHeight;
            getIconInfo()->m_icon[ICON_EMOTICON]->draw(screenX, screenY, frameWidth, frameHeight);
        }
        else
        {
            clearEmoticon();
        }
    }
}
