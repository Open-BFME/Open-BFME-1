#pragma once

#include "../Common/ScalarTypes.h"

// Existing provider view, shared with an opaque receiver-only caller.
// Its placeholder identity is retained; no new semantic class name is inferred.
class ThingTemplate;
class ContainModuleInterface;
class Team;

class BfmeSubBIC
{
public:
	virtual void slot00();
	int rva001CABE0();
	ContainModuleInterface *getContain() const { return m_contain; }

	ThingTemplate *m_template;
	unsigned char m_pad08[0x1f4];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x3c];
	Team *m_team;
	UnsignedInt m_originalTeamName;
	int m_indicatorColor;
};
