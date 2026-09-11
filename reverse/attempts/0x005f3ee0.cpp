// ??0Gen005F3EE0@@QAE@XZ
// partial score=0.98 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc



// The static reached by s4Second is a one-byte guard object.  Its constructor
// owns the four particle scratch buffers published in the adjacent retail
// globals; this TU keeps the buffer template local so the BFME offsets do not
// leak into the shared headers.

class Vector3
{
public:
	float x;
	float y;
	float z;
};

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
};

class RefCountClass
{
public:
	RefCountClass() : m_numRefs(1) {}
	virtual void Delete_This(void);

protected:
	virtual ~RefCountClass() {}

private:
	int m_numRefs;
};

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *name, int alignment = 0);
	ShareBufferClass(const ShareBufferClass &that);
	~ShareBufferClass();

protected:
	T *m_rawBuffer;
	T *m_array;
	int m_count;
	int m_alignment;
};

template <class T>
ShareBufferClass<T>::ShareBufferClass(int count, const char *, int alignment)
	: m_count(count), m_alignment(alignment)
{
	if (m_alignment == 0)
	{
		m_rawBuffer = new T[m_count];
		m_array = m_rawBuffer;
	}
	else
	{
		m_rawBuffer = (T *)new char[m_count * sizeof(T) + m_alignment];
		m_array = (T *)(((unsigned int)m_rawBuffer + m_alignment - 1) &
			~(unsigned int)(m_alignment - 1));
	}
}

template <class T>
ShareBufferClass<T>::ShareBufferClass(const ShareBufferClass &that)
	: m_count(that.m_count), m_alignment(that.m_alignment)
{
}

template <>
ShareBufferClass<Vector3>::ShareBufferClass(int count, const char *name,
	int alignment);

template <>
ShareBufferClass<Vector4>::ShareBufferClass(int count, const char *name,
	int alignment);

struct GlobalData
{
	unsigned char m_beforeHalfHeightMap[0xDCD];
	unsigned char m_useHalfHeightMap;
};

#define TheWritableGlobalData (*(GlobalData **)0x012ED5C8)

typedef ShareBufferClass<Vector3> *Vector3Buffer;
typedef ShareBufferClass<Vector4> *Vector4Buffer;
typedef ShareBufferClass<float> *FloatBuffer;
typedef ShareBufferClass<unsigned char> *ByteBuffer;

#define g_vector3Buffer (*(Vector3Buffer *)0x012F6DC8)
#define g_vector4Buffer (*(Vector4Buffer *)0x012F6DCC)
#define g_floatBuffer (*(FloatBuffer *)0x012F6DD0)
#define g_byteBuffer (*(ByteBuffer *)0x012F6DD4)

inline void *operator new(unsigned int, void *place)
{
	return place;
}

class Gen005F3EE0
{
public:
	Gen005F3EE0();
	~Gen005F3EE0();
};

// ??0Gen005F3EE0@@QAE@XZ
Gen005F3EE0::Gen005F3EE0()
{
	int count = 0x200;
	if (TheWritableGlobalData->m_useHalfHeightMap != 0)
		count = 0x400;

	g_vector3Buffer =
		new ShareBufferClass<Vector3>(count, (const char *)0x0111362C, 0);

	g_vector4Buffer =
		new ShareBufferClass<Vector4>(count, (const char *)0x011135E8, 0);

	g_floatBuffer =
		new ShareBufferClass<float>(count, (const char *)0);

	g_byteBuffer =
		new ShareBufferClass<unsigned char>(count, (const char *)0);
}
