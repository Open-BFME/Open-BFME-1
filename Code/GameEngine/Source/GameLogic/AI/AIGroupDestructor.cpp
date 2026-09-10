// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::~AIGroup, retail 0x00151D10, 246 bytes.
//
// The deleting-destructor thunk at 0x00152690 calls this body. The AIGroup
// vtable and the AI::createGroup caller identify the class. The body walks the
// member list, releases the ground path, then destroys the BFME ID vector.

#include <list>
#include <vector>

typedef unsigned int UnsignedInt;

class BfmeBaseVUQ
{
public:
    virtual ~BfmeBaseVUQ() {}
};

class Object
{
public:
	void leaveGroup();
};

class __declspec(novtable) Path
{
    friend class AIGroup;

protected:
    virtual ~Path();
};

class BFMEDeletablePath : public Path
{
public:
    void destroy() { Path::~Path(); }
};

void __cdecl operator delete(void *block);

class AIGroup : public BfmeBaseVUQ
{
public:
	virtual ~AIGroup();
	friend class PathDeleteArgument;

private:
	_STL::list<Object *> m_memberList;
	UnsignedInt m_memberListSize;
	float m_speed;
	bool m_dirty;
    UnsignedInt m_id;
    volatile Path *m_groundPath;
    volatile void *m_pathState1C;
    volatile void *m_pathState20;
    volatile void *m_pathState24;
    volatile float m_pathState28;
    volatile void *m_pathState2C;
    volatile void *m_pathState30;
	_STL::vector<UnsignedInt> m_lastRequestedIDList;
};

class PathDeleteArgument
{
public:
	PathDeleteArgument(Path *path, AIGroup *group) : m_path(path), m_group(group) { }
	operator void *(void) const { return m_path; }
	~PathDeleteArgument()
	{
		m_group->m_groundPath = 0;
		m_group->m_pathState1C = 0;
		m_group->m_pathState20 = 0;
		m_group->m_pathState24 = 0;
	}

private:
	Path *m_path;
	AIGroup *m_group;
};

// ??1AIGroup@@UAE@XZ
AIGroup::~AIGroup()
{
    register AIGroup *self = this;
    register UnsignedInt zero = self->m_memberListSize - self->m_memberListSize;
    register Path *groundPath;
    std::list<Object *>::iterator i;
    for (i = self->m_memberList.begin(); i != self->m_memberList.end();)
    {
        Object *member = *i;
        if (member != (Object *)zero)
        {
            member->leaveGroup();
            i = self->m_memberList.begin();
        }
        else
        {
            i = self->m_memberList.erase(i);
        }
    }

    groundPath = (Path *)self->m_groundPath;
    if (groundPath != (Path *)zero)
    {
        ((BFMEDeletablePath *)groundPath)->destroy();
        operator delete(PathDeleteArgument(groundPath, self));
        self->m_pathState28 = 10.0f;
        self->m_pathState2C = (void *)zero;
        self->m_pathState30 = (void *)zero;
    }
}
