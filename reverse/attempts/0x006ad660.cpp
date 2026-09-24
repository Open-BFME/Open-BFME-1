// ?rva006AD660@Rva006AD590Owner@@QAEIPBVAudioEventRTS@@@Z
// partial score=0.37 date=2026-09-24
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &);
	~AudioEventRTS();
	void setPlayingHandle(unsigned int handle);

	char m_pad00[0x0c];
	unsigned int m_playingHandle; // +0x0c
	char m_pad10[0x18];
	int m_timeOfDay; // +0x28
	char m_pad2c[0x70 - 0x2c];
};

struct Rva006AACB0Element
{
	AudioEventRTS m_event;
	unsigned int m_zero;
	unsigned char m_flag;

	Rva006AACB0Element(const AudioEventRTS &event)
		: m_event(event), m_zero(0) { m_flag = 0; }
};

namespace _STL
{
struct __false_type {};
template <class Type> class allocator {};
template <class Type> void __cdecl BfmeElementConstruct(Type *, const Type &);

template <class Type, class Allocator>
class vector
{
public:
	void push_back(const Type &value)
	{
		if (_M_finish != _M_end_of_storage) {
			BfmeElementConstruct(_M_finish, value);
			++_M_finish;
		} else {
			_M_insert_overflow(_M_finish, value, __false_type(), 1, true);
		}
	}
	Type *end() const { return _M_finish; }

protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &,
		unsigned int, bool);
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

class Rva006AD590Owner
{
public:
	void bfmeAdjustPriorityAndVolume(AudioEventRTS *);
	unsigned int rva006AD660(const AudioEventRTS *);

private:
	char m_pad00[0x84];
	unsigned int m_nextHandle;
	char m_pad88[0x0c];
	_STL::vector<Rva006AACB0Element,
		_STL::allocator<Rva006AACB0Element> > m_queues[3];
};

unsigned int Rva006AD590Owner::rva006AD660(const AudioEventRTS *source)
{
	int category = source->m_timeOfDay;
	{
		Rva006AACB0Element entry(*source);
		m_queues[category].push_back(entry);
	}
	_STL::vector<Rva006AACB0Element,
		_STL::allocator<Rva006AACB0Element> > &queue = m_queues[category];
	AudioEventRTS *added = &((queue.end() - 1)->m_event);
	bfmeAdjustPriorityAndVolume(added);
	added->setPlayingHandle(m_nextHandle++);
	return added->m_playingHandle;
}
