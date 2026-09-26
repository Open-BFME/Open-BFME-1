// BFME Player selection setter: complete 102-byte body at 0x000D2C60.
//
// The retail Player embeds the current-selection pointer at +0x67c.  The
// selection object itself is the 0x1c-byte, one-vptr/two-vector object whose
// recovered helper bodies live at 0x0018b850/0x0018b8b0/0x0018b9a0.  Keep the
// BFME view local: the checked-in ZH Player/Squad headers have different
// inheritance and absolute offsets.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned char Bool;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

typedef _STL::vector<ObjectID> VecObjectID;

class AIGroup;
extern int Gen01083E78;

// This is the BFME shape at Player+0x67c: one vptr followed by the two
// STLport vector triples.  The body identity is kept address-derived because
// the retail vtable has not been assigned a trusted class name.
class Gen_0018B850
{
public:
	// The 0x1c-byte allocation is initialized inline in both Player methods.
	// Keep the storage as scalar fields so MSVC emits the retail vptr literal
	// and six zero stores instead of an EH-bearing virtual constructor path.
	Gen_0018B850()
		: m_vptr(&Gen01083E78), m_04(0), m_08(0), m_0C(0),
		  m_10(0), m_14(0), m_18(0)
	{
	}

	void bfmeClear(void);

private:
	int *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

// The body at 0x0018b8b0 is the vector assignment used by the retail
// set-current-selection path.  Its address-derived argument is deliberately
// kept separate from AIGroup; the retail getter thunk is shared with
// AIGroup::getAllIDs at 0x00154ad0.  The same body is also reached by the
// historical Rva001705A0Inner::applyAlternate alias, so neither alias is
// asserted as the unique owning C++ class here.
class Rva0018B8B0Arg;
class Rva0018B8B0Holder
{
public:
	void apply(Rva0018B8B0Arg *arg, bool clearFirst);
};

class Rva0018B9A0Holder
{
public:
	void addObjectID(ObjectID id);
};

class AIGroup
{
public:
	const VecObjectID &getAllIDs(void) const;
};

class Rva0018B8B0Arg
{
};

struct BFMEPlayerSelectionView
{
	unsigned char pad[0x67c];
	Gen_0018B850 *m_currentSelection;
};

class Player
{
public:
	void setCurrentlySelectedAIGroup(AIGroup *group);
	void addAIGroupToCurrentSelection(AIGroup *group);

	unsigned char m_pad[0x67c];
	Gen_0018B850 *m_currentSelection;
};

// ?setCurrentlySelectedAIGroup@Player@@QAEXPAVAIGroup@@@Z
void Player::setCurrentlySelectedAIGroup(AIGroup *group)
{
	if (m_currentSelection == NULL)
	{
		m_currentSelection = new Gen_0018B850;
	}
	m_currentSelection->bfmeClear();

	if (group != NULL)
	{
		((Rva0018B8B0Holder *)m_currentSelection)->apply((Rva0018B8B0Arg *)group, true);
	}
}

// ?addAIGroupToCurrentSelection@Player@@QAEXPAVAIGroup@@@Z
void Player::addAIGroupToCurrentSelection(AIGroup *group)
{
	if (group == NULL)
		return;

	if (m_currentSelection == NULL)
	{
		m_currentSelection = new Gen_0018B850;
	}

	VecObjectID ids(group->getAllIDs());
	int count = (int)ids.size();
	ObjectID *base = ids.begin();
	for (int i = 0; i < count; ++i)
	{
		((Rva0018B9A0Holder *)m_currentSelection)->addObjectID(base[i]);
	}
}

