// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::tryGroupSpecial, retail 0x001599A0, 169 bytes.
//
// Helper that applyOrFallback (0x0015A190) and groupAttackMoveToPosition
// (0x0015A030) both call through ILT 0x00046876. If isReady is false the
// caller treats the order as already handled. Otherwise walk m_memberList
// for an AI inner (+0x1CC via getAIUpdateInterface ILT 0x00021017) whose
// Overridable at +4 has field +0x74 set after getFinalOverride. A hit
// runs prep / check / prepFollow / send.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_unmodelled_000[4];
	Overridable *m_nextOverride;			// +0x04
	unsigned char m_unmodelled_008[0x74 - 0x08];
	void *m_field74;						// +0x74
};

class BfmeAIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[4];
	Overridable *m_override;				// +0x04
};

class BfmeUpdateObject
{
public:
	BfmeAIUpdateInterface *getAIUpdateInterface();
};

class AIGroup
{
public:
	char isReady();
	void prepSpecial();
	bool checkSpecial(const Coord3D *pos, int a);
	void prepFollow(CommandSourceType cmdSource, int flag);
	void sendSpecial(const Coord3D *pos, int a, int b, int d, int zero);
	bool tryGroupSpecial(const Coord3D *pos, int a, int b, int c, int d);

private:
	unsigned char m_unmodelled_000[4];
	_STL::list<BfmeUpdateObject *> m_memberList;	// +0x04
};

bool AIGroup::tryGroupSpecial(const Coord3D *pos, int a, int b, int c, int d)
{
	if (isReady())
	{
		bool found = false;
		_STL::list<BfmeUpdateObject *>::iterator i;
		for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
		{
			BfmeUpdateObject *obj = *i;
			if (obj == 0)
				continue;
			BfmeAIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai == 0)
				continue;
			Overridable *ovr = ai->m_override;
			if (ovr)
			{
				if (ovr->m_nextOverride)
					ovr = (Overridable *)ovr->m_nextOverride->getFinalOverride();
			}
			if (ovr->m_field74)
				found = true;
		}

		if (!found)
			return false;

		prepSpecial();
		if (!checkSpecial(pos, a))
			return false;

		prepFollow((CommandSourceType)a, b);
		sendSpecial(pos, a, b, d, 0);
		return true;
	}

	return true;
}
