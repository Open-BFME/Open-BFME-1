// cl: -GX-
// stlport
//
// Open-BFME5: the STLport allocator entry points whose partner did NOT sit
// next to them. U5StlAllocatorWidths.cpp took the eighteen adjacent
// allocate/deallocate pairs; fifteen of them match by
// element width but not by address, so nothing in the bytes says they come from
// the same instantiation and none of them is grouped with another here.
//
// Each body therefore gets an instantiation of its own, named for its own
// address, and claims exactly one member of it. The sibling member each
// instantiation also emits is left unclaimed rather than folded onto a body the
// bytes do not pick out -- the same caution U4StlAllocatorWidths.cpp records.
//
// The shape is unchanged: `allocate(n, hint)` is `ret 8` with ecx never read and
// the hint never touched, `deallocate(p, n)` the mirror, and the element width
// is the sole immediate in each. Identity is not recovered; `char m_body[WIDTH]`
// carries a size and nothing else. Three further bodies in the same sweep --
// 0x0014B450, 0x0014B550 and 0x00784C30 -- are already real C++ under
// address-derived names of their own and are left alone.

#include <vector>

#define U6_ALLOC_WIDTH( NAME, SZ )                                            	struct NAME                                                               	{                                                                         		char m_body[ SZ ];                                                    		NAME();                                                               		NAME( const NAME & );                                                 		~NAME();                                                              		NAME &operator=( const NAME & );                                      	};                                                                        	template class _STL::vector<NAME >;

U6_ALLOC_WIDTH( U6Elem000BA370, 0x70 )
U6_ALLOC_WIDTH( U6Elem000F9B10, 0x60 )
U6_ALLOC_WIDTH( U6Elem00122910, 0x84 )
U6_ALLOC_WIDTH( U6Elem001340F0, 0x5C )
U6_ALLOC_WIDTH( U6Elem00134130, 0x24 )
U6_ALLOC_WIDTH( U6Elem00134170, 0xEC )
U6_ALLOC_WIDTH( U6Elem003A2410, 0xB8 )
U6_ALLOC_WIDTH( U6Elem004F9B80, 0x338 )
U6_ALLOC_WIDTH( U6Elem005858D0, 0x50 )
U6_ALLOC_WIDTH( U6Elem000BA4F0, 0x70 )
U6_ALLOC_WIDTH( U6Elem000CA8F0, 0x60 )
U6_ALLOC_WIDTH( U6Elem00122630, 0x84 )
U6_ALLOC_WIDTH( U6Elem00133DA0, 0x5C )
U6_ALLOC_WIDTH( U6Elem00133E20, 0xEC )
U6_ALLOC_WIDTH( U6Elem002BC720, 0xB8 )
U6_ALLOC_WIDTH( U6Elem00585820, 0x50 )
