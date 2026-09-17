// cl: /DNDEBUG /MD /EHsc
// Address-derived reconstruction of retail 0x0019BE80.
//
// The SidesList constructor and the adjacent full map parser both use the
// two TeamsInfoRec objects at +0x630 and +0x64c.  BFME's clear body at
// 0x001991F0 proves the record extent is 0x1c bytes (the retail layout is
// wider than the old Zero Hour header).  The add body is the adjacent
// 0x0019BA40 body reached through its 0x00045DC7 thunk.

class DataChunkInput;
struct DataChunkInfo;

class Dict
{
public:
	~Dict() { releaseData(); }

private:
	void releaseData();
	void *m_data;
};

class DataChunkInput
{
public:
	int readInt();
	Dict readDict();
};

class Rva0019BE80TeamRec
{
public:
	void clear();
	int append(const Dict *dict);

private:
	unsigned char m_layout[0x1c];
};

class Rva0019BE80SidesList
{
public:
	bool loadTeams(DataChunkInput &file, DataChunkInfo *info);

private:
	unsigned char m_prefix[0x630];
	Rva0019BE80TeamRec m_teamrec;
	Rva0019BE80TeamRec m_skirmishTeamrec;
};

// Retail calls the clear and append implementations through these ILT
// thunks.  The names are deliberately TU-local: the old TeamsInfoRec::addTeam
// pin was proven to be an unrelated string-destructor thunk.

bool Rva0019BE80SidesList::loadTeams(DataChunkInput &file, DataChunkInfo *info)
{
	int count = file.readInt();
	m_teamrec.clear();
	m_skirmishTeamrec.clear();
	if (count > 0)
	{
		for (int i = count; i > 0; --i)
		{
			Dict d = file.readDict();
			m_teamrec.append(&d);
		}
	}
	return true;
}
