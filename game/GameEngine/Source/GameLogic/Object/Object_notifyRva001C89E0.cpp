// cl: /DNDEBUG /MD /EHsc
// BFME Object deselection notification, retail 0x001C89E0, 123 bytes.
//
// GameLogic::deselectObject at 0x00382F50 passes its Object argument as this
// and the selected Player as the only stack argument through ILT 0x000380CD.
// The paired, matched Object::notifyRva001C8830 body proves the Object field
// layout and the selection-side slots of the two interfaces used below.

typedef unsigned int UnsignedInt;

class Player;

class ModelConditionFlags
{
public:
	UnsignedInt m_bits[10];
};

class ModelConditionPrefix
{
public:
	unsigned char m_data[0x14];
};

class SelectionFlags
{
public:
	bool test(UnsignedInt bit) const
	{
		return (m_bits & (1u << bit)) != 0;
	}

	void clear(UnsignedInt bit)
	{
		m_bits &= ~(1u << bit);
	}

	UnsignedInt m_bits;
};

// ContainModuleInterface slot 26 returns this real secondary interface.  The
// matched HordeContain implementation returns its subobject at +0xE4; its
// completed-object vtable 0x010AED58 supplies the selection slots below;
// 0x010AE8E0 is the corresponding construction/base table.
class HordeContainInterface
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
	virtual void notifySelection(Player *player);       // vtable +0xC0
	virtual void notifyDeselection(Player *player);     // vtable +0xC4
};

class ContainModuleInterface
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
	virtual HordeContainInterface *getHordeContainInterface();
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags,
		UnsignedInt forceReplace, UnsignedInt value);
};

class AIUpdateInterface
{
public:
	virtual void friend_notifyStateMachineChanged();
};

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

	void notifyRva001C89E0(Player *player);

};

// The matched selection-side body establishes the complete retail offsets.
// Keep the method body on an offset-faithful view so this TU does not claim
// unrecovered Object members between the fields it actually accesses.
class ObjectDeselectLayout
{
public:
	void *m_vtable;                                        // +0x000
	unsigned char m_pad004[0x80 - 0x04];
	Drawable *m_drawable;                                  // +0x080
	unsigned char m_pad084[0x110 - 0x84];
	ModelConditionPrefix m_conditionPrefix;                // +0x110
	SelectionFlags m_selectionFlags;                       // +0x124
	unsigned char m_conditionTail[0x138 - 0x128];
	unsigned char m_pad138[0x1FC - 0x138];
	ContainModuleInterface *m_contain;                     // +0x1FC
	unsigned char m_pad200[0x204 - 0x200];
	AIUpdateInterface *m_ai;                               // +0x204
	unsigned char m_pad208[0x23C - 0x208];
	Team *m_team;                                          // +0x23C
};

void Object::notifyRva001C89E0(Player *player)
{
	ObjectDeselectLayout *self = reinterpret_cast<ObjectDeselectLayout *>(this);
	Player *owner = self->m_team ? self->m_team->getControllingPlayer() : 0;

	if (player == owner && self->m_selectionFlags.test(0))
	{
		self->m_selectionFlags.clear(0);
		if (self->m_drawable)
			self->m_drawable->replaceModelConditionState(
				*reinterpret_cast<ModelConditionFlags *>(&self->m_conditionPrefix), 0, 0);
		if (self->m_ai)
			self->m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
	}

	ContainModuleInterface *contain = self->m_contain;
	if (contain)
	{
		HordeContainInterface *selection = contain->getHordeContainInterface();
		if (selection)
			selection->notifyDeselection(player);
	}
}
