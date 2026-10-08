// ?Rva00036057PlayerAddScienceThunk@@YAXXZ
// Retail 0x00036057 is the Player::addScience ILT. Its five-byte tail jump
// reaches the matched Player::addScience body at 0x000D5380.
// The wrapper keeps the retail cdecl void(void) signature, so the member call is
// routed through the same pointer/member-pointer union the other ILT thunks use:
// cl folds the constant member address into a direct tail jump, so .text stays
// the five-byte E9 rel32 that the linker resolves to the matched
// ?addScience@Player@@AAE_NW4ScienceType@@@Z at 0x000D5380.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

enum ScienceType { SCIENCE_INVALID = -1 };

// Declaration only: the body is owned by
// game/GameEngine/Source/Common/RTS/Player_addScience_bfme.cpp at 0x000D5380.
void Rva00036057PlayerAddScienceThunk(void);

class Player
{
	bool addScience(ScienceType);
	friend void Rva00036057PlayerAddScienceThunk(void);
};

typedef bool (Player::*AddScienceFn)(ScienceType);

void Rva00036057PlayerAddScienceThunk(void)
{
	union { void (*fn)(); AddScienceFn call; } u;
	u.call = &Player::addScience;
	u.fn();
}