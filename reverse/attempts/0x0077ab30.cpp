// ?stopClientParticleSystems@W3DModelDraw@@IAEXXZ
// partial score=0.70 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME retail vector element is 0x20 bytes: a retained object pointer, an
// STLport string, three words and a final word.  The loop copies the record
// inline, sends its object to the client manager, releases that temporary
// reference, then lets the temporary string destruct before clearing the
// original vector.

#include <string>
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class RenderObjClass
{
public:
	virtual void Delete_This();
	int m_references;
};

class SceneClass
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void Remove_Render_Object(RenderObjClass *object);
};

struct Rva0077AB30Record
{
	Rva0077AB30Record(const Rva0077AB30Record &other) :
		m_object(other.m_object), m_name(other.m_name), m_last(other.m_last)
	{
		m_tail[0] = other.m_tail[0];
		m_tail[1] = other.m_tail[1];
		m_tail[2] = other.m_tail[2];
		_ReadWriteBarrier();
	}

	RenderObjClass *m_object;
	_STL::basic_string<char> m_name;
	int m_tail[3];
	int m_last;
};

class W3DModelDraw
{
protected:
	void stopClientParticleSystems();

private:
	char m_beforeSystems[0x130];
	_STL::vector<Rva0077AB30Record> m_systems;
};

#define TheRva0077AB30Scene (*(SceneClass **)0x012F8058)

void W3DModelDraw::stopClientParticleSystems()
{
	for (_STL::vector<Rva0077AB30Record>::iterator it = m_systems.begin();
		it != m_systems.end(); ++it)
	{
		Rva0077AB30Record record = *it;
		TheRva0077AB30Scene->Remove_Render_Object(record.m_object);
		if (--record.m_object->m_references == 0)
			record.m_object->Delete_This();
	}
	m_systems.clear();
}

#undef TheRva0077AB30Scene
