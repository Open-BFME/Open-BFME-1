// ?rva00892FD0@Rva00892FD0Table@@QAE_NHH@Z
// partial score=0.88 date=2026-09-25
// Retail 0x00892FD0, 71 bytes, a carved extent.  A __thiscall predicate over an
// array of eight-byte entries: count at +0x00, entry array at +0x08, the tested
// field at +0x04 of each entry, two dword arguments, `mov al,1` / `xor al,al`
// exits and `ret 8`.  `this` stays in ecx the whole way and is never copied out.
//
// Size is exact at 71 bytes with this shape and 27 bytes differ.  The load that
// decides the size is the array pointer: retail reads [ecx+8] ONCE before the
// guard and again in the latch, while the plain member form reads it once and
// keeps it, which compiles to 54 bytes.  Qualifying the array pointer volatile
// restores the latch reload and the 71-byte extent.
//
// What is still wrong: retail computes the end as `mov edx,eax / add edx,esi`
// keeping the byte count in esi across the loop, and VC7.1 folds it into
// `lea eax,[esi+edx]`.  Exhausted: the do-while shape with the end recomputed
// in the body (which removes the extra guard read but keeps the lea, 29 bytes),
// a split `end = entry; end += m_count;`, and the full sib/register/loop/copy/
// store/frame sweep from tools/shape_family_levers.py (four trials, all 0.59).
//
// IDENTITY IS NOT RECOVERED; the name is address-derived.

struct Rva00892FD0Entry
{
	int m_00;
	int m_key;
};

class Rva00892FD0Table
{
public:
	bool rva00892FD0(int first, int second);

private:
	int m_count;
	int m_pad;
	Rva00892FD0Entry *volatile m_entries;
};

bool Rva00892FD0Table::rva00892FD0(int first, int second)
{
	Rva00892FD0Entry *entry = m_entries;
	Rva00892FD0Entry *end = entry + m_count;
	if (entry != end)
	{
		do
		{
			if (entry->m_key != first && entry->m_key != second)
				return false;
			++entry;
		} while (entry != m_entries + m_count);
	}

	return true;
}
