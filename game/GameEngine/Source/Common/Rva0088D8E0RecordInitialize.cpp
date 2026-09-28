struct Rva0088D8E0Record
{
	void *field0;
	unsigned int field4;
	unsigned int field8;
	unsigned char flagC;
	unsigned char flagD;
};

void __cdecl initialize0088D8E0(Rva0088D8E0Record *record, void *field0,
	unsigned int field4, unsigned int field8)
{
	record->field0 = field0;
	record->field4 = field4;
	record->field8 = field8;
	record->flagC = 1;
	record->flagD = 1;
}

struct Rva0088D8B0Record
{
	void *m_first;
	unsigned int m_second;
	unsigned int m_third;
	unsigned char m_fourth;
	unsigned char m_fifth;
};
class Rva0088D8B0Owner
{
public:
	Rva0088D8B0Owner *initialize(void *first, unsigned int second, unsigned int third, unsigned char fourth, unsigned char fifth);
	Rva0088D8B0Record m_record;
};
// ?initialize@Rva0088D8B0Owner@@QAEPAV1@PAXIIEE@Z
Rva0088D8B0Owner *Rva0088D8B0Owner::initialize(void *first, unsigned int second, unsigned int third, unsigned char fourth, unsigned char fifth)
{
	m_record.m_first = first;
	m_record.m_second = second;
	m_record.m_third = third;
	m_record.m_fourth = fourth;
	m_record.m_fifth = fifth;
	return this;
}
