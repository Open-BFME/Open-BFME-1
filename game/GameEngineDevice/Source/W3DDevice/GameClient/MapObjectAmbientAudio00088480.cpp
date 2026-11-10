// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ?ambientAudio00088480@MapObject@@QAEXXZ -- retail RVA 0x00088480, 1019 bytes
// (RET at +0x3FA, INT3 padding after).
//
// IDENTITY: class MapObject is proven (matched MapObject::duplicate calls this
// body on the new MapObject through ILT 0x00031FCF; bfmeGoEYE stores the mode
// global 0x012ED5D8 and walks the MapObject list calling it; the +0x44/+0x54/
// +0x58/+0x5C members agree with the matched MapObject destructor). The method
// name is opaque (address kept): the " MapObjectAmb %d %s" literal and the
// AudioManager addAudioEvent calls only show it refreshes the map object's
// ambient audio events. Evidence note:
// targets/game/reverse/identity_evidence/00088480-mapobject-ambient-audio.md
//
// WHAT THE BYTES SHOW that the source must keep:
//   * the ready test 0x000874E0 is an inline member the compiler did not
//     expand: retail keeps alternate.m_ptr in EDI across both ready() calls
//     (side-effect summary known) but in a callee-saved register (no register
//     summary, as for a COMDAT copy);
//   * after re-fetching the slot 0x5B info retail assigns it to `current`
//     (lea ecx,[esp+0x14] at +0x22C), not to `alternate`;
//   * the two addAudioEvent blocks are siblings, each with a named event local.
// The reference helpers are address-named views: one class cannot reach the
// raw-pointer ctor 0x00087720, its temporary's release 0x000877B0, the clearing
// release 0x000877E0 and the two byte-identical copy-assigns 0x00087750 and
// 0x00087860 under their ledger names.

#include "ascii_string.h"

typedef long Long;
typedef int Int;
typedef bool Bool;
typedef unsigned int AudioHandle;

extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement(Long volatile *addend);

struct Coord3D;

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();
	Long m_refCount;			///< +0x04
	AsciiString m_audioName;	///< +0x08
};

// Ready test on the referenced info (+0x84 / +0x3C), retail 0x000874E0.
class Gen_000874E0
{
public:
	__declspec(noinline) int bfmeReady() const
	{
		int state = m_bfmeState;
		if (state != 0 && state != 3 && (m_bfmeFlags & 1) == 0)
			return 0;
		return 1;
	}

	int m_bfmeHead[15];
	unsigned char m_bfmeFlags;
	int m_bfmeGap[17];
	int m_bfmeState;
};

// Info setter retail calls with the formatted name, matched at 0x000B5610.
class BfmeThingWB
{
public:
	void bfmeGoWB(void *what);
};

// Release of a one-pointer info reference, retail 0x000877B0.
class Rva000877B0Ref
{
public:
	void Rva000877B0();

	AudioEventInfo *m_ptr;
};

// Raw-pointer constructor 0x00087720; its temporary is released by 0x000877B0.
struct Rva00087720Target;
class Rva00087720Ptr
{
public:
	Rva00087720Ptr(Rva00087720Target *target);
	~Rva00087720Ptr() { reinterpret_cast<Rva000877B0Ref *>(this)->Rva000877B0(); }

	AudioEventInfo *m_ptr;
};

// Release that also zeroes the pointer, retail 0x000877E0.
class Rva000877E0Ref
{
public:
	~Rva000877E0Ref();

	AudioEventInfo *m_ptr;
};

class Rva00087750Ref
{
public:
	Rva00087750Ref() : m_ptr(0) {}
	~Rva00087750Ref()
	{
		if (m_ptr)
		{
			AudioEventInfo *p = m_ptr;
			if (InterlockedDecrement(&p->m_refCount) <= 0)
				delete p;
		}
	}
	Rva00087750Ref &operator=(const Rva00087750Ref &rhs);	///< retail 0x00087750

	AudioEventInfo *m_ptr;
};

class Rva00087860Ref
{
public:
	Rva00087860Ref() : m_ptr(0) {}
	~Rva00087860Ref()
	{
		if (m_ptr)
		{
			AudioEventInfo *p = m_ptr;
			if (InterlockedDecrement(&p->m_refCount) <= 0)
				delete p;
		}
	}
	Rva00087860Ref &operator=(const Rva00087860Ref &rhs);	///< retail 0x00087860

	AudioEventInfo *m_ptr;
};

class LwsAudioEventRTS
{
public:
	LwsAudioEventRTS(const AsciiString &eventName, const Coord3D *positionOfAudio, int extra);
	~LwsAudioEventRTS();

	void *m_vtable;
	AsciiString m_filenameToLoad;
	Rva00087750Ref m_eventInfo;		///< +0x08
	char m_pad0c[0x70 - 0x0C];
};

class Rva00087BD0
{
public:
	void *get(int i);
};

static inline LwsAudioEventRTS *soundAt(Rva00087BD0 *tt, int i)
{
	return static_cast<LwsAudioEventRTS *>(tt->get(i));
}

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual AudioHandle addAudioEvent(const LwsAudioEventRTS *eventToAdd);			///< +0x44
	virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void getInfoForAudioEvent(const LwsAudioEventRTS *eventToFindAndFill);	///< +0xAC
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68();
	virtual void slot69(AudioEventInfo *info);									///< +0x114
};

extern AudioManager *TheAudio;
extern void *g_bfmeCurEYE;
// Rename counter for customized map-object infos, retail VA 0x012ED5E8.
extern Int g_Va012ED5E8;

class Dict
{
	void *m_data;
};

// Audio property parser 0x000B6030 under its pinned call-site spelling.
class Rva001D0610Drawable;
class Rva001D0610AudioInfo;
template <class T> class Rva001D0610Ref;
void rva000B6030(Dict *properties, Rva001D0610Drawable *drawable, void *thingTemplate,
	bool *disabled, Rva001D0610Ref<Rva001D0610AudioInfo> *info, bool *enabled);

class BfmeRetBWF;
class BfmeThingBWF
{
public:
	BfmeRetBWF *bfmeGoBWF();
};

class Gen00087C30_00088480
{
public:
	void gen00087C30();
};

class MapObject
{
public:
	void ambientAudio00088480();
	Bool isRuntimeFlag10() const { return (m_runtimeFlags & 0x10) != 0; }

private:
	void *m_vtable;
	MapObject *m_nextMapObject;					///< +0x04
	char m_pad08[0x0C];							///< +0x08
	AsciiString m_objectName;					///< +0x14
	Rva00087BD0 *m_thingTemplate;				///< +0x18
	float m_angle;								///< +0x1C
	Int m_flags;								///< +0x20
	Dict m_properties;							///< +0x24
	char m_pad28[0x1C];							///< +0x28
	Int m_runtimeFlags;							///< +0x44
	char m_pad48[0x0C];							///< +0x48
	AudioHandle m_rva54;						///< +0x54
	AudioHandle m_rva58;						///< +0x58
	Rva00087860Ref m_rva5c;						///< +0x5C
};

void MapObject::ambientAudio00088480()
{
	if (TheAudio == 0 || m_thingTemplate == 0)
		return;

	Bool enable = false;
	Bool disabled = false;
	Rva00087860Ref info;
	Bool modeTwo = false;
	rva000B6030(&m_properties, 0, m_thingTemplate, &disabled,
		reinterpret_cast<Rva001D0610Ref<Rva001D0610AudioInfo> *>(&info), &modeTwo);

	if (info.m_ptr)
	{
		AsciiString name;
		name.format(AsciiString(" MapObjectAmb %d %s"), g_Va012ED5E8,
			info.m_ptr->m_audioName.str());
		++g_Va012ED5E8;
		reinterpret_cast<BfmeThingWB *>(info.m_ptr)->bfmeGoWB(&name);
		TheAudio->slot69(info.m_ptr);
	}

	Rva00087750Ref current;
	Rva00087750Ref alternate;
	if (!disabled && g_bfmeCurEYE && isRuntimeFlag10())
	{
		if (info.m_ptr == 0)
		{
			Rva00087BD0 *tt = m_thingTemplate;
			if (tt->get(0x57) == 0)
			{
				enable = false;
				reinterpret_cast<Rva000877E0Ref *>(&current)->~Rva000877E0Ref();
			}
			else
			{
				current = soundAt(tt, 0x57)->m_eventInfo;
				if (current.m_ptr == 0)
				{
					AudioManager *audio = TheAudio;
					audio->getInfoForAudioEvent(soundAt(m_thingTemplate, 0x57));
					current = soundAt(m_thingTemplate, 0x57)->m_eventInfo;
				}
			}
		}
		else
		{
			current = *reinterpret_cast<const Rva00087750Ref *>(
				&Rva00087720Ptr(reinterpret_cast<Rva00087720Target *>(info.m_ptr)));
		}

		Rva00087BD0 *tt = m_thingTemplate;
		if (tt->get(0x5b))
		{
			alternate = soundAt(tt, 0x5b)->m_eventInfo;
			if (alternate.m_ptr == 0)
			{
				AudioManager *audio = TheAudio;
					audio->getInfoForAudioEvent(soundAt(m_thingTemplate, 0x5b));
				// Retail assigns the re-fetched 0x5b info to `current` here (lea ecx,[esp+0x14] at +0x22C).
				current = soundAt(m_thingTemplate, 0x5b)->m_eventInfo;
			}
		}

		if (current.m_ptr || alternate.m_ptr)
		{
			switch ((Int)g_bfmeCurEYE)
			{
			case 1:
				enable = true;
				break;
			case 2:
				enable = modeTwo;
				break;
			case 3:
				enable = false;
				if (current.m_ptr && (char)reinterpret_cast<Gen_000874E0 *>(current.m_ptr)->bfmeReady())
				{
					enable = true;
					break;
				}
				if (alternate.m_ptr && (char)reinterpret_cast<Gen_000874E0 *>(alternate.m_ptr)->bfmeReady())
					enable = true;
				break;
			}
		}
		else
			enable = false;
	}
	else
		enable = false;

	Bool playing = m_rva54 >= 5 || m_rva58 >= 5;
	if (enable != playing)
	{
		if (enable)
		{
			m_rva5c = info;
			if (current.m_ptr)
			{
				LwsAudioEventRTS event(reinterpret_cast<const AsciiString &>(current),
					reinterpret_cast<const Coord3D *>(reinterpret_cast<BfmeThingBWF *>(this)->bfmeGoBWF()), 0);
				m_rva54 = TheAudio->addAudioEvent(&event);
			}
			if (alternate.m_ptr)
			{
				LwsAudioEventRTS event(reinterpret_cast<const AsciiString &>(alternate),
					reinterpret_cast<const Coord3D *>(reinterpret_cast<BfmeThingBWF *>(this)->bfmeGoBWF()), 0);
				m_rva58 = TheAudio->addAudioEvent(&event);
			}
		}
		else
			reinterpret_cast<Gen00087C30_00088480 *>(this)->gen00087C30();
	}
}
