// cl: /DNDEBUG /MD /EHsc

// RvaC4390First::getInterface, retail 0x001BFE40. The class and interface names
// are this tree's, derived from an address; only the shape below is claimed.
//
// A null-terminated array of modules at +0x1F0 is walked, each asked through
// the sub-object at its own +0x0C, virtual slot +0x90. The first non-null
// answer wins. The zero for "none" is materialised after the loop rather than
// before it, which is where MSVC puts it - unlike Object::getObjectExitInterface
// forty bytes away, whose retail body zeroes up front and does not reproduce.

// A struct, not a class: the decorated name says PAURvaC4390Interface@@, and a
// forward declaration as `class' produces PAV and no such symbol in the object.
struct RvaC4390Interface;

class RvaC4390Provider
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_38() = 0;
	virtual void _bfme_pad_3C() = 0;
	virtual void _bfme_pad_40() = 0;
	virtual void _bfme_pad_44() = 0;
	virtual void _bfme_pad_48() = 0;
	virtual void _bfme_pad_4C() = 0;
	virtual void _bfme_pad_50() = 0;
	virtual void _bfme_pad_54() = 0;
	virtual void _bfme_pad_58() = 0;
	virtual void _bfme_pad_5C() = 0;
	virtual void _bfme_pad_60() = 0;
	virtual void _bfme_pad_64() = 0;
	virtual void _bfme_pad_68() = 0;
	virtual void _bfme_pad_6C() = 0;
	virtual void _bfme_pad_70() = 0;
	virtual void _bfme_pad_74() = 0;
	virtual void _bfme_pad_78() = 0;
	virtual void _bfme_pad_7C() = 0;
	virtual void _bfme_pad_80() = 0;
	virtual void _bfme_pad_84() = 0;
	virtual void _bfme_pad_88() = 0;
	virtual void _bfme_pad_8C() = 0;
	virtual RvaC4390Interface *getInterface() = 0;		// +0x90
};

class RvaC4390First
{
public:
	RvaC4390Interface *getInterface( void );

private:
	unsigned char m_unmodelled_00[ 0x1F0 ];
	char **m_modules;						// +0x1F0
};

// ?getInterface@RvaC4390First@@QAEPAURvaC4390Interface@@XZ
RvaC4390Interface *RvaC4390First::getInterface( void )
{
	for( char **module = m_modules; *module; ++module )
	{
		RvaC4390Interface *found = ((RvaC4390Provider *)( *module + 0x0C ))->getInterface();

		if( found )
			return found;
	}

	return 0;
}
