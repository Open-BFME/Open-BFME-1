// ?onRemoving@OpenContain@@UAEXPAVObject@@@Z
// partial score=0.2 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: OpenContain::onRemoving, retail 0x00227DC0, 525 bytes.
//
// The callback is the ContainModuleInterface secondary-base method.  Retail
// enters with that subobject in ECX; the owning OpenContain object is at
// `this - 0x20`, and its Object member is therefore at `this - 0x18`.
// OpenContain_onContaining.cpp proves the same receiver and Object ABI.
// CaveContain::onRemoving at 0x00219FA0 calls this qualified base method, and
// OpenContain's secondary vtable 0x010AC038 slot +0x48 reaches this body.

#define _STLP_USE_STATIC_LIB 1

typedef int Int;
typedef unsigned int ObjectID;
typedef bool Bool;

enum
{
	BFME_SOUND_EXIT = 0x66,
	BFME_SOUND_FALLING = 0x6A
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &src); // ILT 0x00047B27
	~AudioEventRTS(); // ILT 0x00026F35
	void setObjectID(ObjectID id); // ILT 0x00019A6A

private:
	unsigned char m_unmodelled[0x70];
};

class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const; // ILT 0x0001BFD1
};

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
	virtual const ThingTemplate *getTemplate() const; // vtable +0x28

	ObjectID getID() const { return m_id; }

private:
	unsigned char m_unmodelled[0x74 - 4];
	ObjectID m_id;
};

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
	virtual void addAudioEvent(const AudioEventRTS *event); // vtable +0x44
};

extern AudioManager *TheAudio;

class ContainModuleInterface
{
public:
	virtual void onRemoving(Object *obj) = 0;
};

class __declspec(novtable) OpenContain : public ContainModuleInterface
{
public:
	virtual void onRemoving(Object *obj);

private:
	Object *getObject() const
	{
		return *(Object **)((const char *)this - 0x18);
	}
};

void OpenContain::onRemoving(Object *rider)
{
	AudioEventRTS exitSound = *getObject()->getTemplate()->getSound(BFME_SOUND_EXIT);
	exitSound.setObjectID(getObject()->getID());
	TheAudio->addAudioEvent(&exitSound);

	if (rider)
	{
		AudioEventRTS fallingSound = *rider->getTemplate()->getSound(BFME_SOUND_FALLING);
		fallingSound.setObjectID(rider->getID());
		TheAudio->addAudioEvent(&fallingSound);
	}
}
