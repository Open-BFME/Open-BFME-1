// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy- /Ob1 /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Rva0019BE80TeamRec::append -- retail 0x0019BA40, 331 B body plus the
// catch funclet at 0x0019BB8B (20 B), 351 B of code in all.
//
// Identity: the ILT thunk at 0x00045DC7 pinned to this name reaches 0x0019BA40,
// and the matched caller ?loadTeams@Rva0019BE80SidesList@@ (0x0019BE80) calls it
// with the Dict it just read. Returns the record index in EAX; ret 4.
//
// Callees resolve against already-matched/pinned ledger rows, not invented
// names:
//  * Dict(int)/clear()/operator=()/releaseData() below are a TU-local stand-in
//    (same shape as the real Common/Dict.h, which only carries one member,
//    a refcounted DictPairData*) declared under the real Dict.cpp method
//    names so the compiled calls resolve directly against its already-matched
//    rows, without pulling in the vendored STLport that Common/Dict.h's own
//    NameKeyGenerator.h chain drags in -- which collides with the address-
//    derived vector shim below (both are named _STL::vector).
//  * finish(int) reuses the existing reverse/symbols.csv pin
//    ?finish@Rva0019BC00Owner@@QAEXH@Z, which names the very same ILT thunk
//    (0x000026EE -> 0x0019B850) that the landed sibling
//    Rva0019BC00Owner::apply (Rva0019BC00SetFields.cpp) already calls
//    through under that name; reused here rather than minting a second name
//    for the same target.
//
// Shape notes, both read out of the retail image rather than guessed:
//  * FuncInfo 0x00DF5E78 has three unwind states and one try block (tryLow=1,
//    tryHigh=1, catchHigh=2) whose single catch has a null type descriptor --
//    catch(...). Its handler at 0x0019BB8B reloads the record from [ebp-0x14],
//    calls Dict::clear on it and re-throws (_CxxThrowException(0,0)).
//    That try block is what makes the prologue save ESP at [ebp-0x10] and spill
//    the record pointer; without it the body is 318 B, where it sat for 12
//    earlier verdicts.
//  * state 0's cleanup (0x00C076B0) takes [ebp-0x24], the push_back argument,
//    so the appended record is a temporary of the full expression: its Dict is
//    released before m_freeHead is assigned.
//  * STLport's growth path passes an empty __false_type tag by const reference;
//    MSVC 7.1 gives that 1-byte temporary no frame slot of its own and hands it
//    a dead byte of the incoming argument area (lea ecx,[ebp+0xb]). The cast
//    below reproduces that placement; a real temporary costs a frame slot retail
//    does not allocate.

#include <new>

// TU-local stand-in for Common/Dict.h; see the file banner. Only member is
// the real class's own m_data (a refcounted DictPairData*), so layout and the
// inline copy-ctor's refcount bump match retail exactly.
class Dict
{
public:
	Dict(int numPairsToPreAllocate = 0);
	Dict(const Dict &other) : m_data(other.m_data)
	{
		if (m_data)
			++*(short *)m_data;
	}
	~Dict() { releaseData(); }
	Dict &operator=(const Dict &other);
	void clear();

private:
	void releaseData();
	void *m_data;
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	__forceinline void push_back(const Type &value)
	{
		if (_M_finish != _M_end_of_storage)
		{
			new (_M_finish) Type(value);
			++_M_finish;
		}
		else
		{
			const __false_type &tag =
				*reinterpret_cast<const __false_type *>((const char *)&value + 0x2f);
			_M_insert_overflow(_M_finish, value, tag, 1, true);
		}
	}

	Type *begin() const { return _M_start; }
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);
};
}

struct Gen_t_0019a890_p16cd
{
	short next;
	short previous;
	short reserved;
	short free;
	int generation;
	Dict dict;

	Gen_t_0019a890_p16cd()
		: next(0), previous(0), reserved(0), free(0), generation(0), dict()
	{
	}

	__forceinline Gen_t_0019a890_p16cd(const Gen_t_0019a890_p16cd &other)
		: next(other.next), previous(other.previous), reserved(other.reserved),
		  free(other.free), generation(other.generation), dict(other.dict)
	{
	}
};

// Shares the ILT thunk (0x000026EE -> 0x0019B850) the landed sibling
// Rva0019BC00Owner::apply already calls through as finish(int); the class
// shape here is a minimal, declaration-only stand-in purely to reach that
// existing pinned name, same as Rva0019BC00SetFields.cpp does for prepare/finish.
class Rva0019BC00Owner
{
public:
	void finish(int index);
};

class Rva0019BE80TeamRec
{
public:
	int append(const Dict *dict);

private:
	char m_prefix[0xc];
	_STL::vector<Gen_t_0019a890_p16cd,
		_STL::allocator<Gen_t_0019a890_p16cd> > m_teams;
	short m_numActive;
	short m_freeHead;
};

int Rva0019BE80TeamRec::append(const Dict *dict)
{
	if (m_freeHead == 0)
	{
		int index = (int)(m_teams._M_finish - m_teams._M_start);
		m_teams.push_back(Gen_t_0019a890_p16cd());
		m_freeHead = (short)index;
	}

	int index = m_freeHead;
	Gen_t_0019a890_p16cd *team = m_teams.begin() + index;
	team->dict.clear();
	if (dict)
		team->dict = *dict;
	try
	{
		reinterpret_cast<Rva0019BC00Owner *>(this)->finish(index);
		m_freeHead = team->next;
		m_teams._M_start[m_teams._M_start[0].previous].next = (short)index;
		team->previous = m_teams._M_start[0].previous;
		team->next = 0;
		m_teams._M_start[0].previous = (short)index;
		++m_numActive;
	}
	catch (...)
	{
		team->dict.clear();
		throw;
	}
	return index;
}
