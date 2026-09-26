// cl: /DNDEBUG /MD /EHsc
// Open-BFME: address-derived member of the offset-tail-thunk family at
// 0x002BA240 (game/GameEngine/Source/Common/MemberOffsetTailThunks.cpp names
// the class Gen002BA240 and declares the generic void handle() the whole
// family shares, but THIS body actually reads a stack argument and cleans it
// with ret 4, so its true signature takes one UnsignedInt id). Reached from
// Rva002BAA30::invoke (this-32) which itself is reached, via the same bare
// jmp chain, from d_002baa40.asm and d_00373220.asm; none of those callers
// are landed yet, so no proven owning class exists -- keeping the address
// token per docs/naming_evidence.md.
//
// Body: this+0x94 is a last-seen id guard (return if unchanged); this+0x8 is
// an object pointer. When id != 0, this+0x8's vtable slot 0x28 is called to
// get a Drawable and isKindOf(0x95) is tested on the object; when it fails,
// setStatusBit(3,true) fires and, if the drawable exists, it is deselected
// and delayed. When isKindOf(0x95) succeeds, and both objects are set, and
// the object's controlling player is the local player, a GameMessage 0x3ec
// is appended with the object's id field (+0x74) and InGameUI vslot 0xe4 is
// invoked on the drawable. When id == 0, the object is read directly (no
// vtable+0x28 call up front), and on a *different* isKindOf(0x95) failure
// clearStatus(3) fires, the vtable+0x28 lookup happens afterward, a second
// isKindOf(0x95) check gates a select (true) and a second delay variant.

typedef unsigned int UnsignedInt;

class Drawable
{
public:
	void setSelectable(bool selectable);
	void bfmeDelayA(int);
	void bfmeDelayB(int);
};

class BfmeThingAIA
{
public:
	bool bfmeAskAIA(int what);
};

class BfmeR1094;

class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094();
};

class Rva0025DF30Object
{
public:
	void applyUpgrade(int upgrade);
};

void __stdcall bfmeLogCNE(int code, int level);

class GameMessage
{
public:
	void appendObjectIDArgument(UnsignedInt id);
};

class MessageStream
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual GameMessage *appendMessage(int type) = 0;
};

class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void notify0xE4(Drawable *drawable) = 0;
};

class Rva002BA240SourceObject
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual Drawable *vslot0x28() = 0;

	char m_pad[0x70];
	UnsignedInt m_id0x74;
};

class Player;

class Rva002EE330PlayerList
{
private:
	char m_slice_pad[0x0C];

public:
	Player *m_localPlayer;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;
extern MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;

class Gen002BA240
{
public:
	void handle(UnsignedInt id);

private:
	char m_pad0[0x8];
	Rva002BA240SourceObject *m_object;   // +0x8
	char m_pad8[0x94 - 0xC];
	UnsignedInt m_lastId;                // +0x94
};

void Gen002BA240::handle(UnsignedInt id)
{
	if (m_lastId == id)
		return;

	m_lastId = id;

	if (id != 0)
	{
		Drawable *drawable = m_object->vslot0x28();
		Rva002BA240SourceObject *who = m_object;

		if (!reinterpret_cast<BfmeThingAIA *>(who)->bfmeAskAIA(0x95))
		{
			typedef void (__stdcall *LogCNEFn)(int, int);
			typedef void (Rva002BA240SourceObject::*LogCNEThisCall)(int, int);
			union { LogCNEFn function; LogCNEThisCall member; } route;
			route.function = bfmeLogCNE;
			(who->*route.member)(3, 1);

			if (drawable)
			{
				drawable->setSelectable(false);
				drawable->bfmeDelayA(0xa);
			}

			return;
		}

		if (drawable && who)
		{
			BfmeR1094 *localPlayer = reinterpret_cast<BfmeR1094 *>(Rva002EE330ThePlayers->m_localPlayer);
			if (reinterpret_cast<BfmeK1094 *>(who)->bfmeCur1094() == localPlayer)
			{
				GameMessage *message = TheMessageStream->appendMessage(0x3ec);
				message->appendObjectIDArgument(m_object->m_id0x74);
				TheInGameUI->notify0xE4(drawable);
			}
		}

		return;
	}

	Rva002BA240SourceObject *direct = m_object;

	if (reinterpret_cast<BfmeThingAIA *>(direct)->bfmeAskAIA(0x95))
		return;

	reinterpret_cast<Rva0025DF30Object *>(direct)->applyUpgrade(3);

	Drawable *drawable = m_object->vslot0x28();

	if (!drawable)
		return;

	if (reinterpret_cast<BfmeThingAIA *>(m_object)->bfmeAskAIA(0x95))
		return;

	drawable->setSelectable(true);
	drawable->bfmeDelayB(0x1e);
}
