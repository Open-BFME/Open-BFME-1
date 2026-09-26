// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Complete Player::countObjects body at RVA 0x000CDE00, 149 bytes.
// The Ghidra 143-byte extent omitted six live epilogue bytes.
// Typed script-condition caller via ILT 0x1FF1E proves two BitFlags<192> values.

typedef int Int;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	// 192 bits is six dwords.  The $0MA decoration is established by the
	// typed retail Player ILT and by the caller's 24-byte argument copies.
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

class TeamPrototype
{
public:
	Int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
};

// The counter body lives at RVA 0x000F40E0; the observed call encodes its
// ILT at RVA 0x0000CC11. Both masks have six words and the callee returns ret0x30.

// In BFME, Player+0x288 contains the address of this circular sentinel.  A
// node's next link is at +0x00, previous at +0x04, and TeamPrototype value at
// +0x08.  This pointer view is the same layout used by the matched Player
// object walkers; using an embedded std::list view would place the member at
// the ZH offset and lose the BFME +0x288 identity.
class BfmePlayerTeamNode
{
public:
	BfmePlayerTeamNode *m_next;
	BfmePlayerTeamNode *m_prev;
	TeamPrototype *m_teamPrototype;
};

class Player
{
public:
	Int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);

private:
	unsigned char m_bfmePrefix[0x288];
	BfmePlayerTeamNode *m_playerTeamPrototypes;
};

// ?countObjects@Player@@QAEHV?$BitFlags@$0MA@@@0@Z
Int Player::countObjects(KindOfMaskType setMask, KindOfMaskType clearMask)
{
	Int retVal = 0;

	BfmePlayerTeamNode *node = m_playerTeamPrototypes->m_next;
	while (node != m_playerTeamPrototypes)
	{
		retVal += node->m_teamPrototype->countObjects(setMask, clearMask);
		node = node->m_next;
	}

	return retVal;
}
