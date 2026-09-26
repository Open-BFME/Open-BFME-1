// cl: /DNDEBUG /DWIN32 /MD
//
// View's marker list at +0x80: lookup, cleanup and unlink-by-name.
// ScriptActions::doMoveCameraTo (0x002F24F0) calls findMarker0045C9E0 with ECX
// = TheTacticalView, unadjusted, and the View constructor 0x0045B8C0 zeroes
// +0x80 itself, so the list is a View member (reverse/identity_evidence/
// 0045c9e0.md).  Nothing names these methods or the node type, so they keep
// their addresses.
//
// This is not the waypoint lookup upstream's doMoveCameraTo uses: BFME still
// has ?getWaypointByName@TerrainLogic@@UAEPAVWaypoint@@VAsciiString@@@Z,
// matched at 0x001AA900, so the camera resolves its target through a second,
// separate named list that lives on the client side.

typedef int Int;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	Int compare(const AsciiString &that) const
	{
		const Int thatLength = that.m_data ? that.m_data->length : 0;
		const char *thatText = that.m_data ? that.m_data->text : "";
		const Int thisLength = m_data ? m_data->length : 0;
		const char *thisText = m_data ? m_data->text : "";
		Int result = memcmp(thisText, thatText,
			thisLength < thatLength ? thisLength : thatLength);
		if (result != 0)
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

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

struct Rva0045C9E0CameraMarker
{
	~Rva0045C9E0CameraMarker();

	Rva0045C9E0CameraMarker *m_next;
	AsciiString m_name;
};

// ??1Rva0045C9E0CameraMarker@@QAE@XZ present-unmatched -- the node destructor is
// real (its ILT is pinned at 0x00028984 and clearMarkers0045C8A0() calls it), but
// no row here claims its bytes; the definition stays because removing it changes
// clearMarkers0045C8A0()'s inlining.
Rva0045C9E0CameraMarker::~Rva0045C9E0CameraMarker()
{
}

class View
{
public:
	void clearMarkers0045C8A0();
	Rva0045C9E0CameraMarker *findMarker0045C9E0(const AsciiString &name) const;
	void removeMarker0045CA80(Rva0045C9E0CameraMarker *marker);

private:
	char m_unknown[0x80];  // laid out in ViewConstructorBfme.cpp
	Rva0045C9E0CameraMarker *m_markers;
};

void View::clearMarkers0045C8A0()
{
	while (m_markers)
	{
		Rva0045C9E0CameraMarker *marker = m_markers;
		m_markers = marker->m_next;
		delete marker;
	}
}

Rva0045C9E0CameraMarker *View::findMarker0045C9E0(
	const AsciiString &name) const
{
	Rva0045C9E0CameraMarker *marker = m_markers;
	while (marker)
	{
		if (marker->m_name == name)
			return marker;
		marker = marker->m_next;
	}
	return 0;
}

void View::removeMarker0045CA80(Rva0045C9E0CameraMarker *marker)
{
	Rva0045C9E0CameraMarker **link = &m_markers;
	while (*link)
	{
		if ((*link)->m_name == marker->m_name)
		{
			Rva0045C9E0CameraMarker *removed = *link;
			*link = removed->m_next;
			delete removed;
			return;
		}
		link = &(*link)->m_next;
	}
}
