// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc-
// stlport
// ScriptEngine::adjustToppleDirection(Object *, Coord3D *), retail 0x0034DC50,
// 198 bytes.

#define _STLP_NO_EXCEPTIONS 1
typedef int Int;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void normalize(void) throw();
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
	void releaseBuffer();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	Bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_len == 0;
	}

	Int compare(const AsciiString &right) const throw();

private:
	BfmeAsciiStringData *m_data;
};

#pragma comment(linker, "/alternatename:?compare@AsciiString@@QBEHABV1@@Z=?j_000220c5@@YAXXZ")

class Object
{
public:
	const AsciiString &getName(void) const
	{
		return m_name;
	}

	char m_pad000[0x38];
	Coord3D m_position;
	char m_pad044[0x40];
	AsciiString m_name;
};

struct ToppleDirectionNode
{
	ToppleDirectionNode *next;
	ToppleDirectionNode *previous;
	AsciiString objectName;
	Coord3D direction;
};

class ScriptEngine
{
public:
	virtual void adjustToppleDirection(Object *object, Coord3D *direction);

private:
	char m_slice_pad[0x175F0];
	ToppleDirectionNode *m_toppleDirections;
};

// ?adjustToppleDirection@ScriptEngine@@UAEXPAVObject@@PAUCoord3D@@@Z
void ScriptEngine::adjustToppleDirection(Object *object, Coord3D *direction)
{
	ScriptEngine *engine = this;
	AsciiString objectName = object->getName();
	if (objectName.isEmpty() || !direction) {
		return;
	}

	ToppleDirectionNode *head = engine->m_toppleDirections;
	ToppleDirectionNode *it = head->next;
	while (it != head) {
		if (it->objectName.compare(objectName) == 0) {
			*direction = it->direction;
			direction->x -= object->m_position.x;
			direction->y -= object->m_position.y;
			direction->z -= object->m_position.z;
			direction->normalize();
			return;
		}
		it = it->next;
	}
}
