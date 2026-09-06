// Address-derived reconstruction of the retail 0x00191830 script-list copy.
// The +0x28 count and +0x2c flexible SidesInfo array are the proven SidesList
// layout.  The source accessor is intentionally retained: retail performs the
// same bounds check before dereferencing the script slot.

class ScriptList
{
public:
	ScriptList();
	virtual ~ScriptList();
	char m_storage[0x48];
};

class Gen0035E3B0;
class Host0035E450
{
public:
	Gen0035E3B0 *create();
};

struct Rva00191830SidesInfo
{
	void *m_buildList;
	void *m_dict;
	ScriptList *m_scriptList;
	void *m_rest[3];
};

class Rva00191830SidesList
{
public:
	void resetScriptLists(Rva00191830SidesList *input);

	Rva00191830SidesInfo *getSideInfo(int side)
	{
		return (side >= 0 && side < m_numSides) ? &m_sides[side] : 0;
	}

private:
	char m_head[0x28];
	int m_numSides;
	Rva00191830SidesInfo m_sides[1];
};

void Rva00191830SidesList::resetScriptLists(Rva00191830SidesList *input)
{
	int index = 0;
	if (input->m_numSides <= 0)
		return;

	Rva00191830SidesInfo *slot = m_sides;
	while (index < input->m_numSides)
	{
		Rva00191830SidesInfo *source = input->getSideInfo(index);
		ScriptList *replacement;
		if (source->m_scriptList)
		{
			Host0035E450 *factory =
				reinterpret_cast<Host0035E450 *>(source->m_scriptList);
			replacement = reinterpret_cast<ScriptList *>(factory->create());
		}
		else
			replacement = new ScriptList;

		ScriptList *old = slot->m_scriptList;
		slot->m_scriptList = replacement;
		if (old)
			delete old;

		++index;
		++slot;
	}
}
