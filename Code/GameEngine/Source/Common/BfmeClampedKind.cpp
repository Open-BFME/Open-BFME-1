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

extern BfmeStateEE *g_bfmeStateEE;

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
	if (g_bfmeStateEE != 0 && g_bfmeStateEE->activeRow >= 0 && g_bfmeStateEE->activeRow < 2)
	{
		m_kind = g_bfmeStateEE->rows[g_bfmeStateEE->activeRow].kind;
		if (m_kind <= 2)
			return;
	}

	m_kind = 2;
}
