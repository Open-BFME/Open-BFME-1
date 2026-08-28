class BfmeSubDDB
{
public:
	int bfmeTailDDB();
	unsigned char m_bfmeHead[0x39];
	bool m_bfmeFlag;
};

class BfmeThingDDB
{
public:
	int bfmeGoDDB();
	unsigned char m_bfmeHead[0x64];
	BfmeSubDDB *m_bfmeSub;
};

int BfmeThingDDB::bfmeGoDDB()
{
	BfmeSubDDB *s = m_bfmeSub;
	if (s != 0 && s->m_bfmeFlag)
		return s->bfmeTailDDB();
	return 0;
}
