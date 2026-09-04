// cl: /DNDEBUG /DWIN32 /MD
//
// Open-BFME5: thiscall filter at retail 0x003DF1E0 (90B).

enum KindOfType
{
	KINDOF_FILTER_41 = 0x41
};

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	char m_pad[0x74];
	int m_tag74;
};

class GameLogicFrameSlice
{
public:
	Object *bfmeFind(int id);
};

extern GameLogicFrameSlice *TheGameLogic;

struct BfmeMsgObj
{
	char m_pad[0x20];
	int m_id20;
};

struct BfmeFilterMsg
{
	BfmeMsgObj *m_obj;
	char m_pad4[8];
	unsigned int m_flagsC;
};

class BfmeLogicFindKindFilter
{
public:
	int bfmeAccept(void *a, BfmeFilterMsg *msg, void *c, void *d);

private:
	Object *m_hit;
	int m_tag4;
};

// ?bfmeAccept@BfmeLogicFindKindFilter@@QAEHPAXPAUBfmeFilterMsg@@00@Z
int BfmeLogicFindKindFilter::bfmeAccept(void *a, BfmeFilterMsg *msg, void *c, void *d)
{
	(void)a;
	(void)c;
	(void)d;
	Object *obj;
	if ((msg->m_flagsC & 7) == 4)
	{
		BfmeMsgObj *mo = msg->m_obj;
		int id = mo ? mo->m_id20 : 0;
		obj = TheGameLogic->bfmeFind(id);
		if (obj)
		{
			if (obj->isKindOf(KINDOF_FILTER_41))
			{
				if (obj->m_tag74 != m_tag4)
				{
					m_hit = obj;
					return 1;
				}
			}
		}
	}
	return 0;
}
