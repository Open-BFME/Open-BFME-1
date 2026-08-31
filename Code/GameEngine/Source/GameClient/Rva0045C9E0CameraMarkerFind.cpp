// cl: /DNDEBUG /DWIN32 /MD
//
// BFME's ScriptActions::doMoveCameraTo calls this lookup when resolving its
// named camera marker.  The one caller supplies an AsciiString and the body
// walks the marker list at +0x80, comparing each node's name case-sensitively.

typedef int Int;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

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

Rva0045C9E0CameraMarker::~Rva0045C9E0CameraMarker()
{
}

class Rva0045C9E0CameraMarkerList
{
public:
	void clear();
	Rva0045C9E0CameraMarker *find(const AsciiString &name) const;

private:
	char m_unknown[0x80];
	Rva0045C9E0CameraMarker *m_markers;
};

void Rva0045C9E0CameraMarkerList::clear()
{
	while (m_markers)
	{
		Rva0045C9E0CameraMarker *marker = m_markers;
		m_markers = marker->m_next;
		delete marker;
	}
}

Rva0045C9E0CameraMarker *Rva0045C9E0CameraMarkerList::find(
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
