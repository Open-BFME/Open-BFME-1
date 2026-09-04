// cl: /DNDEBUG /MD /EHs-c-
// BFME Drawable ambient-info assignment, retail 0x0041AD20.
//
// This build has a ref-counted DynamicAudioEventInfo holder at +0x10c.  The
// setter receives the address of the incoming holder, so the self-assignment
// check compares that address with the member slot itself.

typedef unsigned int UnsignedInt;
typedef long RefCount;

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile *value );
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile *value );

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
	UnsignedInt m_handle;
};

class ObjectDrawInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c();
	virtual void *getAmbientValue();
};

class Object
{
public:
	unsigned char m_head[ 0x200 ];
	ObjectDrawInterface *m_drawInterface;
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

class Drawable
{
public:
	void setCustomSoundAmbientInfo( DynamicAudioEventInfo **customAmbientInfo );
	void startAmbientSound();
	void emitAmbientValue( void *value, void *param );

private:
	unsigned char m_head[ 0xfc ];
	Object *m_object;
	unsigned char m_gap100[ 0x0c ];
	DynamicAudioEventInfo *m_customSoundAmbientInfo;
	unsigned char m_gap110[ 0x30 ];
	unsigned char m_ambientSoundEnabled;
	unsigned char m_ambientSoundEnabledFromScript;
	unsigned char m_gap142;
	unsigned char m_ambientSoundPermanent;
	BfmeAudioSlot *m_ambientSound;
	BfmeAudioSlot *m_ambientSoundAlternate;
};

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

	if ( m_ambientSoundEnabled && m_ambientSoundEnabledFromScript && m_ambientSoundPermanent )
	{
		reinterpret_cast<Gen_00417cb0 *>( this )->alt();

		Object *object = m_object;
		void *value = 0;
		if ( object )
			value = object->m_drawInterface->getAmbientValue();
		reinterpret_cast<Gen_00417cb0 *>( this )->bfmeEmit( value, 0 );
	}
}
