// cl: /DNDEBUG /MD /EHsc
// readable body of ?onContaining@OpenContain@@: Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp
// Open-BFME: OpenContain::onContaining, retail 0x00221720, 154 bytes.
//
// The reference's body with one BFME change: the enter sound is fetched by
// INDEX from the template -- getSound(101) -- rather than through a named
// getSoundEnter(), and that getter falls back to the no-sound event when the
// index has none.
//
// The shape worth keeping is the negative offset. onContaining is a virtual of
// the contain interface, which sits at +0x20 inside the module, so `this' points
// there and getObject() reads the module's object at this-0x18 -- module+0x08,
// the same slot ProneUpdate's getObject() uses. m_loadSoundsEnabled is at
// this+0x95, module+0xB5.
//
// getTemplate() is vtable slot 10 (+0x28) on the object and is called twice: once
// for the guard and once for the sound, because a virtual call is not CSEd.

typedef int Int;
typedef bool Bool;
typedef unsigned int ObjectID;

enum { BFME_SOUND_ENTER = 101 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &src);		// ILT 0x00047B27
	~AudioEventRTS();					// ILT 0x00026F35

	void setObjectID(ObjectID id);				// ILT 0x00019A6A

private:
	unsigned char m_unmodelled_000[0x70];			// sizeof
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;		// ILT 0x0001BFD1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual const ThingTemplate *getTemplate(void) const;	// vtable +0x28

	ObjectID getID(void) const { return m_id; }

private:
	unsigned char m_unmodelled_004[0x74 - 0x04];
	ObjectID m_id;						// Object+0x74
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual void unusedSlot10();
	virtual void unusedSlot11();
	virtual void unusedSlot12();
	virtual void unusedSlot13();
	virtual void unusedSlot14();
	virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void addAudioEvent(const AudioEventRTS *event);	// vtable +0x44
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void onContaining(Object *rider, Bool wasSelected) = 0;
};

class OpenContain : public ContainModuleInterface
{
public:
	virtual void onContaining(Object *rider, Bool wasSelected);

private:
	// The interface subobject sits at +0x20 inside the module, so `this' points
	// there and everything the body touches is addressed from it: the module's
	// object at this-0x18, which is module+0x08 -- the same slot ProneUpdate's
	// getObject() reads -- and the flag at this+0x95, module+0xB5.
	Object *getObject(void) const { return *(Object **)((const char *)this - 0x18); }

	unsigned char m_unmodelled_004[0x95 - 0x04];
	Bool m_loadSoundsEnabled;				// this+0x95, module+0xB5
};

void OpenContain::onContaining( Object *rider, Bool wasSelected )
{
	// Play audio
	if( m_loadSoundsEnabled )
	{
		if( getObject()->getTemplate() )
		{
			const ThingTemplate *tmpl = getObject()->getTemplate();
			AudioEventRTS enterSound = *tmpl->getSound( BFME_SOUND_ENTER );
			enterSound.setObjectID(getObject()->getID());
			TheAudio->addAudioEvent(&enterSound);
		}
	}
}
