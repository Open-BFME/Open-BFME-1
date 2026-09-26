// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Open-BFME7: the 378-byte private method at 0x00433900, called three times by
// the matched ?apply@Rva00435270Layout@@QAEXXZ at 0x00435270 through retail ILT
// thunk 0x0001CBB6.  It fills one (left from right to) integer quad, then walks
// m_count24 receivers from m_cursor3C, asking the 0x004337B0 helper for four
// words, masking them to their top byte, handing both arrays plus the quad to
// three virtual setters and finally placing the receiver.  Owner and slot names
// stay address-derived: no layout or string witness names this class.

typedef int Int;
typedef float Real;

class Rva00435270Receiver;

class BfmeThingHM
{
public:
	void bfmeFillHM( unsigned int *out, unsigned int value, Int mode );
};

class Rva00433900Receiver
{
public:
	virtual void slot00( void );
	virtual void slot01( void );
	virtual void slot02( void );
	virtual void slot03( void );
	virtual void slot04( void );
	virtual void slot05( void );
	virtual void slot06( void );
	virtual void slot07( void );
	virtual void slot08( void );
	virtual void slot09( void );
	virtual void slot0A( void );
	virtual void setFirst( unsigned int *value );
	virtual void setSecond( unsigned int *value );
	virtual void slot0D( void );
	virtual void setPosition( Int position, Int value, Int first, Int second );
	virtual void slot0F( void );
	virtual void slot10( void );
	virtual void slot11( void );
	virtual void slot12( void );
	virtual void slot13( void );
	virtual void setThird( Int *values );
};

class Rva00435270Layout
{
private:
	void setRange( Int mode, Int from, Int to );

	char m_unreconstructed00[ 0x08 ];
	Int m_unknown08;
	Int m_unknown0c;
	char m_unreconstructed10[ 0x04 ];
	Int m_state14;
	char m_unreconstructed18[ 0x04 ];
	Int m_timer1c;
	char m_unreconstructed20[ 0x04 ];
	Int m_count24;
	Int m_progress28;
	Int m_owner2C;
	Int m_value30;
	Rva00435270Receiver **m_receivers34;
	unsigned int *m_values38;
	Int m_cursor3C;
	char m_unreconstructed40[ 0x04 ];
	Real m_value44;
	Real m_value48;
	Real m_left4C;
	Real m_top50;
	Real m_right54;
	Real m_bottom58;
	char m_unreconstructed5C[ 4 ];
	Real m_split60;
	char m_unreconstructed64[ 4 ];
	Real m_split68;
};

// ?setRange@Rva00435270Layout@@AAEXHHH@Z
void Rva00435270Layout::setRange( Int mode, Int from, Int to )
{
	Int storage[ 4 ];
	storage[ 0 ] = (Int)m_left4C;
	storage[ 2 ] = (Int)m_right54;
	storage[ 1 ] = from;
	storage[ 3 ] = to;
	Int range = (Int)m_value44 - m_value30 - 2;
	Real start = (Real)range + m_top50;

	for( Int i = 0; i < m_count24; ++i )
	{
		Int generatedStorage[ 4 ];
		Int masked[ 4 ] = { 0, 0, 0, 0 };
		Int index = (m_cursor3C + i) % m_count24;
		index *= sizeof( Int );
		BfmeThingHM *helper = (BfmeThingHM *)this;
		helper->bfmeFillHM( (unsigned int *)generatedStorage,
			*(unsigned int *)((char *)m_values38 + index), mode );
		masked[ 0 ] = generatedStorage[ 0 ] & 0xff000000;
		masked[ 1 ] = generatedStorage[ 1 ] & 0xff000000;
		masked[ 2 ] = generatedStorage[ 2 ] & 0xff000000;
		masked[ 3 ] = generatedStorage[ 3 ] & 0xff000000;

		Rva00433900Receiver *receiver =
			*(Rva00433900Receiver **)((char *)m_receivers34 + index);
		receiver->setFirst( (unsigned int *)generatedStorage );
		index = ((m_cursor3C + i) % m_count24) * sizeof( Int );
		receiver = *(Rva00433900Receiver **)((char *)m_receivers34 + index);
		receiver->setSecond( (unsigned int *)masked );
		index = ((m_cursor3C + i) % m_count24) * sizeof( Int );
		receiver = *(Rva00433900Receiver **)((char *)m_receivers34 + index);
		receiver->setThird( storage );

		index = ((m_cursor3C + i) % m_count24) * sizeof( Int );
		receiver = *(Rva00433900Receiver **)((char *)m_receivers34 + index);
		Int span = m_value30;
		Int product = span * i;
		Int value = (Int)((Real)product + start);
		Int midpoint = span >> 1;
		Int position = (Int)((Real)midpoint + (Real)storage[ 0 ]);
		receiver->setPosition( position, value, 1, 1 );
	}
}
