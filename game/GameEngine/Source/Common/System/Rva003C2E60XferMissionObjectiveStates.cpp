// ?xferMissionObjectiveStates@Rva003C2E60Owner@@QAEXPAVXfer@@@Z
// Retail 0x003C2E60. The owner is address-qualified because no named caller
// or vtable claim identifies it. Its vector at +0x84 uses the two-byte
// MissionObjectiveState element established by the adjacent matched bodies.
// stlport

#define BFME_STLP_NODE_ALLOC
#include <vector>
#include "xfer.h"

typedef bool Bool;

struct MissionObjectiveState
{
	Bool m_visible;
	Bool m_completed;
};

typedef _STL::vector<MissionObjectiveState> MissionObjectiveStateVector;

Xfer *Rva003C2830XferMissionObjectiveStateVector(Xfer *, MissionObjectiveStateVector *);

class Rva003C2E60Owner
{
public:
	void xferMissionObjectiveStates(Xfer *xfer);

private:
	unsigned char m_unmodelled00[0x84];
	MissionObjectiveStateVector m_states;
};

void Rva003C2E60Owner::xferMissionObjectiveStates(Xfer *xfer)
{
	if (xfer->IsLoading())
		m_states.clear();
	Rva003C2830XferMissionObjectiveStateVector(xfer, &m_states);
}
