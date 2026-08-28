// cl: /DNDEBUG /MD /EHsc

// A base constructed out of line, then this class's vptr, then a layout-string
// member at +0x5C given a literal.
//
// The base owns offset zero: retail passes this straight to its constructor with
// no lea, so the vptr belongs to the base and this class merely overwrites it.
// Introducing the vtable in the derived class instead puts the base at +4 and
// adds a lea ecx,[esi+4] that retail does not have.
//
// ecx is loaded with the member's address before the vptr store and reused for
// both the member's own zeroing and the set call that follows -- it is the
// thiscall argument being set up early, not a separate cursor.
//
// Two unwind states, 0 and 1, count the two destructible things built before the
// call that can throw: the base and the member. The literal's length is pushed
// as 0x2F, which is exactly its 47 characters.
class RetailLayoutString
{
public:
	RetailLayoutString() : m_data(0) {}
	~RetailLayoutString();

	void set(const char *text, int length);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();
	virtual ~ActiveBodyModuleData();

private:
	unsigned char m_head[0x58];
};

class SymbioticStructuresBodyModuleData : public ActiveBodyModuleData
{
public:
	SymbioticStructuresBodyModuleData();

private:
	RetailLayoutString m_layout;
};

// ??0SymbioticStructuresBodyModuleData@@QAE@XZ
SymbioticStructuresBodyModuleData::SymbioticStructuresBodyModuleData()
{
	m_layout.set("Not likely to duplicate this name, is he, Fred?", 47);
}
