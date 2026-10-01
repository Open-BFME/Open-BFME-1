struct BfmeMatETE
{
	unsigned char m_bfmeBodyETE[0x30];
};

class BfmeClientETE
{
public:
	virtual void bfmeSlot00ETE();
	virtual void bfmeSlot01ETE();
	virtual void bfmeSlot02ETE();
	virtual void bfmeSlot03ETE();
	virtual void bfmeSlot04ETE();
	virtual void bfmeSlot05ETE();
	virtual void bfmeSlot06ETE();
	virtual void bfmeSlot07ETE();
	virtual void bfmeSlot08ETE();
	virtual void bfmeSlot09ETE();
	virtual void bfmeSlot10ETE();
	virtual void bfmeSlot11ETE();
	virtual void bfmeSlot12ETE();
	virtual void bfmeSlot13ETE();
	virtual void bfmeSlot14ETE();
	virtual void bfmeSlot15ETE();
	virtual void bfmeSlot16ETE();
	virtual void bfmeSlot17ETE();
	virtual void bfmeSlot18ETE();
	virtual void bfmeSlot19ETE();
	virtual void bfmeSlot20ETE();
	virtual void bfmeSlot21ETE();
	virtual void bfmeSlot22ETE();
	virtual void bfmeSlot23ETE();
	virtual void bfmeSlot24ETE();
	virtual void bfmeSlot25ETE();
	virtual unsigned int bfmeSlot26ETE();
};

// The 0x012F1464 global is EA's `GameClient *TheGameClient`, defined once in
// GameClient.cpp; only the pointee type may differ per TU, so it is forward
// declared here and this TU's slot-26 view is applied at the uses.
class GameClient;
extern GameClient *TheGameClient;

class BfmeEngineETE
{
public:
	unsigned char m_bfmeHeadETE[0x38];
	float m_bfme38ETE;
};

extern BfmeEngineETE *g_bfmeEngineETE;

// 0x008D8480 is Matrix3D::Lerp (matrix3d.cpp, matched); BfmeMatETE is this
// TU's 48-byte view of a Matrix3D, kept so the accessor's mangled name (its
// ledger identity) is unchanged.
class Matrix3D
{
public:
	static void Lerp(const Matrix3D &A, const Matrix3D &B, float factor, Matrix3D &result);
	unsigned char m_bfmeBody[0x30];
};

class BfmeHostETE
{
public:
	BfmeMatETE *bfmeGetETE();

	unsigned char m_bfmeHeadETE[0x168];
	BfmeMatETE m_bfme168ETE;
	BfmeMatETE m_bfme198ETE;
	BfmeMatETE m_bfme1c8ETE;
	unsigned char m_bfmeGapETE[4];
	unsigned int m_bfme1fcETE;
	unsigned char m_bfmeMidETE[0x104];
	unsigned int m_bfme304ETE;
};

BfmeMatETE *BfmeHostETE::bfmeGetETE()
{
	if (m_bfme304ETE <= ((BfmeClientETE *)TheGameClient)->bfmeSlot26ETE())
		return &m_bfme198ETE;

	if (m_bfme1fcETE != ((BfmeClientETE *)TheGameClient)->bfmeSlot26ETE())
	{
		Matrix3D::Lerp(*reinterpret_cast<const Matrix3D *>(&m_bfme168ETE),
			*reinterpret_cast<const Matrix3D *>(&m_bfme198ETE), g_bfmeEngineETE->m_bfme38ETE,
			*reinterpret_cast<Matrix3D *>(&m_bfme1c8ETE));

		m_bfme1fcETE = ((BfmeClientETE *)TheGameClient)->bfmeSlot26ETE();
	}

	return &m_bfme1c8ETE;
}
