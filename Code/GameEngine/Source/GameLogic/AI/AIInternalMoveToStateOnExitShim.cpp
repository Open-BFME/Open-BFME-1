// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME's AIInternalMoveToState::onExit body at retail RVA 0x00172D80.
// The incremental-link name for this body is kept as a TU-local shim because
// the surviving Zero Hour base method is still the ILT at 0x00029311.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned int AudioHandle;

enum StateExitType
{
	STATE_EXIT_NORMAL = 0
};

class Object;

class StateMachine
{
private:
	UnsignedByte m_unreconstructed_00[0x10];

public:
	Object *m_owner;
};

// The condition words are the BFME Object model-condition bitset words that
// the retail body updates directly.  The names are deliberately descriptive
// of the observed offsets rather than pretending the ZH header has this
// layout.
class Rva00172D80Object
{
public:
	UnsignedByte m_unreconstructed_00[0x98];
	UnsignedInt m_status98;

private:
	UnsignedByte m_unreconstructed_9c[0x78];

public:
	UnsignedInt m_condition114;
	UnsignedInt m_condition118;
	UnsignedInt m_condition11c;
	UnsignedInt m_condition120;

private:
	UnsignedByte m_unreconstructed_124[0xe0];

public:
	void *m_unreconstructed_204;
};

class AudioManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent(AudioHandle handle);
};

extern AudioManager *TheAudio;
extern void j_00012486();
extern void j_0002191d();

class AIInternalMoveToStateOnExitShim
{
private:
	UnsignedByte m_unreconstructed_00[0x1c];
	StateMachine *m_machine;
	UnsignedByte m_unreconstructed_20[0x20];
	AudioHandle m_ambientPlayingHandle;

public:
	void onExit(StateExitType status);
};

void AIInternalMoveToStateOnExitShim::onExit(StateExitType status)
{
	Rva00172D80Object *object = (Rva00172D80Object *)m_machine->m_owner;
	void *ai = object->m_unreconstructed_204;

	if ((object->m_status98 & 0x400) == 0)
	{
		if (object->m_condition114 & 0x10000000)
		{
			object->m_condition114 &= 0xEFFFFFFF;
			typedef void (Rva00172D80Object::*NotifyCall)();
			union { void *asVoid; NotifyCall asMember; } notifyCast;
			notifyCast.asVoid = (void *)j_0002191d;
			(object->*notifyCast.asMember)();
		}

	}

	if (object->m_condition120 & 0x00040000)
	{
		object->m_condition120 &= 0xFFFBFFFF;
		typedef void (Rva00172D80Object::*NotifyCall)();
		union { void *asVoid; NotifyCall asMember; } notifyCast;
		notifyCast.asVoid = (void *)j_0002191d;
		(object->*notifyCast.asMember)();
	}

	if ((*(UnsignedByte *)&object->m_condition11c & 0x40) != 0)
	{
		object->m_condition11c &= 0xFFFFFFBF;
		typedef void (Rva00172D80Object::*NotifyCall)();
		union { void *asVoid; NotifyCall asMember; } notifyCast;
		notifyCast.asVoid = (void *)j_0002191d;
		(object->*notifyCast.asMember)();
	}

	if (object->m_condition11c & 0x100)
	{
		object->m_condition11c &= 0xFFFFFEFF;
		typedef void (Rva00172D80Object::*NotifyCall)();
		union { void *asVoid; NotifyCall asMember; } notifyCast;
		notifyCast.asVoid = (void *)j_0002191d;
		(object->*notifyCast.asMember)();
	}

	TheAudio->removeAudioEvent(m_ambientPlayingHandle);
	m_ambientPlayingHandle = 1;
	if (ai != 0)
	{
		typedef void (Rva00172D80Object::*SetCall)();
		union { void *asVoid; SetCall asMember; } setCast;
		setCast.asVoid = (void *)j_00012486;
		(((Rva00172D80Object *)ai)->*setCast.asMember)();
	}
}
