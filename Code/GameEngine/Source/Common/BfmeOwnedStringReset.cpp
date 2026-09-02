// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

class AsciiString
{
public:
	~AsciiString();
	char *m_data;
};

class Gen_dtor_0034dd90
{
public:
	virtual ~Gen_dtor_0034dd90();
};

class BfmeOwnedStringState
{
public:
	void resetOwnedObject();

private:
	int m_head;
	AsciiString m_name;
	int m_reset;
	Gen_dtor_0034dd90 *m_owned;
};

void BfmeOwnedStringState::resetOwnedObject()
{
	m_name.~AsciiString();
	Gen_dtor_0034dd90 *owned = m_owned;
	m_reset = 1;
	if (owned != 0) {
		owned->Gen_dtor_0034dd90::~Gen_dtor_0034dd90();
		operator delete(owned);
		m_owned = 0;
	}
}
