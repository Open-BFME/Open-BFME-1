// cl: /DNDEBUG /MD /EHsc
// readable body of ?getShroudClearingRange@Object@@QBEMXZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::getShroudClearingRange, retail 0x001CA4B0. No calls: a flag byte at
// +0x90 chooses between two floats, +0xBC when bit 2 is set and +0x198 when it
// is not. Retail loads the +0x198 one before the test and pops it in the taken
// branch, which is what a conditional return of two members compiles to.

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real getShroudClearingRange( void ) const;

private:
	unsigned char m_unmodelled_00[ 0x90 ];
	unsigned char m_statusFlags;			// +0x90
	unsigned char m_unmodelled_91[ 0xBC - 0x91 ];
	Real m_unmodelled_BC;					// +0xBC
	unsigned char m_unmodelled_C0[ 0x198 - 0xC0 ];
	Real m_unmodelled_198;					// +0x198
};

// ?getShroudClearingRange@Object@@QBEMXZ
Real Object::getShroudClearingRange( void ) const
{
	// Both values are read before the test: retail loads the flag byte into a
	// register and pushes the +0x198 float, then pops it again in the taken
	// branch. A plain `if' over two returns tests the byte in memory instead and
	// keeps the two loads in their own arms.
	unsigned char flags = m_statusFlags;
	Real range = m_unmodelled_198;

	if( flags & 4 )
		range = m_unmodelled_BC;

	return range;
}
