// cl: /DNDEBUG /MD /EHsc

class Gen00887940
{
public:
	~Gen00887940();

private:
	void *m_data[3];
};

class Gen0045AFE0Base
{
public:
	virtual ~Gen0045AFE0Base()
	{
		if( m_next != 0 )
			delete m_next;
		m_next = 0;
	}

private:
	Gen0045AFE0Base *m_next;
	bool m_override;
};

class __declspec(novtable) Gen0045AFE0 : public Gen0045AFE0Base
{
public:
	virtual ~Gen0045AFE0();

private:
	Gen00887940 m_tail;
};

Gen0045AFE0::~Gen0045AFE0()
{
}
