// carved dump placeholder: d_0045c8f0
// cl: /DNDEBUG /DWIN32 /MD
//
// Carved body at retail 0x0045C8F0, a member of View's marker list at +0x80
// (targets/game/reverse/identity_evidence/0045c9e0.md). Same View/Rva0045C9E0CameraMarker/
// AsciiString layout the landed CameraMarkerListFind.cpp proves (the +0x80
// marker-list head, the node's m_next-then-m_name shape, and the
// StringBase-style compare()/operator== codegen: MSVC 7.1 inlines the
// min-length compare as `repe cmpsb` here instead of a memcmp call, but the
// length/text extraction and the empty-string fallback to the same shared
// ?Rva006A16B0Empty@@3PADA constant are byte-identical). The one-argument,
// `ret 4` signature and the `link = &(*link)->m_next` idiom (exploiting
// m_next being the node's first field, so a node's own address doubles
// as the address of its own m_next) match removeMarker0045CA80()'s traversal
// exactly, but on a name match this body SPLICES `replacement` into the list in
// place of the matched node and returns the displaced node, instead of deleting
// it. No landed caller names the purpose, so the method keeps the address token.

typedef int Int;

extern "C" int __cdecl memcmp( const void *, const void *, unsigned int );
#pragma intrinsic(memcmp)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	Int compare( const AsciiString &that ) const
	{
		const Int thatLength = that.m_data ? that.m_data->length : 0;
		const char *thatText = that.m_data ? that.m_data->text : "";
		const Int thisLength = m_data ? m_data->length : 0;
		const char *thisText = m_data ? m_data->text : "";
		Int result = memcmp( thisText, thatText,
			thisLength < thatLength ? thisLength : thatLength );
		if ( result != 0 )
			return result;
		return thisLength - thatLength;
	}

private:
	struct Data
	{
		Int refs;
		unsigned short length;
		unsigned short capacity;
		char text[1];
	};

	Data *m_data;
};

inline bool operator==( const AsciiString &left, const AsciiString &right )
{
	return left.compare( right ) == 0;
}

struct Rva0045C9E0CameraMarker
{
	Rva0045C9E0CameraMarker *m_next;
	AsciiString m_name;
};

class View
{
public:
	Rva0045C9E0CameraMarker *replaceMarker0045C8F0(
		Rva0045C9E0CameraMarker *replacement );

private:
	char m_unknown[0x80];  // laid out in ViewConstructorBfme.cpp
	Rva0045C9E0CameraMarker *m_markers;
};

Rva0045C9E0CameraMarker *View::replaceMarker0045C8F0(
	Rva0045C9E0CameraMarker *replacement )
{
	Rva0045C9E0CameraMarker *result = 0;
	Rva0045C9E0CameraMarker **link = &m_markers;
	while ( *link )
	{
		if ( (*link)->m_name == replacement->m_name )
		{
			Rva0045C9E0CameraMarker *old = *link;
			*link = replacement;
			replacement->m_next = old->m_next;
			old->m_next = 0;
			result = old;
			break;
		}
		link = &(*link)->m_next;
	}
	return result;
}
