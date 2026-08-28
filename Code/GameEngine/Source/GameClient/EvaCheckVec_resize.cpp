// cl: /DNDEBUG /MD /EHsc

// EvaCheckVec::resize, retail 0x00426100. One argument in, two out: the element
// the vector is grown with is default-constructed on the stack and passed by
// value.
//
// That temporary is the `mov [esp+0x18],esp' at 0x0042611B - the transposition
// that only appears when the constructor's body is visible - so EvaCheck's
// constructor is written out here rather than declared. It is 0x18 bytes, of
// which this constructor touches three: two floats set to -1 and a flag at
// +0x14 cleared.
//
// EvaCheck also needs a declared copy constructor and a declared DESTRUCTOR.
// Without the copy constructor MSVC builds the temporary in a second stack slot
// and copies it in; without the destructor it drops the `push ecx' and the
// `mov [esp+0x18],esp' that go with keeping the temporary unwindable. Neither
// is ever called from here - the callee destroys a by-value parameter - so
// declaring both is enough.
//
// The two-argument resize is unnamed in the image and pinned.

typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	EvaCheck() : m_unmodelled_00( -1.0f ), m_unmodelled_04( -1.0f )
	{
		m_unmodelled_14 = false;
	}

	EvaCheck( const EvaCheck &that );
	~EvaCheck();

	Real m_unmodelled_00;					// +0x00
	Real m_unmodelled_04;					// +0x04
	unsigned char m_unmodelled_08[ 0x14 - 8 ];
	bool m_unmodelled_14;					// +0x14
	unsigned char m_unmodelled_15[3];
};

class EvaCheckVecBase
{
public:
	void resize( Int n, EvaCheck value );
};

class EvaCheckVec : public EvaCheckVecBase
{
public:
	void resize( Int n );
};

// ?resize@EvaCheckVec@@QAEXH@Z
void EvaCheckVec::resize( Int n )
{
	EvaCheckVecBase::resize( n, EvaCheck() );
}
