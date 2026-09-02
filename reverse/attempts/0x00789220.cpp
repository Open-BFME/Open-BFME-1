// ??0Rva00789220Holder@@QAE@PAX@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /O2

class Rva00789220Base
{
public:
	Rva00789220Base(void *source);
	~Rva00789220Base();
	void *m_table;
};

class Rva00789220VectorA
{
public:
	Rva00789220VectorA()
	{
		m_begin = 0;
		m_end = 0;
		m_capacityEnd = 0;
		m_extra = 0;
		bfmeReserve(100);
	}
	~Rva00789220VectorA();
	void bfmeReserve(unsigned int count);

	void *m_pad00;
	void *m_begin;
	void *m_end;
	void *m_capacityEnd;
	void *m_extra;
};

class Rva00789220VectorB
{
public:
	Rva00789220VectorB()
	{
		m_begin = 0;
		m_end = 0;
		m_capacityEnd = 0;
		m_extra = 0;
		bfmeReserve(100);
	}
	~Rva00789220VectorB();
	void bfmeReserve(unsigned int count);

	void *m_pad00;
	void *m_begin;
	void *m_end;
	void *m_capacityEnd;
	void *m_extra;
};

class Rva00789220Holder : public Rva00789220Base
{
public:
	Rva00789220Holder(void *source);
	int m_value04;
	Rva00789220VectorA m_first;
	Rva00789220VectorB m_second;
};

// @??0Rva00789220Holder@@QAE@PAX@Z 0x00789220
Rva00789220Holder::Rva00789220Holder(void *source) :
	Rva00789220Base(source),
	m_value04(0)
{
}
