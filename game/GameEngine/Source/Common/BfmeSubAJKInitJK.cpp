// Open-BFME: 0x0074E820, the initialiser the matched ?bfmeClearJK@BfmeBigJK
// calls with the literal 1 (game/GameEngine/Source/Common/BfmeConv2077.cpp).
// It appends `count` copies of an all-zero 36-byte element to the vector that
// starts at offset 0 of this object.
//
// Evidence for the element shape (retail 0x0074E820, 122 bytes):
//   * nine dwords are copied with `rep movsd` (mov ecx,9), so the element is
//     36 bytes and is passed BY VALUE -- the callee at 0x0074E710 is
//     ?resize@?$vector@UGen_t_0074d9c0_p128pod@@V?$allocator@...@_STL@@@_STL@@
//     QAEXIUGen_t_0074d9c0_p128pod@@@Z, whose `ret 0x28` eats 36+4 bytes;
//   * the first 32 bytes are written as eight `mov dword [esp+N], 0`
//     IMMEDIATE stores while the last four bytes are written from CL/CX.
//     MSVC 7.1 only drops a zero float store to an immediate; the same eight
//     stores written as `int` fields collapse into one zeroed scratch register.
//     So the leading eight fields are floats (each 0.0f) and the tail is a
//     byte, a byte and a word;
//   * the zero register is ECX (`xor ecx,ecx`) and the receiver is carried in
//     EAX, which is the allocation this statement order selects.

// The retail element type; its real identity is only known through the matched
// vector::resize row above, so it keeps the address token here.
struct Gen36_0074E820
{
	float m_values[8];
	unsigned char m_firstFlag;
	unsigned char m_secondFlag;
	unsigned short m_mode;
};

// The retail container.  It is reached through the incremental-link thunk
// ?j_00025bf3@@YAXXZ (0x00025BF3), which tail-jumps to the matched resize, so
// the call is issued through a member-pointer cast rather than a direct call.
class Vec36_0074E820
{
public:
	void resize(unsigned count, Gen36_0074E820 value);

	Gen36_0074E820 *m_start;
	Gen36_0074E820 *m_finish;
	Gen36_0074E820 *m_end;
};

void j_00025bf3(void);

union ResizeThunk_0074E820
{
	void (*raw)();
	void (Vec36_0074E820::*mem)(unsigned, Gen36_0074E820);
};

class BfmeSubAJK
{
public:
	void bfmeInitJK(int a);

	unsigned char m_bfmeGapJK[12];
};

void BfmeSubAJK::bfmeInitJK(int a)
{
	Gen36_0074E820 element;
	element.m_values[0] = 0.0f;
	element.m_values[1] = 0.0f;
	element.m_values[2] = 0.0f;
	element.m_values[3] = 0.0f;
	element.m_values[4] = 0.0f;
	element.m_values[5] = 0.0f;
	element.m_values[6] = 0.0f;
	element.m_values[7] = 0.0f;
	element.m_firstFlag = 0;
	element.m_secondFlag = 0;
	element.m_mode = 0;

	ResizeThunk_0074E820 resize;
	resize.raw = j_00025bf3;
	(reinterpret_cast<Vec36_0074E820 *>(this)->*resize.mem)(a, element);
}
