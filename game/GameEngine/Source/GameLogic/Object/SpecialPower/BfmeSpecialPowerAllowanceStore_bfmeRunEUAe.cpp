// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// BfmeSpecialPowerAllowanceStore::bfmeRunEUAe, retail 0x0039C260 (287 bytes,
// ret 8 at 0x0039C37C). The matched BfmeItemEUA::bfmeRunEUAe (0x000C9930)
// reaches it through ILT 0x00045039 with its state at +0x274 and the context
// it was handed. The loop finds the first entry (final override) whose string
// at +0x0C matches the context string, then erases that entry's index from
// the state's integer vector at +0x08. The erase is the body retail also keeps
// out of line at 0x0039BE00.
//
// The loop is the one LightPointSystem::rva0039CB60 (0x0039CB60) runs, so the
// source follows that matched twin: a visible out-of-line override walk lets
// MSVC hoist the context string's data out of the loop. Without it the load
// stays in the preheader and the EBX save sinks below the EDI one.

#include <vector>
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	// ILT 0x00048C61 -> 0x00097880. The visible body is what lets MSVC keep
	// the name's data across the call; the call still binds to the ILT.
	__declspec(noinline) Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

class Rva0039C260Entry : public Overridable
{
public:
	unsigned char m_pad08[0x0c - 0x08];
	AsciiString m_string0C;
};

class BfmePlayerSpecialPowerState
{
public:
	unsigned char m_head[0x08];
	_STL::vector<Int> m_vector08;
};

class BfmeSpecialPowerAllowanceStore
{
public:
	void bfmeRunEUAe(BfmePlayerSpecialPowerState *state, void *context);

private:
	unsigned char m_head[0x08];
	_STL::vector<Rva0039C260Entry *> m_vector08;
};

// ?bfmeRunEUAe@BfmeSpecialPowerAllowanceStore@@QAEXPAVBfmePlayerSpecialPowerState@@PAX@Z
void BfmeSpecialPowerAllowanceStore::bfmeRunEUAe(
		BfmePlayerSpecialPowerState *state, void *context)
{
	const AsciiString &name = *(const AsciiString *)context;
	for (UnsignedInt i = 0; i < m_vector08.size(); ++i)
	{
		Rva0039C260Entry *entry =
			(Rva0039C260Entry *)m_vector08[i]->getFinalOverride();
		if (entry->m_string0C.compare(name) == 0)
		{
			for (_STL::vector<Int>::iterator it = state->m_vector08.begin();
					it != state->m_vector08.end(); ++it)
			{
				if (*it == (Int)i)
				{
					state->m_vector08.erase(it);
					return;
				}
			}
			return;
		}
	}
}
