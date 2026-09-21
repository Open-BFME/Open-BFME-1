// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// INILineBuffer -- BFME's INI line array. Zero Hour streams the file and keeps
// one line at a time in a fixed buffer; BFME reads the whole file in and splits
// it, so it needs something to hold the split result. The class name is
// provisional and comes from reverse/symbols.csv, which decoded both bodies
// below from their call sites in INI::readLine and INI::load.
//
// The layout is read straight off the two functions and nothing more is claimed
// than they show:
//
//   +0x00  untouched by either body
//   +0x04  a buffer freed with one-argument operator delete by clear()
//   +0x08  start   \
//   +0x0c  finish   |  a vector of 8-byte elements: getText divides
//   +0x10  end_of_storage /   (finish - start) by 8 to bound the index
//
// getText reads the FIRST four bytes of element[index] (`mov eax,[ecx+eax*8]`),
// so the text pointer is the element's first member. What the other four bytes
// are is not visible from these two bodies and is left named but unexplained.

#include <vector>

typedef char Char;
typedef int Int;
typedef int Bool;

struct INILine
{
	const char *m_text;		// +0x00 -- what getText returns
	Int m_unknown4;			// +0x04 -- neither body reads it
};

class INILineBuffer
{
public:
	const char *getText( Int index ) const;
	void clear( void );

private:
	void *m_unknown0;					// +0x00
	char *m_buffer;						// +0x04
	std::vector<INILine> m_lines;		// +0x08
};

// Retail 0x009CBC60, 33 bytes. Note there is no lower bound: retail compares the
// index against the count with a signed jge and returns null only on the high
// side, so a negative index is not rejected.
const char *INILineBuffer::getText( Int index ) const
{
	// Spelled as the in-range case first. Retail falls through to the element
	// and jumps away for the null, which is the block order this shape gives;
	// `if (index >= size) return NULL;` emits the two blocks the other way round
	// with the branch inverted.
	if (index < (Int)m_lines.size()) {
		// m_lines[index], not begin()[index]: retail re-loads the start pointer
		// (`mov ecx,[ecx+8]`) after the bound test rather than keeping the one
		// it already had, which is what indexing the container again emits.
		return m_lines[index].m_text;
	}

	return NULL;
}

// Retail 0x009CBF50, 69 bytes. The erase is spelled as a range rather than
// clear(): retail emits the copy loop that erase(first, last) expands to, with
// its trip count computed as (finish - last) / 8 -- which is zero here, so the
// loop never runs, but it is still emitted.
void INILineBuffer::clear( void )
{
	m_lines.erase( m_lines.begin(), m_lines.end() );

	if (m_buffer != NULL) {
		delete [] m_buffer;
		m_buffer = NULL;
	}
}

// ?Rva001F9140NoOp@@YAXXZ
void Rva001F9140NoOp()
{
}
