// cl: /DNDEBUG /DWIN32 /MD
//
// BFME's ScriptActions::doMoveCameraTo calls this lookup when resolving its
// named camera marker.  The one caller supplies an AsciiString and the body
// walks the marker list at +0x80, comparing each node's name case-sensitively.
//
// CameraMarkerList and CameraMarker are descriptive, not recovered EA names --
// what is proven is the role.  The matched caller is
// ?doMoveCameraTo@ScriptActions@@IAEXABVAsciiString@@MMMM@Z at 0x002F24F0, and
// this is not the waypoint lookup it uses upstream: BFME still has
// ?getWaypointByName@TerrainLogic@@UAEPAVWaypoint@@VAsciiString@@@Z, matched at
// 0x001AA900, so the camera resolves its target through a second, separate
// named list that lives on the client side.

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

struct CameraMarker
{
	~CameraMarker();

	CameraMarker *m_next;
	AsciiString m_name;
};

// ??1CameraMarker@@QAE@XZ present-unmatched -- the node destructor is real (its
// ILT is pinned at 0x00028984 and clear() calls it), but no row here claims its
// bytes; the definition stays because removing it changes clear()'s inlining.
CameraMarker::~CameraMarker()
{
}

class CameraMarkerList
{
public:
	void clear();
	CameraMarker *find(const AsciiString &name) const;

private:
	char m_unknown[0x80];
	CameraMarker *m_markers;
};

void CameraMarkerList::clear()
{
	while (m_markers)
	{
		CameraMarker *marker = m_markers;
		m_markers = marker->m_next;
		delete marker;
	}
}

CameraMarker *CameraMarkerList::find(
	const AsciiString &name) const
{
	CameraMarker *marker = m_markers;
	while (marker)
	{
		if (marker->m_name == name)
			return marker;
		marker = marker->m_next;
	}
	return 0;
}
