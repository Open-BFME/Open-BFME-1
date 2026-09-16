// Retail RVA 0x0021C820, 96 bytes. Address-derived owner: its identity is unproven.
// Source-shape donor: Rva0021C7A0RawDispatch.cpp; this twin changes both call targets.
// Receiver vslot +0xc4 returns AL; subject byte +0x94 supplies mask 0x10.
// ILT 0x0002e951 -> Weapon position-range overload at 0x001e88f0 (44 bytes):
// ECX receiver, three stack words, AL result, ret 12. The last argument is zero.
// ILT 0x00022b2e -> GarrisonContain position handler at 0x0021e5d0 (186 bytes):
// ECX receiver, three stack pointers, AL result, ret 12. Typed thunk adapters
// retain the existing address routes without assigning a speculative owner.

extern void j_00022b2e(void);
extern void j_0002e951(void);

struct Rva0021C820Call
{
	bool call(void *, void *, void *);
};

typedef bool (Rva0021C820Call::*Rva0021C820Member)(void *, void *, void *);
typedef bool (Rva0021C820Call::*Rva0021C820RangeMember)(void *, void *, int);

static bool callPositionRange(Rva0021C820Call *receiver, void *subject, void *position)
{
	union { void (*raw)(); Rva0021C820RangeMember member; } thunk;
	thunk.raw = j_0002e951;
	return (receiver->*thunk.member)(subject, position, 0);
}

static bool callPositionHandler(Rva0021C820Call *receiver,
	void *subject, void *entry, void *position)
{
	union { void (*raw)(); Rva0021C820Member member; } thunk;
	thunk.raw = j_00022b2e;
	return (receiver->*thunk.member)(subject, entry, position);
}

class Rva0021C820Owner
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
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
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
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual bool slot49();

	bool run(void *subject, void *entry, void *context);
};

// ?run@Rva0021C820Owner@@QAE_NPAX00@Z
bool Rva0021C820Owner::run(void *subject, void *entry, void *context)
{
	if (subject == 0 || entry == 0 || context == 0)
		return false;

	if (slot49())
	{
		const unsigned char flags =
			*reinterpret_cast<const unsigned char *>(
				reinterpret_cast<const unsigned char *>(subject) + 0x94);
		if ((flags & 0x10) != 0)
		{
			return callPositionRange(reinterpret_cast<Rva0021C820Call *>(entry),
				subject, context);
		}
	}

	return callPositionHandler(reinterpret_cast<Rva0021C820Call *>(this),
		subject, entry, context);
}
