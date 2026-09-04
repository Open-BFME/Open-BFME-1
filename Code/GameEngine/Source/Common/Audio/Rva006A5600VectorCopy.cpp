// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006A5600: mutex-guarded eight-byte vector copy/reset.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

struct Rva006A5600Element
{
	unsigned int m_first;
	unsigned int m_second;
};

inline Rva006A5600Element *Rva006A5600Copy(
	Rva006A5600Element *destination,
	const Rva006A5600Element *first,
	const Rva006A5600Element *last)
{
	int count = last - first;
	if (count > 0)
	{
		do
		{
			*destination = *first;
			++first;
			++destination;
		}
		while (--count);
	}
	return destination;
}

class Rva006A5600Owner
{
public:
	void reset();

private:
	char m_pad636[0x636];
	unsigned char m_dirty;
	char m_pad638[0x95c - 0x638];
	void *m_mutex;
	char m_pad960[0xadc - 0x960];
	class Rva006A5600Vector
	{
	public:
		bool empty() const
		{
			return m_begin == m_end;
		}

		void clear()
		{
			m_end = Rva006A5600Copy(m_begin, m_end, m_end);
		}

		Rva006A5600Element *m_begin;
		Rva006A5600Element *m_end;
		Rva006A5600Element *m_capacity;
	} m_vector;
};

void Rva006A5600Owner::reset()
{
	void *mutex = m_mutex;
	unsigned char held = 0;
	if (WaitForSingleObject(mutex, 0xFFFFFFFFu) != 0x102u)
		held = 1;

	if (!m_vector.empty())
	{
		m_dirty = 1;
		m_vector.clear();
	}
	if (held)
		ReleaseMutex(mutex);
}
