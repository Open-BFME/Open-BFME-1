// cl: /O2 /DNDEBUG /MD /EHsc
// Toggles the BFME house-color indicator over GameLogic's object chain.

typedef bool Bool;

// Both bodies retail calls from this loop (0x00018CF5 and 0x0001B9A5) are
// five-byte ILT thunks, not bodies: the ledger defines each under its
// address-claimed name (game/gen_small/thunks_011.cpp and thunks_012.cpp), so
// the calls are spelled here as member-pointer calls onto those thunk
// addresses, which is what puts the object pointer in ECX the way the thiscall
// the retail source used did.
extern void j_00018cf5();
extern void j_0001b9a5();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
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

	Rva0038AD90Template *m_template;
	char m_pad08[0x80];
	Rva0038AD90Object *m_next;
};

typedef void (Drawable::*SetIndicatorThunk)(Bool flag);
typedef void (Rva0038AD90Object::*RefreshCompletedUpgradesThunk)(void);

union SetIndicatorThunkCast
{
	void (__cdecl *freeFunction)(Bool flag);
	SetIndicatorThunk memberFunction;
};

union RefreshCompletedUpgradesThunkCast
{
	void (__cdecl *freeFunction)(void);
	RefreshCompletedUpgradesThunk memberFunction;
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
			SetIndicatorThunkCast setIndicator;
			setIndicator.freeFunction = reinterpret_cast<void (__cdecl *)(Bool)>(&::j_00018cf5);
			(drawable->*setIndicator.memberFunction)(enabled);

			RefreshCompletedUpgradesThunkCast refresh;
			refresh.freeFunction = reinterpret_cast<void (__cdecl *)(void)>(&::j_0001b9a5);
			(object->*refresh.memberFunction)();
		}
	}
}
