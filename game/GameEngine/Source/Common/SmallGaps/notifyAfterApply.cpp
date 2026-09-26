// cl: /Igame/Libraries/Source/WWVegas/WWLib
// ?notifyAfterApply@@YAXPAURva00234200Owner@@HH@Z
//
// The apply helper called from this TU is the real owner of the generated
// 0x0022E270 body.  Its first collection is an STLport list of AsciiStrings
// at +0x174, while the later vector remains at +0x2b0 for notifyAfterApply.
// The registry object keeps its retail neutral type for the global symbol but
// inherits the already matched ThingFactory lookup ABI.
#include "ascii_string.h"

struct Rva0020AA00Target
{
public:
	void notify(int a, int b);

	unsigned char m_pad00[0xc8];
};

class ThingTemplate : public Rva0020AA00Target
{
public:
	unsigned int m_kindOf[3];
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

struct Rva0020AA00Registry : public BfmeThingFactory
{
	Rva0020AA00Target *lookup(const int &id);
};

extern Rva0020AA00Registry *Rva0020AA00TheRegistry;

struct Rva0022E270ListNode
{
	Rva0022E270ListNode *m_next;
	Rva0022E270ListNode *m_previous;
	AsciiString m_value;
};

struct Rva0022E270List
{
	Rva0022E270ListNode *m_head;
};

class GameLODManager
{
public:
	unsigned char m_pad00[0x16c4];
	int m_currentLevel;
};

extern GameLODManager *TheGameLODManager;

class Rva0022E270AIData
{
public:
	unsigned char m_pad00[0xb7];
	unsigned char m_useTemplateNotification;
};

class AI
{
public:
	unsigned char m_pad00[0x14];
	Rva0022E270AIData *m_data;
};

extern AI *TheAI;

class Gen_001D5EE0Target
{
public:
	void bfmeForward(void *first, void *second);
};

static __forceinline void *rva0022E270PointerWord(int word)
{
	// The neutral outer ABI carries this value as a 32-bit word, while the
	// proven guarded-delegate ABI consumes it as a pointer.  Preserve that
	// caller-supplied word without inventing a stronger public signature.
	return reinterpret_cast<void *>(static_cast<unsigned int>(word));
}

struct Rva00234200Owner
{
	unsigned char m_pad000[0x174];
	Rva0022E270List m_applyList;
	unsigned char m_pad178[0x200 - 0x178];
	Gen_001D5EE0Target *m_forward;
	unsigned char m_pad204[0x2b0 - 0x204];
	int *m_begin;
	int *m_end;
};

void __cdecl Rva00234200Apply(Rva00234200Owner *owner, int a, int b)
{
	register Rva00234200Owner *savedOwner = owner;
	const int lod = TheGameLODManager->m_currentLevel;
	Rva0022E270ListNode *node = savedOwner->m_applyList.m_head->m_next;
	while (node != savedOwner->m_applyList.m_head)
	{
		const ThingTemplate *templateObject =
			Rva0020AA00TheRegistry->findTemplate(node->m_value);
		if (templateObject)
		{
			unsigned char notify = *reinterpret_cast<const unsigned char *>(
				static_cast<unsigned int>(b));
			if (lod != 4 &&
				(templateObject->m_kindOf[2] & 0x02000000) == 0 &&
				(templateObject->m_kindOf[0] & 0x00000400) == 0 &&
				TheAI->m_data->m_useTemplateNotification != 0)
			{
				notify = 1;
			}
			Rva0020AA00Target *target =
				const_cast<Rva0020AA00Target *>(
					static_cast<const Rva0020AA00Target *>(templateObject));
			target->notify(a, (int)&notify);
		}
		node = node->m_next;
	}

	if (savedOwner->m_forward)
	{
		savedOwner->m_forward->bfmeForward(
			rva0022E270PointerWord(a), rva0022E270PointerWord(b));
	}
}

void notifyAfterApply(Rva00234200Owner* owner, int a, int b)
{
	Rva00234200Apply(owner, a, b);
	for (int* it = owner->m_begin; it != owner->m_end; ++it) {
		Rva0020AA00Target* t = Rva0020AA00TheRegistry->lookup(*it);
		if (t)
			t->notify(a, b);
	}
}
