// cl: /O2 /DNDEBUG /MD /EHsc
// Toggles the BFME house-color indicator over GameLogic's object chain.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void bfmeSetIndicatorOn(Bool enabled);
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();
};

struct Rva0038AD90Template
{
	char m_pad00[4];
	BfmeOverridable *m_override;
	char m_pad08[0xCC];
	unsigned int m_kindOf;
};

class Rva0038AD90Object
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual Drawable *getDrawable();
	void bfmeRefreshCompletedUpgrades();

	Rva0038AD90Template *m_template;
	char m_pad08[0x80];
	Rva0038AD90Object *m_next;
};

class Rva0038AD90GameLogic
{
public:
	void setObjectIndicators(Bool enabled);

private:
	char m_pad00[0xA8];
	Rva0038AD90Object *m_objects;
};

void Rva0038AD90GameLogic::setObjectIndicators(Bool enabled)
{
	for (Rva0038AD90Object *object = m_objects; object; object = object->m_next)
	{
		if (!enabled)
		{
			Rva0038AD90Template *thing = object->m_template;
			if (thing && thing->m_override)
				thing = (Rva0038AD90Template *)thing->m_override->friend_getFinalOverride();
			if (thing->m_kindOf & 0x00800000)
				continue;
		}

		Drawable *drawable = object->getDrawable();
		if (drawable)
		{
			drawable->bfmeSetIndicatorOn(enabled);
			object->bfmeRefreshCompletedUpgrades();
		}
	}
}
