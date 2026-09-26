// 17-byte guarded virtual call with 1 unused argument

class Receiver004892E0
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void slot();
};

class Rva004892E0
{
public:
	void call( int dummy );

	char              m_pad00[ 0x10 ];
	Receiver004892E0 *m_receiver;
};

void Rva004892E0::call( int dummy )
{
	if( m_receiver )
		m_receiver->slot();
}
