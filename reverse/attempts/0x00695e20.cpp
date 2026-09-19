// ?d_00695e20@@YAXXZ
// partial score=0.95 date=2026-09-19
// cl: /DNDEBUG /MD /EHsc

// Retail 0x00695E20 checks this object's LOD selector against the active
// GameLODManager row.  The surrounding bytes prove the selector offset and
// the two-byte row range, but they do not prove a semantic method name.

class GameLODManager
{
public:
	char m_padding0[0x174];
	bool m_rowFlags[2][8];
	char m_padding1[0x16cc - 0x184];

public:
	int m_activeRow;
};

extern GameLODManager *TheGameLODManager;

class Rva00695E20LodGate
{
public:
	bool check() const;

private:
	char m_padding0[0xb60];
	int m_lodSelector;
};

bool Rva00695E20LodGate::check() const
{
	if (m_lodSelector > 0 && m_lodSelector <= 5)
	{
		GameLODManager *lod = TheGameLODManager;
		if (lod == 0)
			goto true_return;

		goto row_check;

	true_return:
		return true;

	row_check:
		int row = lod->m_activeRow;
		if (row >= 0 && row < 2)
			return lod->m_rowFlags[row][0];

		goto true_return;
	}

	return false;
}
