// cl: /DNDEBUG /MD /EHsc
// Retail 0x00235380 has no named caller or proven semantic owner. Keep this
// type and method address-derived. The body calls slots 16 and 7 and walks a
// circular list at this-0xAC; the single 32-bit stack argument is unused.
// The position and orientation call views describe their observed thiscall
// shapes only; their semantic interfaces are not established here.

struct Rva00235380Coord
{
	float x;
	float y;
	float z;
};

class Rva00235380Item
{};

extern void j_0001621b();
extern void j_000399A5();

class Rva00235380PositionCall
{
public:
	void apply(const Rva00235380Coord *position, bool update);
};

class Rva00235380OrientationCall
{
public:
	void apply(float angle);
};

static __forceinline void setRva00235380Position(
	Rva00235380Item *item, const Rva00235380Coord *position, bool update)
{
	typedef void (Rva00235380PositionCall::*Function)(
		const Rva00235380Coord *, bool);
	union
	{
		void (*raw)(void);
		Function member;
	} thunk;
	thunk.raw = j_0001621b;
	(reinterpret_cast<Rva00235380PositionCall *>(item)->*thunk.member)(
		position, update);
}

static __forceinline void setRva00235380Orientation(
	Rva00235380Item *item, float angle)
{
	typedef void (Rva00235380OrientationCall::*Function)(float);
	union
	{
		void (*raw)(void);
		Function member;
	} thunk;
	thunk.raw = j_000399A5;
	(reinterpret_cast<Rva00235380OrientationCall *>(item)->*thunk.member)(
		angle);
}

struct Rva00235380Node
{
	Rva00235380Node *next;
	Rva00235380Node *previous;
	Rva00235380Item *item;
};

class Rva00235380
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual Rva00235380Coord *slot07(
		Rva00235380Coord *scratch,
		Rva00235380Item *item,
		float *angle) = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;

	void rva00235380(unsigned int unused);
};

void Rva00235380::rva00235380(unsigned int unused)
{
	slot16();
	Rva00235380Node *volatile *list =
		(Rva00235380Node *volatile *)((char *)this - 0xac);
	Rva00235380Node *head = *list;
	Rva00235380Node *node = head->next;
	if (node != head)
	{
		do
		{
			Rva00235380Item *item = node->item;
			Rva00235380Coord scratch;
			float angle;
			Rva00235380Coord position;
			Rva00235380Coord *result = slot07(&scratch, item, &angle);
			position = *result;
			setRva00235380Position(item, &position, false);
			setRva00235380Orientation(item, angle);
			node = node->next;
		} while (node != *list);
	}
}
