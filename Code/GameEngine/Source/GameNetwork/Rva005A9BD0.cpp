// cl: /DNDEBUG /MD
// Retail 0x005A9BD0, 145 bytes, __stdcall (ret 0xc, three stack args).
// Two "holder" pointers each gated by their own +0xfc pointer field; when the
// third argument is zero, the second holder's +0xfc object's ID is appended
// to a new TheMessageStream message (type 0x424), then its +0x214 Thing is
// asked isKindOf(0x6c) and, if so, a pointer returned by that Thing's
// vtbl+0x28 gets bfmeThenBXF(0) called on it. No named caller (brief lists
// none) and no vtable/string ties an owner, so this keeps the address token.

typedef int Int;
typedef unsigned int UnsignedInt;

enum KindOfType { KINDOF_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
// Real class name for correct mangling of the already-pinned
// ?isKindOf@Thing@@QBE_NW4KindOfType@@@Z (REL32 0x0003251F). The extra
// leading virtual slots are unproven padding so the second call on the same
// object (vtbl+0x28) lands at the right offset; Thing's own real layout has
// only the dtor virtual, so this is a TU-local wider view of a derived type.
class Thing
{
public:
	virtual void rva005A9BD0Slot0();
	virtual void rva005A9BD0Slot1();
	virtual void rva005A9BD0Slot2();
	virtual void rva005A9BD0Slot3();
	virtual void rva005A9BD0Slot4();
	virtual void rva005A9BD0Slot5();
	virtual void rva005A9BD0Slot6();
	virtual void rva005A9BD0Slot7();
	virtual void rva005A9BD0Slot8();
	virtual void rva005A9BD0Slot9();
	virtual void *rva005A9BD0Slot10();		///< vtbl+0x28

	bool isKindOf(KindOfType t) const;
};

// The already-pinned ?bfmeThenBXF@BfmeThingBXF@@QAEXH@Z (REL32 0x0004067E).
class BfmeThingBXF
{
public:
	void bfmeThenBXF(int arg);
};

struct Rva005A9BD0Object
{
	unsigned char m_pad74[0x74];
	UnsignedInt m_id;						///< +0x74
	unsigned char m_pad214[0x214 - 0x78];
	Thing *m_aiThing;						///< +0x214
};

struct Rva005A9BD0Holder
{
	unsigned char m_padFC[0xfc];
	Rva005A9BD0Object *m_object;			///< +0xfc
};

class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };
	void appendObjectIDArgument(UnsignedInt arg);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
// BFME's GameMessageList/MessageStream vtable carries five more slots than
// Zero Hour's ahead of appendMessage(GameMessage*) (see
// Code/GameEngine/Source/Common/MessageStream.cpp's BfmeCommandList, whose
// nine placeholder slots put appendMessage(GameMessage*) at 0x24 instead of
// ZH's 0x10); MessageStream's own appendMessage(Type) then lands at 0x34.
class MessageStream
{
public:
	virtual void rva005A9BD0MsSlot0();
	virtual void rva005A9BD0MsSlot1();
	virtual void rva005A9BD0MsSlot2();
	virtual void rva005A9BD0MsSlot3();
	virtual void rva005A9BD0MsSlot4();
	virtual void rva005A9BD0MsSlot5();
	virtual void rva005A9BD0MsSlot6();
	virtual void rva005A9BD0MsSlot7();
	virtual void rva005A9BD0MsSlot8();
	virtual void rva005A9BD0MsSlot9();
	virtual void rva005A9BD0MsSlot10();
	virtual void rva005A9BD0MsSlot11();
	virtual void rva005A9BD0MsSlot12();
	virtual GameMessage *appendMessage(GameMessage::Type type);	///< vtbl+0x34
};

extern MessageStream *TheMessageStream;

int __stdcall rva005A9BD0(Rva005A9BD0Holder *holder1, Rva005A9BD0Holder *holder2, Int flag)
{
	if (!holder1->m_object)
		return 0;

	if (!holder2->m_object)
		return 0;

	if (!flag)
	{
		GameMessage *msg = TheMessageStream->appendMessage((GameMessage::Type)0x424);
		msg->appendObjectIDArgument(holder2->m_object->m_id);

		// Defaults to holder2 itself (always non-null here); only when the
		// object's AI Thing exists and matches kind 0x6c does the target
		// become the (possibly null) result of that Thing's vtbl+0x28 call.
		void *target = holder2;
		Thing *aiThing = holder2->m_object->m_aiThing;
		if (aiThing && aiThing->isKindOf((KindOfType)0x6c))
			target = aiThing->rva005A9BD0Slot10();

		if (target)
			((BfmeThingBXF *)target)->bfmeThenBXF(0);
	}

	return 0x424;
}
