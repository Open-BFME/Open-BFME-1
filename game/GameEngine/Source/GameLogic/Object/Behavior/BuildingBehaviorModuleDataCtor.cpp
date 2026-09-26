// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModuleFactory's data-create proc 0x001146F0 allocates 0x24 and
// runs this body, which identifies BuildingBehaviorModuleData.
//
// The four strings at +0x08 are an ARRAY member, which is why retail reaches
// them through the compiler's eh vector constructor iterator with the string's
// constructor ILT 0x00017BD9 and destructor ILT 0x0000D828 as arguments; the
// three dwords above them are the initialiser list, and the counted loop that
// follows is set("", 0) over the array.

class RetailLayoutString
{
public:
	RetailLayoutString(void);
	~RetailLayoutString(void);

	void set(const char *text, int length);

private:
	char *m_data;
};

// The dword at +0x04 is a destructible BASE, not a member: retail stores EH
// state 0 BEFORE the vftable store, and only a base subobject is constructed
// that early. Spelled as a member it still produces state 0, but MSVC then
// hoists the vftable store to the top of the body instead of scheduling it
// into the array constructor's argument window.
class BBMD_Owned
{
public:
	~BBMD_Owned(void) { m_p = 0; }

private:
	void *m_p;
};

class BBMD_Handle
{
public:
	BBMD_Handle(int) { m_p = 0; }
	~BBMD_Handle(void) { m_p = 0; }

private:
	void *m_p;
};

class BuildingBehaviorModuleData : public BBMD_Owned
{
public:
	BuildingBehaviorModuleData();
	virtual ~BuildingBehaviorModuleData();

private:
	RetailLayoutString m_names[4];		// this+0x08 .. 0x14
	unsigned int m_x18;
	unsigned int m_x1c;
	BBMD_Handle m_x20;
};

// ??0BuildingBehaviorModuleData@@QAE@XZ
BuildingBehaviorModuleData::BuildingBehaviorModuleData()
	: m_x18(0), m_x1c(0), m_x20(0)
{
	for (int i = 0; i < 4; i++)
		m_names[i].set("", 0);
}
