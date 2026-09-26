struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeObjXQ
{
public:
	unsigned char m_bfmeHeadXQ[0x38];
	Coord3D m_bfme38XQ;
};

class BfmeTeamXQ
{
public:
	void bfmeEstimateXQ(Coord3D *out);
};

struct Rva00367E30Logic
{
	BfmeObjXQ *bfmeFindXQ(void *id);
};

class TeamFactory
{
public:
	BfmeTeamXQ *bfmeFindXQ(void *id);
};

extern Rva00367E30Logic *TheBfmeGameLogic;
extern TeamFactory *TheTeamFactory;

class BfmeCfgXQ
{
public:
	unsigned char m_bfmeHeadXQ[0x44];
	void *m_bfme44XQ;
	void *m_bfme48XQ;
};

class BfmeSinkXQ
{
public:
	virtual void bfmeV0XQ() = 0;
	virtual void bfmeV1XQ() = 0;
	virtual void bfmeV2XQ() = 0;
	virtual void bfmeV3XQ() = 0;
	virtual void bfmeV4XQ() = 0;
	virtual void bfmeV5XQ() = 0;
	virtual int bfmeRunXQ() = 0;
};

class BfmeHostXQ
{
public:
	int bfmeStepXQ();

	unsigned char m_bfmeHeadXQ[0x1c];
	BfmeCfgXQ *m_bfme1CXQ;
	unsigned char m_bfmeGapXQ[0xc];
	Coord3D m_bfme2CXQ;
	unsigned char m_bfmeGap2XQ[8];
	BfmeSinkXQ *m_bfme40XQ;
};

int BfmeHostXQ::bfmeStepXQ()
{
	if (m_bfme40XQ == 0)
		return -1;

	BfmeCfgXQ *cfg = m_bfme1CXQ;
	BfmeObjXQ *obj = TheBfmeGameLogic->bfmeFindXQ(cfg->m_bfme44XQ);
	BfmeTeamXQ *team = TheTeamFactory->bfmeFindXQ(cfg->m_bfme48XQ);

	if (obj)
		m_bfme2CXQ = obj->m_bfme38XQ;
	else if (team)
		team->bfmeEstimateXQ(&m_bfme2CXQ);

	return m_bfme40XQ->bfmeRunXQ();
}

class BfmeHost2XQ
{
public:
	int bfmeStep2XQ();

	unsigned char m_bfmeHeadXQ[0x1c];
	BfmeCfgXQ *m_bfme1CXQ;
	unsigned char m_bfmeGapXQ[0xc];
	Coord3D m_bfme2CXQ;
	unsigned char m_bfmeGap2XQ[8];
	BfmeSinkXQ *m_bfme40XQ;
};

int BfmeHost2XQ::bfmeStep2XQ()
{
	if (m_bfme40XQ == 0)
		return -1;

	BfmeCfgXQ *cfg = m_bfme1CXQ;
	BfmeObjXQ *obj = TheBfmeGameLogic->bfmeFindXQ(cfg->m_bfme44XQ);
	BfmeTeamXQ *team = TheTeamFactory->bfmeFindXQ(cfg->m_bfme48XQ);

	if (obj)
		m_bfme2CXQ = obj->m_bfme38XQ;
	else if (team)
		team->bfmeEstimateXQ(&m_bfme2CXQ);

	return m_bfme40XQ->bfmeRunXQ();
}
