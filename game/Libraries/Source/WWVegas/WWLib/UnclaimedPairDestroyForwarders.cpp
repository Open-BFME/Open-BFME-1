// cl: /DNDEBUG /MD /EHsc
// Three unreferenced nine-byte cdecl bodies of one shape:
//
//     mov ecx,[esp+4] / jmp <pair destructor>
//
// Each destroys the map node payload (`_STL::pair<const K, V>`) its single
// argument points at by tail-jumping to that pair's destructor, the shape of
// STLport's `_Destroy(T *)` once the destructor is out of line. Each sits alone
// in an int3-padded .text gap no ledger row covered, and no call, ILT stub,
// table slot or dir32 name reaches it.
//
//   0x0094C630 -> 0x0094BFD0, pinned as the int/p16cd pair destructor
//   0x009C9500 -> ILT 0x0002C2A0 (pinned as the k4/p4pod pair destructor)
//   0x009D0D60 -> 0x009D0A50, the k4/p12cd pair destructor row
//
// IDENTITY IS NOT RECOVERED: the wrappers keep address-derived names, and the
// pair types are the generated payload stand-ins the destructor rows already
// use. No STLport header is included: only the destructor declarations are
// needed, so the pair is declared, not defined.

struct Gen_t_0094c740_p16cd;
struct Gen_t_009c9700_k4;
struct Gen_t_009c9700_p4pod;
struct Gen_t_009d0a50_k4;
struct Gen_t_009d0a50_p12cd;

namespace _STL
{
template <class _T1, class _T2> struct pair
{
	~pair();
};
}

typedef _STL::pair<const int, Gen_t_0094c740_p16cd> Rva0094C630Pair;
typedef _STL::pair<const Gen_t_009c9700_k4, Gen_t_009c9700_p4pod> Rva009C9500Pair;
typedef _STL::pair<const Gen_t_009d0a50_k4, Gen_t_009d0a50_p12cd> Rva009D0D60Pair;

void Rva0094C630Destroy(Rva0094C630Pair *pointer)
{
	pointer->~Rva0094C630Pair();
}

void Rva009C9500Destroy(Rva009C9500Pair *pointer)
{
	pointer->~Rva009C9500Pair();
}

void Rva009D0D60Destroy(Rva009D0D60Pair *pointer)
{
	pointer->~Rva009D0D60Pair();
}
