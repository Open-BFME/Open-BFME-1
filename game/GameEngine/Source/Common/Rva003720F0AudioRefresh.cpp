// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x003720F0 is an address-derived two-argument __thiscall.  The
// boundary is proved by ret 8 and by the status-word read at argument two
// offset +0x18.  The owner fields used below are the only fields reached by
// the body: module data at +0x04, the owning Object at +0x08, and an audio
// handle at +0x20.

typedef unsigned int AudioHandle;

struct Rva003720F0AsciiString
{
	void *m_data;
};

struct Rva003720F0ModuleData
{
	unsigned char m_pad00[0x24];
	Rva003720F0AsciiString m_eventName;
};

struct Rva003720F0Object
{
	unsigned char m_pad00[0x74];
	unsigned int m_id;
};

struct Rva003720F0Context
{
	unsigned char m_pad00[0x18];
	unsigned int m_flags;
};

// The retail object is AudioEventRTS (0x70B). Its outlined ObjectID
// constructor is a distinct compiled variant, reached through ILT 0x00008E86.
#include "ascii_string.h"
enum ObjectID { INVALID_ID = 0 };
class AudioEventRTS
{
public:
    ~AudioEventRTS();
    unsigned char m_body[0x70];
};

extern void j_00008e86();

// Own the lifetime of the event built by the existing outlined constructor.
// Its inline sibling has the same C++ signature but a different call target.
class Rva003720F0EventStorage
{
public:
    Rva003720F0EventStorage(const AsciiString &name, ObjectID owner)
    {
        typedef void (Rva003720F0EventStorage::*ConstructCall)(
            const AsciiString &, ObjectID);
        union { void *address; ConstructCall member; } call;
        call.address = (void *)j_00008e86;
        (this->*call.member)(name, owner);
    }
    ~Rva003720F0EventStorage()
    {
        reinterpret_cast<AudioEventRTS *>(m_storage)->~AudioEventRTS();
    }
    unsigned char m_storage[0x70];
};

class Rva005A00B0AudioClient
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual AudioHandle addAudioEvent(const AudioEventRTS *event);
	virtual void slot18();
	virtual void removeAudioEvent(AudioHandle handle);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual bool isCurrentlyPlaying(AudioHandle handle);
};

// Root ledger already binds this decorated global at 0x012ED668 to the
// Rva005A00B0AudioClient type; this TU adds no global pin.
extern Rva005A00B0AudioClient *TheAudioClientUpdate;

class Rva003720F0Owner
{
public:
	void update(Rva003720F0Context *previous, Rva003720F0Context *current);

private:
	void *m_virtuals;
	Rva003720F0ModuleData *m_moduleData;
	Rva003720F0Object *m_object;
	unsigned char m_pad0c[0x14];
	AudioHandle m_audioHandle;
};

void Rva003720F0Owner::update(Rva003720F0Context *previous,
	Rva003720F0Context *current)
{
	unsigned int currentFlags = current->m_flags;
	if (currentFlags & 0x10000)
	{
		Rva003720F0ModuleData *module = m_moduleData;
		Rva003720F0AsciiString *eventName = &module->m_eventName;
		if (eventName->m_data != 0)
		{
			if (!TheAudioClientUpdate->isCurrentlyPlaying(m_audioHandle))
			{
				Rva003720F0Object *object = m_object;
				unsigned int ownerID = object->m_id;
				Rva003720F0EventStorage event(*reinterpret_cast<AsciiString *>(eventName), static_cast<ObjectID>(ownerID));
				m_audioHandle = TheAudioClientUpdate->addAudioEvent(reinterpret_cast<const AudioEventRTS *>(&event));
			}
		}
		return;
	}

	if (previous->m_flags & 0x10000)
	{
		if (m_audioHandle >= 5)
		{
			TheAudioClientUpdate->removeAudioEvent(m_audioHandle);
			m_audioHandle = 1;
		}
	}
}
