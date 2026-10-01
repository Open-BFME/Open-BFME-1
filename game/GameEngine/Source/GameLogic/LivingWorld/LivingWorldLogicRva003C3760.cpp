// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x003C3760, 191 bytes; complete RET at 0x003C381E.
// LivingWorldLogic ownership follows the landed constructor and objective
// setters: region manager +0x28, region name +0x30, objective states +0x84.
// The method name remains address-derived. Initial/reset state consists of
// visible=true and completed=false. Retail passes its two-byte initial state
// by value to the resize ILT at 0x000299CE, whose body at 0x003C2EE0
// consumes two stack arguments and uses only the lower word of the value.
// The vector declaration reuses the existing matched unsigned-short resize
// ABI. Its storage is viewed as two boolean bytes when resetting objectives;
// the original retail STL element type remains unproven.

#include <vector>
#include "ascii_string.h"

struct Rva003C3760State
{
	bool m_visible;
	bool m_completed;
};

namespace Gen003C2EE0Stl
{
template <class Type>
class allocator
{
};
template <class Type, class Allocator>
class vector
{
public:
	Type *begin() { return m_begin; }
	Type *end() { return m_end; }
	void resize(unsigned int, Type);
private:
	Type *m_begin;
	Type *m_end;
	Type *m_capacity;
};
}
typedef Gen003C2EE0Stl::vector<unsigned short,
	Gen003C2EE0Stl::allocator<unsigned short> > Rva003C2EE0StateVector;

struct LivingWorldRegionPointerVector
{
	void **m_begin;
	void **m_end;
	void **m_capacity;

	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}
};

class Rva00618E60FieldAddress
{
public:
	const void *get() const;
};

class Rva00618E70FieldAddress
{
public:
	const void *get() const;
};

class Rva00618E80FieldAddress
{
public:
	const void *get() const;
};

class Rva00618E90FieldAddress
{
public:
	const void *get() const;
};

class Rva0036CA00Str;

class LivingWorldRegion
{
public:
	unsigned int rva003C3760Count() const
	{
		return m_60.size() + m_54.size();
	}

private:
	char m_pad[0x54];
	LivingWorldRegionPointerVector m_54;
	LivingWorldRegionPointerVector m_60;
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50(const AsciiString &);
};

class Rva00386090
{
public:
	void set(Rva0036CA00Str *);
};

class Rva003860F0
{
public:
	void set(Rva0036CA00Str *, Rva0036CA00Str *, Rva0036CA00Str *);
};

class GameLogic;
extern GameLogic *TheBfmeGameLogic;
#define g_012F0898 reinterpret_cast<Rva00386090 *>(TheBfmeGameLogic)

class LivingWorldLogic
{
public:
	void rva003C3760();

private:
	char m_pad00[0x28];
	LivingWorldRegionManager *m_regionManager;
	char m_pad2c[4];
	AsciiString m_currentRegionName;
	char m_pad34[0x50];
	Rva003C2EE0StateVector m_missionObjectiveStates;
};

void LivingWorldLogic::rva003C3760()
{
	if (m_regionManager == 0)
		return;

	LivingWorldRegion *region =
		m_regionManager->rva003C8A50(m_currentRegionName);
	if (region == 0)
		return;

	__declspec(align(4)) Rva003C3760State initialState;
	initialState.m_visible = true;
	initialState.m_completed = false;
	m_missionObjectiveStates.resize(region->rva003C3760Count(),
		*reinterpret_cast<unsigned short *>(&initialState));

	__declspec(align(4)) Rva003C3760State resetState;
	resetState.m_visible = true;
	resetState.m_completed = false;
	_STL::fill(reinterpret_cast<Rva003C3760State *>(m_missionObjectiveStates.begin()),
		reinterpret_cast<Rva003C3760State *>(m_missionObjectiveStates.end()), resetState);

	if (g_012F0898)
	{
		g_012F0898->set(
			(Rva0036CA00Str *)((Rva00618E60FieldAddress *)region)->get());
		((Rva003860F0 *)g_012F0898)->set(
			(Rva0036CA00Str *)((Rva00618E70FieldAddress *)region)->get(),
			(Rva0036CA00Str *)((Rva00618E80FieldAddress *)region)->get(),
			(Rva0036CA00Str *)((Rva00618E90FieldAddress *)region)->get());
	}
}
