// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
// Only Player::enableRadar's identity matters here: this TU is the 0x00043207
// incremental-link thunk, so the body is the tail jmp MSVC emits for a function
// whose only statement is a call to that member function.
class Player
{
public:
	void enableRadar();
};

void j_00043207()
{
	typedef void (Player::*Fn)();

	union
	{
		Fn call;
		void (*fn)();
	} u;

	u.call = &Player::enableRadar;
	(u.fn)();
}