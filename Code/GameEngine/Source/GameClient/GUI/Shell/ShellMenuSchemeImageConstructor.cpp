// cl: /DNDEBUG /MD /EHsc
// readable body of ??0ShellMenuSchemeImage@@QAE@XZ: Code/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp

// Open-BFME5: ShellMenuSchemeImage::ShellMenuSchemeImage, retail 0x005807D0,
// 74 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// Zero Hour's constructor accounts for every store, including two oddities
// that would look like mistakes in the disassembly:
//
//   m_position.x = m_position.y = 0;
//
// is a chained assignment, so y at +8 is stored before x at +4 -- which is why
// retail writes +8, then +4, and not in address order.
//
//   m_size.x = m_size.x = 0;
//
// names x twice. It is a typo in the original, and BFME kept it: m_size.y at
// +0x10 is never written, which is exactly what retail does.
//
// The string member is cleared through StringBase<char>::clear, which the
// ledger already places at 0x00887940 folded with releaseBuffer, and the
// unwind state around it is there to destroy that member if it throws.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

class Image;

template <class T>
class StringBase
{
public:
	StringBase(void) : m_data(0) {}
	~StringBase(void) { releaseBuffer(); }

	void clear(void);					// retail 0x00887940

private:
	void releaseBuffer(void);				// retail 0x00887940

	T *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeImage
{
public:
	ShellMenuSchemeImage(void);

	StringBase<char> m_name;				// +0x00
	ICoord2D m_position;					// +0x04
	ICoord2D m_size;					// +0x0C
	Image *m_image;						// +0x14
};

// ??0ShellMenuSchemeImage@@QAE@XZ
ShellMenuSchemeImage::ShellMenuSchemeImage(void)
{
	m_name.clear();
	m_position.x = m_position.y = 0;
	m_size.x = m_size.x = 0;
	m_image = 0;
}
