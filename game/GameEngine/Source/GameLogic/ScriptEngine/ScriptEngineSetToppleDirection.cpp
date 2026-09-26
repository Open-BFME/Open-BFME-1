// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// ScriptEngine::setToppleDirection, retail 0x0034EA70, 451 bytes.
//
// The action-template table assigns action 230 to NAMED_SET_TOPPLE_DIRECTION.
// ScriptActions::doSetToppleDirection passes the named unit and an optional
// Coord3D to TheScriptEngine, whose global is also loaded by the direct caller
// at 0x002EFF20.  Retail stores the pairs in the list immediately before the
// named-reveal vector: the list object is at this+0x175F4 and its 0x18-byte
// nodes contain two links followed by {AsciiString, Coord3D}.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);

struct Coord3D
{
	Coord3D(void) {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	Real x;
	Real y;
	Real z;
};

struct BfmeAsciiStringData
{
	Int m_refCount;
	UnsignedShort m_len;
	UnsignedShort m_numCharsAllocated;
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
	void set(const StringBase &);
	void releaseBuffer();
};

// This is the one-pointer narrow StringBase view used by the neighboring
// ScriptEngine list/vector bodies.  The copy, assignment, and release calls
// resolve to the existing retail StringBase<char> bodies; no new helper pin is
// introduced here.
class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}

	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	Bool isEmpty(void) const { return m_data == 0 || m_data->m_len == 0; }
	const char *str(void) const
	{
		return m_data ? (const char *)(m_data + 1) : "";
	}

	Int compare(const AsciiString &other) const
	{
		Int otherLength = other.getLength();
		const char *otherText = other.str();
		Int thisLength = getLength();
		const char *thisText = str();
		Int shorter = thisLength < otherLength ? thisLength : otherLength;
		Int difference = memcmp(thisText, otherText, shorter);
		if (difference != 0)
			return difference;
		return thisLength - otherLength;
	}

	Bool operator==(const AsciiString &right) const
	{
		return compare(right) == 0;
	}

private:
	BfmeAsciiStringData *m_data;
};

typedef std::pair<AsciiString, Coord3D> AsciiStringCoord3DPair;
typedef std::list<AsciiStringCoord3DPair> ListAsciiStringCoord3D;
typedef ListAsciiStringCoord3D::iterator ListAsciiStringCoord3DIt;

class ScriptEngine
{
public:
	void setToppleDirection(const AsciiString &objectName,
		const Coord3D *direction);

private:
	char m_slice_pad[0x175F4];
	ListAsciiStringCoord3D m_toppleDirections;
};

// ?setToppleDirection@ScriptEngine@@QAEXABVAsciiString@@PBUCoord3D@@@Z
void ScriptEngine::setToppleDirection(const AsciiString &objectName,
	const Coord3D *direction)
{
	if (objectName.isEmpty()) {
		return;
	}

	ListAsciiStringCoord3DIt it;
	for (it = m_toppleDirections.begin(); it != m_toppleDirections.end(); ++it) {
		if (it->first == objectName) {
			if (direction) {
				it->second = *direction;
			} else {
				m_toppleDirections.erase(it);
			}
			return;
		}
	}

	AsciiStringCoord3DPair newPair;
	newPair.first = objectName;
	newPair.second = *direction;
	m_toppleDirections.push_front(newPair);
}
