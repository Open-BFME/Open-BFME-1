// 0x00479440 -- publish window-like state into an output record and clear the
// referenced view state when the caller requests it.

class Open2479440View
{
public:
	char m_pad0[ 0x14 ];
	int m_flag;
	char m_pad1[ 0x184 ];
	int m_firstClear;
	int m_secondClear;
	int m_thirdClear;
};

class Open2479440Record
{
public:
	char m_pad0[ 4 ];
	int m_second;
	char m_pad1[ 8 ];
	int m_fourth;
	int m_third;
	int m_first;
	int m_seventh;
	int m_fifth;
	int m_sixth;
	int m_eighth;
	int m_ninth;
	Open2479440View *m_view;
};

class Rva00479440
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual int slot1C();

	void publish( Open2479440Record *out, char keep );

	char m_pad0[ 4 ];
	int m_second;
	int m_third;
	int m_fourth;
	char m_pad1[ 0x1c ];
	Open2479440View m_view;
	char m_pad2[ 8 ];
	int m_fifth;
	int m_sixth;
	int m_seventh;
	int m_eighth;
	int m_ninth;
};

// @?publish@Rva00479440@@QAEXPAVOpen2479440Record@@D@Z 0x00479440
void Rva00479440::publish( Open2479440Record *out, char keep )
{
	out->m_first = slot1C();

	char flag = keep;

	out->m_second = m_second;
	out->m_fourth = m_third;
	out->m_third = m_fourth;
	Open2479440View *view = &m_view;
	out->m_view = view;
	out->m_fifth = m_fifth;
	out->m_seventh = m_sixth;
	out->m_sixth = m_seventh;
	out->m_eighth = m_eighth;
	out->m_ninth = m_ninth;

	if( flag != 0 )
	{
		view->m_flag = 0;
		out->m_view->m_firstClear = 0;
		out->m_view->m_secondClear = 0;
		out->m_view->m_thirdClear = 0;
	}
}
