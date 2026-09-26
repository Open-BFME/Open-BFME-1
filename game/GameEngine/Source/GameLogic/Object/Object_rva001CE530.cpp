// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// BFME Object removal helper at retail RVA 0x001CE530.

#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags() { }

	void set(int index)
	{
		m_bits._Unchecked_set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Gen_00411DD0
{
public:
	void bfmeSet(Bool value);

	char m_pad00[0x3AC];
	Bool m_enabled;
};

class Object;

class GameMessage
{
public:
	void appendObjectIDArgument(UnsignedInt value);
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
	virtual GameMessage *appendMessage(UnsignedInt type) = 0;
};

extern MessageStream *TheMessageStream;

class Radar
{
public:
	void removeObject(Object *object);
};

extern Radar *TheRadar;

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

class AI
{
private:
	char m_pad00[0x0C];

public:
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

struct Rva00595160Argument;

class Rva00595160
{
public:
	void update(Rva00595160Argument *argument);
};

class Glo012F4B98Type
{
private:
	char m_pad00[0x2B8];

public:
	Rva00595160 m_subobject;
};

extern Glo012F4B98Type *Glo012F4B98;

class Rva002EE330PlayerList
{
private:
	char m_pad00[0x0C];

public:
	Player *m_localPlayer;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class BfmeThingXV
{
public:
	void bfmeStopXV();
};

class Gen001C8010
{
public:
	void setSold();
};

class BfmeObjectView
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
	virtual Gen_00411DD0 *getDrawable() = 0;
};

class Object : public BfmeObjectView
{
public:
	void rva001CE530();
	void setStatus(const ObjectStatusMaskType &status, Bool set);

private:
	char m_pad04[0x70];
	UnsignedInt m_id;
	char m_pad78[0x18];
	UnsignedInt m_statusWord0;
	UnsignedInt m_statusWord1;
	char m_pad98[0x1A4];
	Team *m_team;
	char m_pad240[0x16C];
};

// ?rva001CE530@Object@@QAEXXZ
void Object::rva001CE530()
{
	if ((m_statusWord1 & 0x40000) != 0)
		return;

	Gen_00411DD0 *drawable = getDrawable();
	if (drawable != 0)
	{
		drawable->bfmeSet(true);

		Player *controller;
		if (m_team != 0)
			controller = m_team->getControllingPlayer();
		else
			controller = 0;

		if (controller == Rva002EE330ThePlayers->m_localPlayer &&
			drawable->m_enabled != 0)
		{
			GameMessage *message = TheMessageStream->appendMessage(0x3EC);
			message->appendObjectIDArgument(m_id);
		}
	}

	TheRadar->removeObject(this);
	TheAI->m_pathfinder->removeObjectFromPathfindMap(this);

	if (Glo012F4B98 != 0)
		Glo012F4B98->m_subobject.update((Rva00595160Argument *)this);

	((BfmeThingXV *)this)->bfmeStopXV();
	((Gen001C8010 *)this)->setSold();

	ObjectStatusMaskType status;
	status.set(50);
	setStatus(status, true);
}
