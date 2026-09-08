// cl: /DNDEBUG /DWIN32 /MD /EHsc

extern "C" void __cdecl _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

extern "C" __declspec( dllimport ) unsigned long __stdcall timeGetTime();

class Rva00494670Resource
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual unsigned char test( int value );
};

class Rva00494670
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void baseUpdate();

	void update();

private:
	unsigned char m_padding0[ 4 ];
	Rva00494670Resource *m_resource;
	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
	union
	{
		char m_state;
		int m_stateValue;
	};
	unsigned char m_flags;
	unsigned char m_padding2[ 3 ];
	int m_color;
	unsigned int m_duration;
	unsigned int m_startTime;
	void (__cdecl *m_callback)( void * );
	void *m_callbackArgument;
};

void Rva00494670::update()
{
	if ( m_resource == 0 )
		return;

	if ( ( m_flags & 4 ) != 0 )
	{
		unsigned int now = timeGetTime();
		unsigned int duration = m_duration;
		int remaining = duration;
		remaining += m_startTime;
		_ReadWriteBarrier();
		remaining -= now;
		int progress = remaining > 0 ? remaining : 0;
		progress = progress > duration ? duration : progress;
		unsigned char alpha = (unsigned char)( progress * 255 / duration );
		m_color = alpha << 24 | 0x00ffffff;
	}

	if ( ( m_flags & 2 ) != 0 && ( m_state & 0x80 ) != 0 )
		return;

	if ( ( m_resource->test( m_stateValue ) & 2 ) == 0 )
		return;

	if ( ( m_flags & 2 ) != 0 )
		return;

	m_flags |= 2;
	if ( m_callback != 0 )
		m_callback( m_callbackArgument );

	if ( ( m_state & 0x84 ) == 0 )
		baseUpdate();
}
