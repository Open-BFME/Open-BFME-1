// cl: /DNDEBUG /MD /EHsc
// readable body of ?friend_checkForSleepTransitions@State@@: Code/GameEngine/Source/Common/StateMachine.cpp
// Open-BFME5: State::friend_checkForSleepTransitions, retail 0x000A05D0,
// zh_sweep packet 000a05d0.
//
// The Zero Hour body unchanged. Compiled inside StateMachine.cpp it reproduced
// all 312 bytes except that every State member sits four bytes earlier in
// retail than the vendored class puts it: the transition vector starts at
// [this+0x10] and m_machine is at [this+0x1C], against +0x14 and +0x20. One
// leading member fewer, uniformly. Its own TU rather than shifting the ten
// other rows in that file.
//
// Everything else the bytes confirm and the class keeps: TransitionInfo is 12
// bytes -- retail steps the iterator by 0x0C -- with the test function pointer
// at +0x00, toStateID at +0x04 and userData at +0x08, so STATE_MACHINE_DEBUG's
// description field is absent from this build. The test is a __cdecl call
// through [it], taking (this, userData). The exit sentinels are 9998 and 9999
// and the two return codes are -1 and -2.
//
// The re-entry counter is the function-local static at 0x012ED638, and the
// SEH frame exists only so StIncrementer's decrement still runs if the test
// function or internalSetState throws. Note retail re-reads the vector's end
// every iteration: the transition test can change it.
//
// The vector is spelled as its three pointers rather than a std::vector so the
// offsets can be pinned without dragging STLport in.

typedef int Int;
typedef unsigned int StateID;

enum StateReturnType
{
	STATE_SUCCESS		= -1,
	STATE_FAILURE		= -2
};

enum
{
	EXIT_MACHINE_WITH_SUCCESS = 9998,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

class State;

typedef bool (*StateTransFuncPtr)( State *state, void *userData );

struct TransitionInfo;

// The three pointers a vector is, with the reference's const/non-const accessor
// split kept: empty() is const and begin()/end() are not, which is what stops
// MSVC folding the empty test into the loop's entry test the way a single
// pointer comparison would.
struct TransitionVector
{
	TransitionInfo *_M_start;								///< +0x00
	TransitionInfo *_M_finish;								///< +0x04
	TransitionInfo *_M_end_of_storage;						///< +0x08

	bool empty( void ) const { return _M_start == _M_finish; }
	TransitionInfo *begin( void ) { return _M_start; }
	TransitionInfo *end( void ) { return _M_finish; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
struct TransitionInfo
{
	StateTransFuncPtr	test;								///< +0x00
	StateID				toStateID;							///< +0x04
	void				*userData;							///< +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	StateReturnType internalSetState( StateID newStateID );	///< ILT 0x000294E7 -> 0x000A1360
};

//-----------------------------------------------------------------------------
class StIncrementer
{
private:
	Int& num;
public:
	StIncrementer(Int& n) : num(n)
	{
		++num;
	}
	~StIncrementer()
	{
		--num;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	StateReturnType friend_checkForSleepTransitions( StateReturnType status );

private:
	StateMachine *getMachine( void ) { return m_machine; }

	virtual void placeholder( void ) = 0;					///< vptr at +0x00

	unsigned char m_unreconstructed_04[0x10 - 4];
	TransitionVector m_transitions;							///< +0x10, three pointers
	StateMachine *m_machine;								///< +0x1C
};

// ?friend_checkForSleepTransitions@State@@QAE?AW4StateReturnType@@W42@@Z
StateReturnType State::friend_checkForSleepTransitions( StateReturnType status )
{
	static Int checkfortransitionsnum = 0;

	StIncrementer inc(checkfortransitionsnum);
	if (checkfortransitionsnum >= 20)
	{
		return STATE_FAILURE;
	}

	// check transition condition list
	if (m_transitions.empty())
		return status;

	for(const TransitionInfo *it = m_transitions.begin(); it != m_transitions.end(); ++it)
	{
		if (!it->test( this, it->userData ))
			continue;

		// test returned true, change to associated state

		// check if machine should exit
		if (it->toStateID == EXIT_MACHINE_WITH_SUCCESS)
		{
			return STATE_SUCCESS;
		}
		else if (it->toStateID == EXIT_MACHINE_WITH_FAILURE)
		{
			return STATE_FAILURE;
		}
		else
		{
			// move to new state
			return getMachine()->internalSetState( it->toStateID );
		}
	}

	return status;
}
