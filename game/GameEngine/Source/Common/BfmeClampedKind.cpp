// Open-BFME5 conversion for the clamped global-state read at 0x00695E80.

struct BfmeKindRow
{
	unsigned short kind;
	char m_pad2[6];
};

class BfmeStateEE
{
public:
	char m_pad0[0x170];
	BfmeKindRow rows[2];
	char m_pad180[0x154c];
	int activeRow;
};

// retail 0x012ED5AC is ?TheGameLODManager@@3PAVGameLODManager@@A; this TU
// keeps its own view of the object and casts at the read.
class GameLODManager;
extern GameLODManager *TheGameLODManager;

class BfmeKindOwner
{
public:
	void refreshKind(void);

private:
	char m_pad0[0x628];
	unsigned short m_kind;
};

void BfmeKindOwner::refreshKind(void)
{
	if (reinterpret_cast<BfmeStateEE *>(TheGameLODManager) != 0 &&
		reinterpret_cast<BfmeStateEE *>(TheGameLODManager)->activeRow >= 0 &&
		reinterpret_cast<BfmeStateEE *>(TheGameLODManager)->activeRow < 2)
	{
		m_kind = reinterpret_cast<BfmeStateEE *>(TheGameLODManager)
			->rows[reinterpret_cast<BfmeStateEE *>(TheGameLODManager)->activeRow].kind;
		if (m_kind <= 2)
			return;
	}

	m_kind = 2;
}
