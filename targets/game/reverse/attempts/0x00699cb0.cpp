// ??0BfmeBinkPlayerAAB@@QAE@XZ
// partial score=0.92 date=2026-09-08
class BfmeBinkStateAAB
{
public:
	BfmeBinkStateAAB();
	~BfmeBinkStateAAB();

	void *m_bfmeStateAAB;
};

class BfmeBinkPlayerMember
{
public:
	BfmeBinkPlayerMember();
	~BfmeBinkPlayerMember();

	void *m_bfmeSlotAAB;
};

class BfmeGuardAAB
{
public:
	~BfmeGuardAAB();
};

class BfmeBinkPlayerAAB : public BfmeGuardAAB
{
public:
	BfmeBinkPlayerAAB();

	char m_bfme00AAB;
	char m_bfme01AAB;
	int m_bfme04AAB;
	int m_bfme08AAB;
	char m_bfme0CAAB;
	int m_bfme10AAB;
	int m_bfme14AAB;
	int m_bfme18AAB;
	BfmeBinkStateAAB m_bfme1CAAB;
	BfmeBinkPlayerMember m_bfme20AAB;
	BfmeBinkPlayerMember m_bfme24AAB;
	int m_bfme28AAB;
	int m_bfme2CAAB;
	int m_bfme30AAB;
	int m_bfme34AAB;
	int m_bfme38AAB;
	char m_bfme3CAAB;
};

BfmeBinkPlayerAAB::BfmeBinkPlayerAAB()
	: m_bfme00AAB(0),
	  m_bfme01AAB(0),
	  m_bfme04AAB(0),
	  m_bfme08AAB(0),
	  m_bfme0CAAB(0),
	  m_bfme10AAB(0),
	  m_bfme14AAB(0),
	  m_bfme18AAB(0),
	  m_bfme28AAB(0),
	  m_bfme2CAAB(0),
	  m_bfme30AAB(0),
	  m_bfme34AAB(0),
	  m_bfme38AAB(0),
	  m_bfme3CAAB(0)
{
}
