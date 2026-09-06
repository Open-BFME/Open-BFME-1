// cl: /DNDEBUG /MD /EHsc
// BFME Object selection notification, retail 0x001C8830, 336 bytes.

typedef unsigned int UnsignedInt;

class BfmeOverridable
{
public:
	virtual ~BfmeOverridable();
	const BfmeOverridable *getFinalOverride() const;

	BfmeOverridable *m_nextOverride;
};

class ThingTemplate : public BfmeOverridable
{
public:
	char m_pad008[0xC8 - 0x08];
	signed char m_kindOf;
};

class Player;

class BfmeBlockVKP
{
public:
	unsigned char m_data[0x14];
};

class BfmeSelectionFlags
{
public:
	bool test(unsigned int bit) const
	{
		return (m_bits & (1u << bit)) != 0;
	}

	void clear(unsigned int bit)
	{
		m_bits &= ~(1u << bit);
	}

	void set(unsigned int bit)
	{
		m_bits |= 1u << bit;
	}

	UnsignedInt m_bits;
};

void j_0001343f();

class BfmeNotifyThunk
{
public:
	void notify(BfmeBlockVKP *block, int unused1, int unused2);
};

#pragma comment(linker, "/alternatename:?notify@BfmeNotifyThunk@@QAEXPAVBfmeBlockVKP@@HH@Z=?j_0001343f@@YAXXZ")

class BfmeUpdVKP
{
public:
	void bfmeUpdateVKP();
};

class Object;

class Drawable
{
};

class DrawableApplyPendingThunk
{
public:
    void apply(bool immediate);
};

#pragma comment(linker, "/alternatename:?apply@DrawableApplyPendingThunk@@QAEX_N@Z=?j_0002d439@@YAXXZ")

class BfmeSelectionResult;

class BfmeSelectionInterface
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
	virtual BfmeSelectionResult *getRva001C8830Interface();
};

class BfmeSelectionResult
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
	virtual void notifySelection(Player *player);
};

class BfmeContainModule
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
	virtual BfmeSelectionResult *getRva001C8830Interface();
};

enum ObjectID
{
	OBJECT_ID_INVALID = 0
};

class BfmeTeam
{
public:
	Player *bfmeGetControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class Object
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
	virtual Drawable *getDrawable();

	bool testStatus(int status) const;
	void notifyRva001C8830(Player *player);

	ThingTemplate *m_template;
	unsigned char m_pad008[0x78 - 0x08];
	ObjectID m_id;
	unsigned char m_pad07C[0x80 - 0x7C];
	Drawable *m_drawable;
	unsigned char m_pad084[0x110 - 0x84];
	BfmeBlockVKP m_conditionFlags;
	BfmeSelectionFlags m_selectionFlags;
	UnsignedInt m_status128;
	unsigned char m_pad12C[0x134 - 0x12C];
	UnsignedInt m_status134;
	unsigned char m_pad138[0x1FC - 0x138];
	BfmeContainModule *m_contain;
	unsigned char m_pad200[0x204 - 0x200];
	BfmeUpdVKP *m_ai;
	unsigned char m_pad208[0x214 - 0x208];
	Object *m_containedBy;
	unsigned char m_pad218[0x23C - 0x218];
	BfmeTeam *m_team;
};

void Object::notifyRva001C8830(Player *player)
{
	Drawable *drawable = getDrawable();
	ThingTemplate *thing = m_template;
	Object *other;
	if (thing && thing->m_nextOverride)
	{
		thing = (ThingTemplate *)thing->m_nextOverride->getFinalOverride();
	}
	if (thing->m_kindOf & 0x80)
		return;
	if (m_status128 & 0x8000)
		return;
	if (m_status134 & 0x1000)
		return;

	BfmeSelectionResult *selection = 0;
	if (m_contain)
	{
		BfmeContainModule *contain = m_contain;
		selection = contain->getRva001C8830Interface();
	}

	if (m_selectionFlags.test(0))
	{
		m_selectionFlags.clear(0);
		if (m_drawable)
			((BfmeNotifyThunk *)m_drawable)->notify(&m_conditionFlags, 0, 0);
		if (m_ai)
			m_ai->bfmeUpdateVKP();
	}

	if (drawable)
	{
		((DrawableApplyPendingThunk *)drawable)->apply(false);

		if (!selection && !m_containedBy && !testStatus(0x25))
		{
			other = TheBfmeGameLogic->findObjectByID(m_id);
			if (other)
			{
				BfmeContainModule *otherContain = other->m_contain;
				if (otherContain && otherContain->getRva001C8830Interface())
					return;
			}
		}
	}

	Player *owner = m_team ? m_team->bfmeGetControllingPlayer() : 0;
	if (player == owner && !m_selectionFlags.test(0))
	{
		m_selectionFlags.set(0);
		if (m_drawable)
			((BfmeNotifyThunk *)m_drawable)->notify(&m_conditionFlags, 0, 0);
		if (m_ai)
			m_ai->bfmeUpdateVKP();
	}
	if (selection)
		selection->notifySelection(player);
}
