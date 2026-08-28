// cl: /DNDEBUG /MD /EHsc

// Drawable::replaceModelConditionState, retail 0x0041CCD0 (323 bytes).
//
// This is the BFME-specific dirty-state path used by Object::
// notifyModelConditionChanged.  The three condition arrays are laid out as
// ten 32-bit words; spelling them out here keeps this TU independent from the
// reference BitFlags implementation while retaining the retail member
// offsets.

typedef unsigned int UnsignedInt;
typedef bool Bool;

class ModelConditionFlags
{
public:
	UnsignedInt m_bits[ 10 ];

	void clearAndSet( const ModelConditionFlags &clear,
		const ModelConditionFlags &set );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void audioAnchor00();
	virtual void audioAnchor04();
	virtual void audioAnchor08();
	virtual void audioAnchor0C();
	virtual void audioAnchor10();
	virtual void audioAnchor14();
	virtual void audioAnchor18();
	virtual void audioAnchor1C();
	virtual void audioAnchor20();
	virtual void audioAnchor24();
	virtual void audioAnchor28();
	virtual void audioAnchor2C();
	virtual void audioAnchor30();
	virtual void audioAnchor34();
	virtual void audioAnchor38();
	virtual void audioAnchor3C();
	virtual void audioAnchor40();
	virtual void audioAnchor44();
	virtual void audioAnchor48();
	virtual void removeAudioEvent( UnsignedInt event );
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class ObjectDrawInterface
{
public:
	virtual void objectDrawAnchor00();
	virtual void objectDrawAnchor04();
	virtual void objectDrawAnchor08();
	virtual void objectDrawAnchor0C();
	virtual void objectDrawAnchor10();
	virtual void objectDrawAnchor14();
	virtual void objectDrawAnchor18();
	virtual void objectDrawAnchor1C();
	virtual void objectDrawAnchor20();
	virtual void objectDrawAnchor24();
	virtual void objectDrawAnchor28();
	virtual void objectDrawAnchor2C();
	virtual void objectDrawAnchor30();
	virtual void objectDrawAnchor34();
	virtual void objectDrawAnchor38();
	virtual void objectDrawAnchor3C();
	virtual void objectDrawAnchor40();
	virtual void objectDrawAnchor44();
	virtual void objectDrawAnchor48();
	virtual void replaceModelConditionState( const ModelConditionFlags &flags,
		Bool force, UnsignedInt value );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class DrawModule
{
public:
	virtual void drawModuleAnchor00();
	virtual void drawModuleAnchor04();
	virtual void drawModuleAnchor08();
	virtual void drawModuleAnchor0C();
	virtual void drawModuleAnchor10();
	virtual void drawModuleAnchor14();
	virtual void drawModuleAnchor18();
	virtual void drawModuleAnchor1C();
	virtual void drawModuleAnchor20();
	virtual void drawModuleAnchor24();
	virtual void drawModuleAnchor28();
	virtual void drawModuleAnchor2C();
	virtual void drawModuleAnchor30();
	virtual void drawModuleAnchor34();
	virtual void drawModuleAnchor38();
	virtual void drawModuleAnchor3C();
	virtual void drawModuleAnchor40();
	virtual void drawModuleAnchor44();
	virtual void drawModuleAnchor48();
	virtual void drawModuleAnchor4C();
	virtual void drawModuleAnchor50();
	virtual void drawModuleAnchor54();
	virtual void drawModuleAnchor58();
	virtual void drawModuleAnchor5C();
	virtual void drawModuleAnchor60();
	virtual void drawModuleAnchor64();
	virtual void drawModuleAnchor68();
	virtual void drawModuleAnchor6C();
	virtual void drawModuleAnchor70();
	virtual void drawModuleAnchor74();
	virtual void drawModuleAnchor78();
	virtual void drawModuleAnchor7C();
	virtual void drawModuleAnchor80();
	virtual void drawModuleAnchor84();
	virtual void drawModuleAnchor88();
	virtual void drawModuleAnchor8C();
	virtual void drawModuleAnchor90();
	virtual void drawModuleAnchor94();
	virtual void drawModuleAnchor98();
	virtual ObjectDrawInterface *getObjectDrawInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class DynamicAudioEventRTS
{
public:
	unsigned char m_unmodelled_00[ 0x10 ];
	UnsignedInt m_playingHandle;
};

class DrawableBase
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public DrawableBase
{
public:
	void replaceModelConditionState( const ModelConditionFlags &flags,
		UnsignedInt a, UnsignedInt b );

private:
	// This no-argument member is the retail callee reached through ILT
	// 0x0002E564.  Its identity is not present in the surviving symbols.
	void refreshAmbientSound();

	unsigned char m_unmodelled_000[ 0x140 ];
	unsigned char m_flag140;
	unsigned char m_flag141;
	unsigned char m_unmodelled_142[ 0xA ];
	DynamicAudioEventRTS *m_ambientSound; // +0x14C
	DrawModule **m_drawModules; // +0x150
	unsigned char m_unmodelled_154[ 0xFC ];
	ModelConditionFlags m_conditionState; // +0x250
	ModelConditionFlags m_clearMask; // +0x278
	ModelConditionFlags m_setMask; // +0x2A0
	unsigned char m_unmodelled_2C8[ 0xEB ];
	Bool m_isModelDirty; // +0x3B3
};

// ?replaceModelConditionState@Drawable@@QAEXABVModelConditionFlags@@II@Z
void Drawable::replaceModelConditionState( const ModelConditionFlags &flags,
	UnsignedInt a, UnsignedInt b )
{
	register Drawable *self = this;
	register UnsignedInt *state;
	ModelConditionFlags newFlags = flags;
	UnsignedInt i = 0;

	for( ; i < 10; ++i )
	{
		if( self->m_setMask.m_bits[ i ] != 0 )
			goto apply_masks;
	}
	for( i = 0; i < 10; ++i )
	{
		if( self->m_clearMask.m_bits[ i ] != 0 )
			goto apply_masks;
	}
	goto masks_done;

apply_masks:
	newFlags.clearAndSet( self->m_clearMask, self->m_setMask );

masks_done:
	if( (unsigned char)a == 0 )
	{
		for( i = 0; i < 10; ++i )
		{
			if( self->m_conditionState.m_bits[ i ] != newFlags.m_bits[ i ] )
				goto flags_changed;
		}
		return;
	}

flags_changed:
	if( (newFlags.m_bits[ 4 ] & 0x80000) != 0 )
	{
		if( (self->m_conditionState.m_bits[ 4 ] & 0x80000) == 0 &&
			self->m_flag141 != 0 && self->m_flag140 != 0 )
		{
			self->refreshAmbientSound();
		}
	}
	else if( (self->m_conditionState.m_bits[ 4 ] & 0x80000) != 0 )
	{
		if( self->m_ambientSound != 0 )
		{
			TheAudio->removeAudioEvent( self->m_ambientSound->m_playingHandle );
		}
	}

	self->m_conditionState = newFlags;

	if( (unsigned char)a == 1 )
		goto update_modules;
	goto mark_dirty;

update_modules:
	state = self->m_conditionState.m_bits;
	for( DrawModule **dm = self->m_drawModules; *dm != 0; ++dm )
	{
		ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();
		if( di != 0 )
			di->replaceModelConditionState( *(ModelConditionFlags *)state, true, b );
	}
	self->m_isModelDirty = false;
	return;

mark_dirty:
	self->m_isModelDirty = true;
}
