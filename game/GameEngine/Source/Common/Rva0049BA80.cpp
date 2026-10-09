// cl: /DNDEBUG /MD
// Retail 0x0049BA80, 292 bytes. Dispatches on this+0x18's flag bits to pick
// one of several status checks on the caller-supplied object, comparing (or
// storing) the result into this+0x148. this+0x138/+0x13c bound a pointer
// vector that must hold >=2 entries or the result is forced to 0; a null
// object, or any branch's own lookup miss, instead leaves this+0x148
// untouched. ILT 0x00006938 and matched Rva0049C2E0::method prove the
// method name and signature. The receiver keeps an address-derived class
// name because retail gives no native owner type. Existing callee declarations
// are ABI views, with routes and contracts in the evidence file.

typedef int Int;
typedef unsigned int UInt;

class Rva001BEF20FieldAddress
{
public:
	char *get();
};

struct RvaC4390First;

class RvaC4390Second
{
public:
	RvaC4390First *resolve( Int id );
};

class BfmeX1004;

// Address-derived ABI view of the borrowed interface queried at slot +0xD8.
// No concrete implementation, owner identity, or object lifetime is claimed.
class Rva0049BA80SlotD8View
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
    virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
    virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9c();
    virtual void slota0(); virtual void slota4(); virtual void slota8(); virtual void slotac();
    virtual void slotb0(); virtual void slotb4(); virtual void slotb8(); virtual void slotbc();
    virtual void slotc0(); virtual void slotc4(); virtual void slotc8(); virtual void slotcc();
    virtual void slotd0(); virtual void slotd4(); virtual bool slotd8();
};

class Object
{
public:
	void *unidentified_001BFE20() const;
};

class BFMEActionObject
{
public:
	bool testStatus( Int code ) const;
};

class Rva000D3F10
{
public:
	int test( UInt bit );
};

class Object;

class Rva0049BA80
{
public:
	void call( Object *object, bool flag ) const;

private:
	char m_unmodelled000[ 0x10 ];
	Int m_field10;
	char m_unmodelled014[ 0x18 - 0x14 ];
	UInt m_flags18;
	char m_unmodelled01c[ 0x70 - 0x1c ];
	Int m_field70;
	Int m_field74;
	Int m_field78;
	UInt m_field7c;
	char m_unmodelled080[ 0x138 - 0x80 ];
	char *m_vecBegin;
	char *m_vecEnd;
	char m_unmodelled140[ 0x148 - 0x140 ];
	mutable Int m_cached148;
};

void Rva0049BA80::call( Object *object, bool flag ) const
{
	if ( object == 0 )
		return;

    if ( ( UInt )( (m_vecEnd - m_vecBegin) >> 2 ) < 2u )
	{
		m_cached148 = 0;
		return;
	}

	UInt flags = m_flags18;

	if ( flags & 0x1000000 )
	{
		Rva001BEF20FieldAddress *owner = reinterpret_cast<Rva001BEF20FieldAddress *>( object );
		const UInt &weaponFlags = *reinterpret_cast<const UInt *>(owner->get());
		bool bitSet = ( weaponFlags & m_field7c ) != 0;
		m_cached148 = ( bitSet != flag ) ? 1 : 0;
		return;
	}

	if ( flags & 0x2000000 )
	{
		RvaC4390Second *second = reinterpret_cast<RvaC4390Second *>( object );
		RvaC4390First *first = second->resolve( 0 );
		if ( first == 0 )
			return;

		Object *holder = reinterpret_cast<Object *>( first );
		void *found = holder->unidentified_001BFE20();
		if ( found == 0 )
			return;

        m_cached148 = !(reinterpret_cast<Rva0049BA80SlotD8View *>(found)->slotd8() ^ flag);
		return;
	}

	if ( flags & 0x800000 )
	{
        switch (m_field10) { case 0x22:
        {
			Rva000D3F10 *bits =
				reinterpret_cast<Rva000D3F10 *>( object );
			if ( (unsigned char)bits->test( 0x89 ) )
			{
				m_cached148 = m_field74;
				return;
			}
			if ( (unsigned char)bits->test( 0x8a ) )
			{
				m_cached148 = m_field78;
				return;
			}
			m_cached148 = m_field70;
			return;
		}

        case 0x2e: {

		BFMEActionObject *action = reinterpret_cast<BFMEActionObject *>( object );
		bool status = action->testStatus( 0x17 );
        m_cached148 = status == flag;
		return;
        } default: return; }
    }
}
