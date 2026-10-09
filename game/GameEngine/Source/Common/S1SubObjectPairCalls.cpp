// stlport
//
// Five __thiscall members that hand a sub-object its own first two dwords:
//
//     mov eax,[ecx+<K>+4] / mov edx,[ecx+<K>] / add ecx,<K> / push eax /
//     push edx / call <REL32> / ret
//
// WHAT THE BYTES SHOW.  ecx is ADJUSTED IN PLACE by a constant rather than
// replaced by a load, so the receiver is a sub-object at a fixed offset, not a
// stored pointer.  Both pushed values are read relative to the SAME constant,
// from that sub-object's offsets 0 and 4, and they are pushed right-to-left.
// The bare `ret` leaves the callee to clean up, making it __thiscall with two
// stack arguments.
//
// THE CALLEES ARE STLPORT RANGE ERASES.  Each REL32 lands on an ordinary ILT
// entry that jumps to a matched vector<T>::erase(T*,T*) row (0x00065960,
// 0x000FAF90, 0x003668E0, 0x003A3280; tools/callees.py), and the two pushed
// dwords are the embedded vector's _M_start and _M_finish, so each body is
// `v.erase(v.begin(), v.end())`.  000FB1F0 and 003C3AC0 share the element
// type while embedding the vector at different offsets (4 and 0x68).
//
// THE SPELLING IS NOT FREE HERE.  Binding the sub-object to a reference first
// is what makes MSVC 7.1 adjust `this` in place with `add ecx,K`, which is what
// retail does.
//
// The element payloads repeat the declarations of the TUs that own those erase
// rows.  The owners' identities are not recovered: names are address-derived,
// and the leading char arrays are padding that reproduces a proven offset.

#include <vector>

struct Gen_t_00065960_p4cd { int a[1]; Gen_t_00065960_p4cd(); Gen_t_00065960_p4cd(const Gen_t_00065960_p4cd&); ~Gen_t_00065960_p4cd(); Gen_t_00065960_p4cd& operator=(const Gen_t_00065960_p4cd&); };

struct BfmeVecElem_000FAFF0
{
	char m_body[ 0x60 ];

	~BfmeVecElem_000FAFF0();
	BfmeVecElem_000FAFF0();
	BfmeVecElem_000FAFF0( const BfmeVecElem_000FAFF0 & );
	BfmeVecElem_000FAFF0 &operator=( const BfmeVecElem_000FAFF0 & );
};

class LivingWorldPlayerArmy
{
public:
	LivingWorldPlayerArmy &operator=( const LivingWorldPlayerArmy &other );
	virtual ~LivingWorldPlayerArmy();

private:
	char m_body[ 0x54 ];
};

class Open2Elem3A3280
{
public:
	~Open2Elem3A3280();

private:
	char m_storage[ 0xb8 ];
};

// The erase bodies are matched in their own TUs; declaring the specializations
// keeps this TU from instantiating a second copy.
namespace _STL
{
template<> Gen_t_00065960_p4cd *vector<Gen_t_00065960_p4cd>::erase(
	Gen_t_00065960_p4cd *first, Gen_t_00065960_p4cd *last );
template<> BfmeVecElem_000FAFF0 *vector<BfmeVecElem_000FAFF0>::erase(
	BfmeVecElem_000FAFF0 *first, BfmeVecElem_000FAFF0 *last );
template<> LivingWorldPlayerArmy *vector<LivingWorldPlayerArmy>::erase(
	LivingWorldPlayerArmy *first, LivingWorldPlayerArmy *last );
template<> Open2Elem3A3280 *vector<Open2Elem3A3280>::erase(
	Open2Elem3A3280 *first, Open2Elem3A3280 *last );
}

#define BFME_PAIR_CALL( NAME, ELEM, LEAD )                               \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void forward();                                                   \
		char m_lead[ LEAD ];                                              \
		_STL::vector<ELEM> m_sub;                                         \
	};                                                                    \
	void NAME::forward()                                                  \
	{                                                                     \
		_STL::vector<ELEM> &sub = m_sub;                                  \
		sub.erase( sub.begin(), sub.end() );                              \
	}

BFME_PAIR_CALL( Rva00065A40, Gen_t_00065960_p4cd, 4 )
BFME_PAIR_CALL( Rva000FB1F0, BfmeVecElem_000FAFF0, 4 )
BFME_PAIR_CALL( Rva00366C80, LivingWorldPlayerArmy, 0x18 )
BFME_PAIR_CALL( Rva003A3580, Open2Elem3A3280, 0x2C )
BFME_PAIR_CALL( Rva003C3AC0, BfmeVecElem_000FAFF0, 0x68 )
