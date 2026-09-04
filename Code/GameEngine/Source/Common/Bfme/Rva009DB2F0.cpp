// ?set@Rva009DB2F0@@QAE_NPAX@Z
// cl: /DNDEBUG /MD

extern void j_00006730(void);

class Rva009DB2F0InsertReceiver
{
};

union Rva009DB2F0InsertCall
{
	void (*free_function)(void);
	void (Rva009DB2F0InsertReceiver::*member_function)(int first, int second);
};

struct Rva009DB2F0Range
{
	volatile int m_first;
	volatile int m_second;
};

class Rva009DB2F0
{
public:
	bool set(void *value);

private:
	unsigned char m_unmodelled_000[4];
	bool m_active;
	unsigned char m_unmodelled_005[3];
	void * volatile m_value;
	Rva009DB2F0Range m_range;
};

bool Rva009DB2F0::set(void *value)
{
	if (m_value != 0)
		return false;
	Rva009DB2F0Range *range = &m_range;
	m_value = value;
	Rva009DB2F0InsertCall call;
	call.free_function = &j_00006730;
	(((Rva009DB2F0InsertReceiver *)range)->*call.member_function)(
		range->m_first, range->m_second);
	m_active = false;
	return true;
}
