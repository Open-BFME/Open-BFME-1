// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// ?getFontFromTemplate@HeaderTemplateManager@@QAEPAVGameFont@@VAsciiString@@@Z
//
// The retail manager keeps a circular list at this+0x00.  Each list node
// links at +0x00 and stores its HeaderTemplate at +0x08; the template keeps
// its GameFont pointer at +0x00 and its inline AsciiString name at +0x04.
// The caller-backed lookup at 0x0048C8C0 compares StringBase length/data and
// returns the matching template.  Its direct-body pin lets the resolver
// derive the retail ILT 0x0004881A without adding an ILT identity claim.

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );
};

class AsciiString
{
public:
	AsciiString( const AsciiString &other )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}

private:
	char *m_data;
};

class GameFont;

class HeaderTemplate
{
public:
	GameFont *m_font;

private:
	AsciiString m_name;
};

class HeaderTemplateManager
{
public:
	HeaderTemplate *findHeaderTemplate( AsciiString name );
	GameFont *getFontFromTemplate( AsciiString name );
};

GameFont *HeaderTemplateManager::getFontFromTemplate( AsciiString name )
{
	HeaderTemplate *header = findHeaderTemplate( name );
	if (!header)
		return 0;
	return header->m_font;
}
