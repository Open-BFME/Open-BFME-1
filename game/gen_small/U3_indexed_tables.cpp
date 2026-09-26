// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: four more relocation-free __thiscall bodies out of
// d_0005b6c0.asm, all of them indexed-table arithmetic.
//
// Nothing here touches a global, so every byte is proof and nothing names them.
// What the bytes DO fix exactly is the element strides, which is the whole
// content of these functions:
//
//   0x0007C190  counts at this+0x16F0 stride 4, rows of 32 entries of 32 bytes
//               based at this+0x160, capped at 32 per row
//   0x0007C480  elements of 16 bytes based at this+0x124, three fields copied
//               into a five-slot block at this+0x16D0
//   0x0007C550  elements of 48 bytes based at this+0x1C (the `lea eax,[eax+eax*2]
//               / shl eax,4` is the 48 multiply)
//   0x0007BC70  a plain store to this+0x1734
//
// 0x0007C190 and 0x0007BC70 are modelled as ONE class: 0x160, 0x16F0 and 0x1734
// sit in that order with room for both. 0x0007C480 and 0x0007C550 are modelled
// separately even though they plainly belong to the same object as the others
// (0x16D0 is inside the same block) -- 0x124 is not a whole number of 48-byte
// elements past 0x1C, so the two array bases cannot be reconciled into one
// layout from these bodies alone, and inventing a wrong shared layout would be
// worse than admitting three address-derived models.

typedef int Int;

// ---------------------------------------------------------------------------

struct Rva0007C190Entry
{
	unsigned char m_unreconstructed_00[32];
};

class Rva0007C190Table
{
public:
	Rva0007C190Entry *allocate(Int row);
	void setValue1734(Int value);

private:
	unsigned char m_unreconstructed_0000[0x160];
	Rva0007C190Entry m_entries[5][32];					///< retail this+0x0160
	unsigned char m_unreconstructed_1560[0x190];
	Int m_counts[5];									///< retail this+0x16F0
	unsigned char m_unreconstructed_1704[0x30];
	Int m_value1734;									///< retail this+0x1734
};

// ?allocate@Rva0007C190Table@@QAEPAURva0007C190Entry@@H@Z
Rva0007C190Entry *Rva0007C190Table::allocate(Int row)
{
	if (m_counts[row] < 32)
	{
		m_counts[row] = m_counts[row] + 1;
		return &m_entries[row][m_counts[row]];
	}

	return 0;
}

// ?setValue1734@Rva0007C190Table@@QAEXH@Z
void Rva0007C190Table::setValue1734(Int value)
{
	m_value1734 = value;
}

// ---------------------------------------------------------------------------

struct Rva0007C480Element
{
	Int m_field00;										///< element+0x00
	Int m_field04;										///< element+0x04
	Int m_field08;										///< element+0x08
	Int m_field0C;										///< element+0x0C
};

class Rva0007C480Table
{
public:
	void select(Int index);

private:
	unsigned char m_unreconstructed_0000[0x124];
	Rva0007C480Element m_elements[346];					///< retail this+0x0124
	unsigned char m_unreconstructed_16C4[12];
	Int m_value16D0;									///< retail this+0x16D0
	Int m_value16D4;									///< retail this+0x16D4
	Int m_value16D8;									///< retail this+0x16D8
	Int m_value16DC;									///< retail this+0x16DC
	Int m_value16E0;									///< retail this+0x16E0
};

// ?select@Rva0007C480Table@@QAEXH@Z
void Rva0007C480Table::select(Int index)
{
	m_value16D0 = 0;
	m_value16D4 = m_elements[index].m_field00;
	m_value16D8 = 0;
	m_value16DC = m_elements[index].m_field04;
	m_value16E0 = m_elements[index].m_field08;
}

// ---------------------------------------------------------------------------

struct Rva0007C550Element
{
	Int m_field00;										///< element+0x00
	unsigned char m_unreconstructed_04[44];
};

class Rva0007C550Table
{
public:
	Int getField00(Int index) const;

private:
	unsigned char m_unreconstructed_0000[0x1C];
	Rva0007C550Element m_elements[64];					///< retail this+0x001C
};

// ?getField00@Rva0007C550Table@@QBEHH@Z
Int Rva0007C550Table::getField00(Int index) const
{
	return m_elements[index].m_field00;
}
