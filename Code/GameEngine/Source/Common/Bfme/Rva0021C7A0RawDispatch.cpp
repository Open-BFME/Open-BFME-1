// Address-derived reconstruction of retail RVA 0x0021C7A0.
//
// The image proves a __thiscall bool routine with three pointer-sized stack
// arguments.  No named caller or vtable slot names this owner, so the class
// and method remain deliberately address-derived.  The virtual predicate is
// slot 49 (+0xC4); the two return-valued callees are the existing canonical
// Weapon::isWithinAttackRange ILT and the existing 0x0021E520 ILT thunk.

class Object;

class Weapon
{
public:
	bool isWithinAttackRange(const Object *source,
		const Object *target, int extra) const;
};

extern void j_00020cf7(void);

struct Rva0021E520Thunk
{
	bool call(void *subject, void *entry, void *context);
};

typedef bool (Rva0021E520Thunk::*Rva0021E520Call)(
	void *subject, void *entry, void *context);

static bool callRva0021E520(Rva0021E520Thunk *owner,
	void *subject, void *entry, void *context)
{
	union
	{
		void (*asFunction)();
		Rva0021E520Call asMember;
	} functionCast;
	functionCast.asFunction = j_00020cf7;
	return (owner->*functionCast.asMember)(subject, entry, context);
}

class Rva0021C7A0Owner
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

// ?run@Rva0021C7A0Owner@@QAE_NPAX00@Z
bool Rva0021C7A0Owner::run(void *subject, void *entry, void *context)
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
			return reinterpret_cast<const Weapon *>(entry)->isWithinAttackRange(
				reinterpret_cast<const Object *>(subject),
				reinterpret_cast<const Object *>(context), 0);
		}
	}

	return callRva0021E520(reinterpret_cast<Rva0021E520Thunk *>(this),
		subject, entry, context);
}
