// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIStateMachine::addToGoalPath, retail 0x00187FA0.
//
// The BFME class places its goal-path vector at 0x44.  The recovered headers
// currently describe an older layout, so keep that retail detail local while
// preserving the original source-level operation.
struct Coord3D
{
	float x;
	float y;
	float z;

	bool equals(const Coord3D &other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
};

// Retail folded the out-of-line twelve-byte push_back used here with this
// equivalent STL instantiation.
struct Gen_t_00156bf0_p12cd
{
	int value[3];
	Gen_t_00156bf0_p12cd();
	Gen_t_00156bf0_p12cd(const Gen_t_00156bf0_p12cd &);
	~Gen_t_00156bf0_p12cd();
	Gen_t_00156bf0_p12cd &operator=(const Gen_t_00156bf0_p12cd &);
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Other>
void _Construct(Type *destination, const Other &source);

template <class Type, class Allocator>
class vector
{
public:
	__forceinline unsigned int size() const
	{
		return (unsigned int)(m_finish - m_start);
	}

	__forceinline Type &operator[](unsigned int index)
	{
		return m_start[index];
	}

	__forceinline void appendAtEnd(const Type &value, const __false_type &tag)
	{
		if (m_finish != m_endOfStorage)
		{
			_Construct(m_finish, value);
			++m_finish;
		}
		else
		{
			_M_insert_overflow(m_finish, value, tag, 1, true);
		}
	}

	void push_back(const Type &value);

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};
}

class AIStateMachine
{
public:
	void addToGoalPath(const Coord3D *pathPoint);

private:
	char m_beforeGoalPath[0x44];
	_STL::vector<Coord3D, _STL::allocator<Coord3D> > m_goalPath;
};

void AIStateMachine::addToGoalPath(const Coord3D *pathPoint)
{
	if (m_goalPath.size() == 0)
	{
		// The STLport false-type tag is empty.  Retail reuses the incoming
		// argument's stack slot as its address rather than reserving storage.
		const _STL::__false_type &tag =
			*reinterpret_cast<const _STL::__false_type *>(&pathPoint);
		m_goalPath.appendAtEnd(*pathPoint, tag);
	}
	else
	{
		Coord3D *finalPoint = &m_goalPath[m_goalPath.size() - 1];
		if (!finalPoint->equals(*pathPoint))
		{
			typedef _STL::vector<Gen_t_00156bf0_p12cd,
				_STL::allocator<Gen_t_00156bf0_p12cd> > FoldedGoalPathVector;
			reinterpret_cast<FoldedGoalPathVector *>(&m_goalPath)->push_back(
				*reinterpret_cast<const Gen_t_00156bf0_p12cd *>(pathPoint));
		}
	}
}
