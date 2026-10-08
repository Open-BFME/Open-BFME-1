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

class Object;

// Retail ILT 0x000241FE lands on the matched body 0x000EDCD0.
class Team
{
public:
	void getEstimateTeamPosition_000EDCD0(Coord3D *out) const;
};

// Retail ILT 0x0001F253 lands on GameLogic::findObjectByID (0x0009A510).
class GameLogic
{
public:
	Object *findObjectByID(int id);
};

// Retail ILT 0x00044C2E lands on TeamFactory::findTeamByID (0x000EF060).
class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

extern GameLogic *TheGameLogic;
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
	BfmeObjXQ *obj = (BfmeObjXQ *)TheGameLogic->findObjectByID((int)cfg->m_bfme44XQ);
	Team *team = TheTeamFactory->findTeamByID((unsigned int)cfg->m_bfme48XQ);

	if (obj)
		m_bfme2CXQ = obj->m_bfme38XQ;
	else if (team)
		team->getEstimateTeamPosition_000EDCD0(&m_bfme2CXQ);

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
	BfmeObjXQ *obj = (BfmeObjXQ *)TheGameLogic->findObjectByID((int)cfg->m_bfme44XQ);
	Team *team = TheTeamFactory->findTeamByID((unsigned int)cfg->m_bfme48XQ);

	if (obj)
		m_bfme2CXQ = obj->m_bfme38XQ;
	else if (team)
		team->getEstimateTeamPosition_000EDCD0(&m_bfme2CXQ);

	return m_bfme40XQ->bfmeRunXQ();
}
