// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00891B80Block
{
	unsigned short m_ref;
};

// The shared empty string block at 0x012D5298 is defined once in
// game/GameEngine/Source/Common/Data/Rva012D5298.cpp as
// EAStringC::StringDataC g_rva012D5298Empty.  Only the refcount word at +0 is
// touched here, so the TU keeps its own view of the block and casts at use.
// The member is EAStringC: retail's unwind funclet uw_00c586f0 jumps straight
// to the matched ??1EAStringC@@QAE@XZ (0x00891B80) for it.
class EAStringC
{
public:
	class StringDataC;

	EAStringC();
	~EAStringC();

	Rva00891B80Block *m_block;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

inline EAStringC::EAStringC()
{
	m_block = (Rva00891B80Block *)&g_rva012D5298Empty;
	++((Rva00891B80Block *)&g_rva012D5298Empty)->m_ref;
}

class Rva008AD2C0
{
public:
	Rva008AD2C0(const Rva008AD2C0 &src);
	void assign(const Rva008AD2C0 &src);

private:
	EAStringC m_str;
	int m_f4;
	int m_f8;
	int m_fC;
	int m_f10;
	int m_f14;
	int m_f18;
	int m_f1C;
};

Rva008AD2C0::Rva008AD2C0(const Rva008AD2C0 &src)
{
	assign(src);
}
