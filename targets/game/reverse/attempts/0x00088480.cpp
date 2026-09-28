// ?ambientAudio00088480@MapObject@@QAEXXZ
// partial score=0.42 date=2026-09-28
// ?ambientAudio00088480@MapObject@@QAEXXZ -- retail RVA 0x00088480, 1019 bytes (banked, not matched).
//
// IDENTITY: class MapObject is proven (matched MapObject::duplicate calls this
// body on the new MapObject through ILT 0x00031FCF; bfmeGoEYE sets the mode
// global 0x012ED5D8 and walks the MapObject list calling it; the +0x44/+0x54/
// +0x58/+0x5C members agree with the matched MapObject destructor).  The method
// name is opaque (address kept); the " MapObjectAmb %d %s" literal and the
// AudioManager addAudioEvent calls only show it manages the map object's
// ambient audio events.
//
// OPEN NAME WORK before landing (probe masks relocations):
//   * the raw-pointer ctor 0x00087720 is ledgered ??0Rva00087720Ptr, the temp
//     dtor 0x000877B0 ??1AudioEventInfoRef, clear 0x000877E0 ??1Rva000877E0Ref,
//     op= 0x00087860 only ?dup_00087860: one ref class cannot reach all four,
//     so the landing needs address-derived pins (pin_consistency before/after).
//   * ready 0x000874E0 is ledgered as int ?bfmeReady@Gen_000874E0@@QBEHXZ but
//     every caller tests AL: the (char) cast here keeps that shape.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline StringBase<char>::~StringBase() { releaseBuffer(); }

typedef long Long;
typedef int Int;
typedef bool Bool;
typedef unsigned int AudioHandle;

extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement(Long volatile *addend);
extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(Long volatile *addend);

struct Coord3D;

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();
	Long m_refCount;			///< +0x04
	AsciiString m_audioName;	///< +0x08
};

// Ready test on the referenced info (+0x84 / +0x3C), matched at 0x000874E0.
class Gen_000874E0
{
public:
	int bfmeReady() const;
};

// Info setter retail calls with the formatted name, matched at 0x000B5610.
class BfmeThingWB
{
public:
	void bfmeGoWB(void *what);
};

class Rva00087750Ref
{
public:
	Rva00087750Ref() : m_ptr(0) {}
	Rva00087750Ref(AudioEventInfo *info);
	~Rva00087750Ref()
	{
		if (m_ptr)
		{
			AudioEventInfo *p = m_ptr;
			if (InterlockedDecrement(&p->m_refCount) <= 0)
				delete p;
		}
	}
	Rva00087750Ref &operator=(const Rva00087750Ref &rhs);
	void clear();

	AudioEventInfo *m_ptr;
};

__declspec(noinline) Rva00087750Ref::Rva00087750Ref(AudioEventInfo *info) : m_ptr(info)
{
	if (m_ptr)
		InterlockedIncrement(&m_ptr->m_refCount);
}

__declspec(noinline) Rva00087750Ref &Rva00087750Ref::operator=(const Rva00087750Ref &rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_ptr)
			InterlockedIncrement(&rhs.m_ptr->m_refCount);
		if (m_ptr)
		{
			AudioEventInfo *p = m_ptr;
			if (InterlockedDecrement(&p->m_refCount) <= 0)
				delete p;
		}
		m_ptr = rhs.m_ptr;
	}
	return *this;
}

__declspec(noinline) void Rva00087750Ref::clear()
{
	if (m_ptr)
	{
		AudioEventInfo *p = m_ptr;
		if (InterlockedDecrement(&p->m_refCount) <= 0)
			delete p;
		m_ptr = 0;
	}
}

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
	Rva00087860Ref &operator=(const Rva00087860Ref &rhs);

	AudioEventInfo *m_ptr;
};

__declspec(noinline) Rva00087860Ref &Rva00087860Ref::operator=(const Rva00087860Ref &rhs)
{
	if (this != &rhs)
	{
		if (rhs.m_ptr)
			InterlockedIncrement(&rhs.m_ptr->m_refCount);
		if (m_ptr)
		{
			AudioEventInfo *p = m_ptr;
			if (InterlockedDecrement(&p->m_refCount) <= 0)
				delete p;
		}
		m_ptr = rhs.m_ptr;
	}
	return *this;
}

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, const Coord3D *positionOfAudio, int extra);
	virtual ~AudioEventRTS();

	AsciiString m_filenameToLoad;
	Rva00087750Ref m_eventInfo;		///< +0x08
	char m_pad0c[0x70 - 0x0C];
};

class Rva00087BD0
{
public:
	void *get(int i);
};

static inline AudioEventRTS *soundAt(Rva00087BD0 *tt, int i)
{
	return static_cast<AudioEventRTS *>(tt->get(i));
}

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual AudioHandle addAudioEvent(const AudioEventRTS *eventToAdd);			///< +0x44
	virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void getInfoForAudioEvent(const AudioEventRTS *eventToFindAndFill);	///< +0xAC
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
extern Int g_mapObjectAmbSerial012ED5E8;

class Dict
{
	void *m_data;
};

void parseAmbientAudioProperties_000B6030();

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
	((void (__cdecl *)(Dict *, int, Rva00087BD0 *, Bool *, Rva00087860Ref *, Bool *))
		parseAmbientAudioProperties_000B6030)(&m_properties, 0, m_thingTemplate,
		&disabled, &info, &modeTwo);

	if (info.m_ptr)
	{
		AsciiString name;
		name.format(AsciiString(" MapObjectAmb %d %s"), g_mapObjectAmbSerial012ED5E8,
			info.m_ptr->m_audioName.str());
		++g_mapObjectAmbSerial012ED5E8;
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
				current.clear();
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
			current = Rva00087750Ref(info.m_ptr);
		}

		Rva00087BD0 *tt = m_thingTemplate;
		if (tt->get(0x5b))
		{
			alternate = soundAt(tt, 0x5b)->m_eventInfo;
			if (alternate.m_ptr == 0)
			{
				AudioManager *audio = TheAudio;
					audio->getInfoForAudioEvent(soundAt(m_thingTemplate, 0x5b));
				alternate = soundAt(m_thingTemplate, 0x5b)->m_eventInfo;
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
					enable = true;
				else if (alternate.m_ptr && (char)reinterpret_cast<Gen_000874E0 *>(alternate.m_ptr)->bfmeReady())
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
				m_rva54 = TheAudio->addAudioEvent(&AudioEventRTS(
					reinterpret_cast<const AsciiString &>(current),
					reinterpret_cast<const Coord3D *>(reinterpret_cast<BfmeThingBWF *>(this)->bfmeGoBWF()), 0));
				if (alternate.m_ptr)
				{
					m_rva58 = TheAudio->addAudioEvent(&AudioEventRTS(
						reinterpret_cast<const AsciiString &>(alternate),
						reinterpret_cast<const Coord3D *>(reinterpret_cast<BfmeThingBWF *>(this)->bfmeGoBWF()), 0));
				}
			}
		}
		else
			reinterpret_cast<Gen00087C30_00088480 *>(this)->gen00087C30();
	}
}
