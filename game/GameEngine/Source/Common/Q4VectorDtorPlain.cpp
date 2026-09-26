// cl: -GX-
// stlport
//
// Eight 98-byte STLport vector<T> destructors, element size 0x14, with NO
// exception frame at all:
//
//     for (p = _M_start; p != _M_finish; p += 0x14) { mov ecx,p; call <DTOR> }
//     n = (_M_end_of_storage - _M_start)                (via the /20 magic)
//     n > 0x80 ? free(_M_start) : __node_alloc::deallocate(_M_start, n)
//
// THE MISSING EH FRAME IS A COMPILER FLAG, NOT A CODE SHAPE, AND IT COST TWO
// REFUTATIONS.  The same source under the project's default flags emits the
// full three-push fs:[0] frame with EH states 0 and -1 around the destroy loop
// -- 166 bytes instead of 98 -- because vector derives from _Vector_base and
// the base's deallocation is the unwind action if an element destructor
// throws.  Defining _STLP_NO_EXCEPTIONS did NOT remove it: STLport's own
// try/catch is not what emits this frame.  `-GX-` does, and that is what this
// file's `// cl:` directive says.  So retail's translation unit for these
// eight was compiled with C++ exception handling OFF, and that fact is part of
// the evidence, not a scheduling accident.
//
// The `mov eax,0x66666667 / imul / sar edx,3 / lea eax,[eax+eax*4] / shl 2`
// sequence is the compiler dividing the byte span by 20 and multiplying back;
// it is how the element size 0x14 shows up when it is not a power of two.  The
// element destructor is called directly with ecx = the element address, so it
// is spelled as the element's own out-of-line destructor rather than as a
// subobject at offset 0 -- both produce these bytes, and the former posits one
// entity fewer.
//
// THE VARYING AXIS IS ONE FIELD: the element destructor's REL32.  Eight rows,
// eight distinct destructors, one shared element size.  Note 0x00351970 and
// 0x00351980 are adjacent bodies, so the two vectors that call them are
// genuinely different instantiations and not one address seen twice.
//
// IDENTITY IS NOT RECOVERED.  Element types are named after their destructors;
// `char m_body[0x14]` carries the size and nothing else.

#include <vector>

#define Q4_PLAIN_ELEM( T )                                                	struct T                                                              	{                                                                     		char m_body[ 0x14 ];                                              		T();                                                              		T( const T & );                                                   		~T();                                                             		T &operator=( const T & );                                        	};                                                                    	template class _STL::vector<T >;

Q4_PLAIN_ELEM( Gen00134590 )
Q4_PLAIN_ELEM( Gen002E9E10 )
Q4_PLAIN_ELEM( Gen00351970 )
Q4_PLAIN_ELEM( Gen00351980 )
Q4_PLAIN_ELEM( Gen003A4310 )
Q4_PLAIN_ELEM( Gen003B9270 )
Q4_PLAIN_ELEM( Gen0013B8E0 )
Q4_PLAIN_ELEM( Gen007701C0 )
