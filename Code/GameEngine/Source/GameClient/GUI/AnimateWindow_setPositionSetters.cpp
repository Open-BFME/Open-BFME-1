// cl: /DNDEBUG /MD /EHsc
// Clean C++ layout view for the two trivial AnimateWindow position setters:
// setStartPos at retail 0x00495370 and setEndPos at retail 0x004953B0.
// Their caller-visible ABI is two four-byte ICoord2D slots; the proven object
// offsets are start +0x08/+0x0c and end +0x10/+0x14 after the class prefix.

typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

class AnimateWindow
{
public:
	void setStartPos(ICoord2D value);
	void setEndPos(ICoord2D value);

private:
	unsigned char m_prefix[8];
	ICoord2D m_startPos;
	ICoord2D m_endPos;
};

// ?setStartPos@AnimateWindow@@QAEXUICoord2D@@@Z
void AnimateWindow::setStartPos(ICoord2D value)
{
	m_startPos = value;
}

// ?setEndPos@AnimateWindow@@QAEXUICoord2D@@@Z
void AnimateWindow::setEndPos(ICoord2D value)
{
	m_endPos = value;
}
