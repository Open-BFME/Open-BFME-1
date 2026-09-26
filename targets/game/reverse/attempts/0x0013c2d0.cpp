// ??1?$vector@URva0013C2D0Record@@V?$allocator@URva0013C2D0Record@@@_STL@@@_STL@@QAE@XZ
// partial score=0.30 date=2026-09-22
// cl: -GX
// stlport
//
// Retail 0x0013C2D0, 227 bytes, a complete carved extent.  An EH-framed STLport
// vector destructor whose ELEMENT destructor is inlined, which is what the
// bytes pin down:
//
//   * the stride is 0x14 -- the tail divides the byte span by 20 with the
//     0x66666667 magic -- and the element holds a string at +0x0C and a pointer
//     at +0x10;
//   * the pointer is released first and the string second, so in declaration
//     order the string comes first;
//   * the release is `--target->m_ref.m_count; if (count <= 0) slot0(1)` where
//     the ref subobject sits at +0x24 of the target (count at +0x28, vptr at
//     +0x24), and the `mov eax,edx` copy before the test says the decremented
//     value is a named local;
//   * the string's destructor calls ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ,
//     so releaseBuffer is a private member of THAT class, not of a StringBase
//     template as the other models in this tree spell it.
//
// This bank is 214 of 227 bytes.  Two things are left and both are compiler
// choices, not spellings:
//
//   1. Retail pads the destroy loop's head to a sixteen-byte boundary with
//      `jmp $+9` and a seven-byte `lea esp,[esp]`; VC7.1 emits no pad at all
//      here, which is the whole size difference.
//   2. Retail keeps `this` in ebp and the end pointer in edi; ours takes edi
//      and ebp respectively, and every later instruction mirrors that pair.
//
// Measured on the element destructor's addressing: reading the count through
// the ref pointer (this file) gives 214/159 and keeps retail's single
// `lea ecx,[eax+0x24]`; reading and storing through `m_target->m_ref` directly
// gives 219/165 but costs a `mov ecx,eax` and a second load of m_target; the
// mixed form -- read through the object, store through the pointer -- is
// CSE'd straight back to the first.
#include <vector>

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString();
	BFMERetailAsciiString(const BFMERetailAsciiString &other);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}
	BFMERetailAsciiString &operator=(const BFMERetailAsciiString &other);

private:
	void releaseBuffer();

	void *m_data;
};

class Rva0013C2D0Ref
{
public:
	virtual void deleteInstance(int flag);

	int m_count;
};

class Rva0013C2D0Target
{
public:
	char m_lead[0x24];
	Rva0013C2D0Ref m_ref;
};

struct Rva0013C2D0Record
{
	char m_lead[0xc];
	BFMERetailAsciiString m_name;
	Rva0013C2D0Target *m_target;

	Rva0013C2D0Record();
	Rva0013C2D0Record(const Rva0013C2D0Record &other);
	Rva0013C2D0Record &operator=(const Rva0013C2D0Record &other);

	~Rva0013C2D0Record()
	{
		if (m_target != 0)
		{
			Rva0013C2D0Ref *ref = &m_target->m_ref;
			int count = ref->m_count - 1;
			ref->m_count = count;
			if (count <= 0)
				ref->deleteInstance(1);
		}
	}
};

template class _STL::vector<Rva0013C2D0Record>;
