// cl: -GX-
// stlport
//
// Nine STLport vector<T> destructors with NO exception frame at all -- the same
// source shape already landed for element size 0x14 in Q4VectorDtorPlain.cpp,
// here over nine larger element sizes:
//
//     for (p = _M_start; p != _M_finish; p += WIDTH) { mov ecx,p; call <DTOR> }
//     n = (_M_end_of_storage - _M_start)              (magic divide by WIDTH)
//     n > 0x80 ? operator delete(_M_start)
//              : __node_alloc::deallocate(_M_start, n)
//
// THE MISSING EH FRAME IS A COMPILER FLAG, NOT A CODE SHAPE.  The same source
// under the project's default flags emits the full three-push fs:[0] frame with
// EH states around the destroy loop, because vector derives from _Vector_base
// and the base's deallocation is the unwind action if an element destructor
// throws.  `-D_STLP_NO_EXCEPTIONS` does NOT remove it -- STLport's own
// try/catch is not what emits it -- `-GX-` does, which is what this file's
// `// cl:` directive says.  That flag is part of the evidence.
//
// TWO AXES, BOTH READ DIRECTLY: the element destructor's REL32 and the element
// size. Nine element types, nine DISTINCT destructors. Width 0x38 repeats
// (at 0x006F2A70 and 0x00770650), but their
// destructors differ, so those are genuinely different instantiations and each
// gets its own element type here.  The 97/103 split in body length is not a
// third axis: 0x80 and above needs `add esi,imm32` and `imul eax,eax,imm32`
// instead of the imm8 forms, which is exactly six bytes.
//
// The element destructor is called directly with ecx = the element address, so
// it is spelled as the element's own out-of-line destructor rather than as a
// subobject at offset 0 -- both produce these bytes, and the former posits one
// entity fewer.
//
// IDENTITY IS NOT RECOVERED.  Element types are named after their destructors;
// `char m_body[SIZE]` carries the size and nothing else.

#include <vector>

#define R4_WIDE_ELEM( T, SZ )                                                 \
	struct T                                                                  \
	{                                                                         \
		char m_body[ SZ ];                                                    \
		T();                                                                  \
		T( const T & );                                                       \
		~T();                                                                 \
		T &operator=( const T & );                                            \
	};                                                                        \
	template class _STL::vector<T >;

R4_WIDE_ELEM( Gen002BC7A0, 0xB8 )
R4_WIDE_ELEM( Gen003CDE30, 0x3C )
R4_WIDE_ELEM( Gen00425060, 0x1C )
R4_WIDE_ELEM( Gen00606F70, 0x1F0 )
R4_WIDE_ELEM( Gen00695630, 0x78 )
R4_WIDE_ELEM( Gen006EDEA0, 0x38 )
R4_WIDE_ELEM( Gen00762250, 0x38 )
// The 0x128-byte element's destructor is the matched ModelConditionInfo body
// at 0x0013C3F0; unique ILT 0x0002306F independently anchors that identity.
R4_WIDE_ELEM( ModelConditionInfo, 0x128 )
R4_WIDE_ELEM( Gen00774D40, 0xBC )
// Recovered Video lifecycle owns its distinct variants in GameClient/VideoVectorDestruction.cpp.
