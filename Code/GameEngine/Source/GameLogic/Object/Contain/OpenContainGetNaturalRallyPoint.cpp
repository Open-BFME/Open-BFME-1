// cl: /DNDEBUG /MD /EHsc
// Open-BFME: OpenContain::getNaturalRallyPoint, retail 0x002227E0.
// ZH twin: OpenContain.cpp getNaturalRallyPoint. ExitInterface this at
// module+0x30: moduleData at [this-0x2C], object at [this-0x28].
// numberOfExitPaths at moduleData+0x144. Unused offset arg is ret-8.

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

class Object
{
public:
	Bool getSingleLogicalBonePosition(const char *boneName, Coord3D *position, Matrix3D *transform) const;
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const char *)this + 0x38);
	}
};

class OpenContainModuleData
{
public:
	unsigned char m_pad[0x144];
	Int m_numberOfExitPaths;
};

template <typename T> struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void concat(const T *text, int length);

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	const char *str(void) const { return m_data ? m_data->m_text : ""; }
	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}
};

class OpenContain
{
public:
	virtual Bool getNaturalRallyPoint(Coord3D &rallyPoint, Bool offset) const;

private:
	const OpenContainModuleData *moduleData() const
	{
		return *reinterpret_cast<const OpenContainModuleData *const *>(
			reinterpret_cast<const char *>(this) - 0x2C);
	}

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x28);
	}
};

// ?getNaturalRallyPoint@OpenContain@@UBE_NAAUCoord3D@@_N@Z
Bool OpenContain::getNaturalRallyPoint(Coord3D &rallyPoint, Bool offset) const
{
	Int numberExits = moduleData()->m_numberOfExitPaths;
	if (numberExits > 0)
	{
		AsciiString endBone("ExitEnd");
		if (numberExits > 1)
			endBone.concat("01", 2);
		getObject()->getSingleLogicalBonePosition(endBone.str(), &rallyPoint, 0);
	}
	else
	{
		rallyPoint = *getObject()->getPosition();
	}
	return true;
}
