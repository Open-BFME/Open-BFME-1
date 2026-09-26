// cl: -GX-
// stlport
//
// Open-BFME5: nineteen more ADJACENT PAIRS of STLport allocator entry points --
// `allocator<T>::allocate(n, hint)` and `allocator<T>::deallocate(p, n)` --
// found the same way U4StlAllocatorWidths.cpp's two were, and carrying the same
// argument: an adjacent allocate/deallocate pair can only come from a TU that
// instantiates the container whole, so one `template class _STL::vector<T>` per
// width produces both members in that order.
//
// These were located by byte signature rather than by name. Every allocate in
// the image opens `8b 44 24 04 85 c0 74` and every deallocate
// `8b 4c 24 04 85 c9 74`; 66 allocate dumps and 47 deallocate dumps still carry
// nothing but machine bytes, and the ones below are those that pair up -- same
// element width, deallocate within 0x80 bytes of its allocate.
//
// The only axis is sizeof(value_type), the sole immediate in each body, and the
// encoding of that immediate is the whole of the 46-versus-49 and 47-versus-50
// length difference: widths through 0x7F take `6b c0 <imm8>`, wider ones
// `69 c0 <imm32>`, and 16 comes out as a scale-1 lea and a shift of four.
//
// IDENTITY IS NOT RECOVERED. `char m_body[WIDTH]` carries a size and nothing
// else, and the element names are derived from the addresses of the rows they
// serve.

#include <vector>

#define U5_ALLOC_WIDTH( NAME, SZ )                                            	struct NAME                                                               	{                                                                         		char m_body[ SZ ];                                                    		NAME();                                                               		NAME( const NAME & );                                                 		~NAME();                                                              		NAME &operator=( const NAME & );                                      	};                                                                        	template class _STL::vector<NAME >;

U5_ALLOC_WIDTH( U5Elem0013AAC0, 0x128 )
U5_ALLOC_WIDTH( U5Elem0013AB40, 0xBC )
U5_ALLOC_WIDTH( U5Elem00193090, 0x8C )
U5_ALLOC_WIDTH( U5Elem001C0540, 0x5C )
U5_ALLOC_WIDTH( U5Elem002E3CE0, 0x54 )
U5_ALLOC_WIDTH( U5Elem00361620, 0xB4 )
U5_ALLOC_WIDTH( U5Elem003616B0, 0x58 )
U5_ALLOC_WIDTH( U5Elem0037DAE0, 0xE0 )
U5_ALLOC_WIDTH( U5Elem0039D140, 0x88 )
U5_ALLOC_WIDTH( U5Elem003A6600, 0xDC )
U5_ALLOC_WIDTH( U5Elem0063B2F0, 0x2B8 )
U5_ALLOC_WIDTH( U5Elem0063B3F0, 0x864 )
U5_ALLOC_WIDTH( U5Elem006441C0, 0x194 )
U5_ALLOC_WIDTH( U5Elem006442C0, 0x330 )
U5_ALLOC_WIDTH( U5Elem006524F0, 0x210 )
U5_ALLOC_WIDTH( U5Elem006525F0, 0x1F0 )
U5_ALLOC_WIDTH( U5Elem00697460, 0x78 )
U5_ALLOC_WIDTH( U5Elem0075DD00, 0x6C )
