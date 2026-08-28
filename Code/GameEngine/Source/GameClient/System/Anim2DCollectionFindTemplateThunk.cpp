// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the Anim2DCollection::findTemplate naked dump to clean C++.
//
// Zero Hour's Anim2D.cpp loop. What retail spells out is the comparison: it
// takes the shorter of the two lengths, runs an inline memcmp over that many
// bytes, and falls back to the length difference when the prefixes are equal.
// That is a three-way compare tested against zero, not a plain strcmp -- the
// `repe cmpsb` followed by `sbb eax,eax / sbb eax,-1` is MSVC's memcmp
// intrinsic returning -1, 0 or 1.
//
// getName returns AsciiString by value, so retail builds a temporary through a
// hidden pointer and destroys it after the comparison but before the branch --
// which is exactly the lifetime of a temporary in the condition of an if.
//
// Both operands are read through two separate null tests of m_data, one for the
// length at data+0x04 and one for the characters at data+0x08, so the length
// and the string are two inline accessors rather than one.
//
// Retail pins the layout: the list head is at collection+0x08 and each
// template's next pointer is at +0x04.

typedef int Int;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[4];
	unsigned short m_len;								///< retail this+0x04
	unsigned char m_unreconstructed_06[2];
	char m_chars[1];									///< retail this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString();
	~AsciiString();

	Int len(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? m_data->m_chars : ""; }

private:
	AsciiStringData *m_data;
};

inline bool operator==(const AsciiString &a, const AsciiString &b)
{
	Int blen = b.len();
	const char *bs = b.str();
	Int alen = a.len();
	const char *as = a.str();
	Int count = (alen < blen) ? alen : blen;

	Int cmp = memcmp(as, bs, count);
	Int result = cmp ? cmp : (alen - blen);

	return result == 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h
class Anim2DTemplate
{
public:
	AsciiString getName(void) const;					///< ILT thunk at 0x00012E72

	Anim2DTemplate *friend_getNextTemplate(void) const { return m_nextTemplate; }

private:
	unsigned char m_unreconstructed_00[4];
	Anim2DTemplate *m_nextTemplate;						///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h
class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);

private:
	unsigned char m_unreconstructed_00[8];
	Anim2DTemplate *m_templateList;						///< retail this+0x08
};

// ?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
Anim2DTemplate *Anim2DCollection::findTemplate( const AsciiString& name )
{

	// search the list
	for( Anim2DTemplate *animTemplate = m_templateList;
			 animTemplate;
			 animTemplate = animTemplate->friend_getNextTemplate() )
	{

		if( animTemplate->getName() == name )
			return animTemplate;

	}  // end for

	return 0;  // template not found

}
