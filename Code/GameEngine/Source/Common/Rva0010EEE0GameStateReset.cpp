// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: address-derived GameState reset candidate for retail 0x0010EEE0.
// The vtable at 0x010893E0 names slot 4 as GameState::reset.  The reset body
// uses a typed view for the already matched canonical clearAvailableGames
// member instead of inventing a thunk-only helper identity.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva0010EEE0AuxiliaryValue
{
	unsigned first;
	unsigned second;
};

class Rva0010EEE0GameState;

class GameState
{
	friend class Rva0010EEE0GameState;

	private:
	void clearAvailableGames();
};

class Rva0010EEE0GameState : public GameState
{
public:
	void reset();

private:
	char m_pad0[0x48];
	_STL::list<void *> m_snapshotList;
	_STL::list<Rva0010EEE0AuxiliaryValue> m_auxiliaryList;
	void *m_availableGames;
	bool m_isInLoadGame;
};

void Rva0010EEE0GameState::reset()
{
	m_snapshotList.clear();
	m_auxiliaryList.clear();
	clearAvailableGames();
	m_isInLoadGame = false;
}
