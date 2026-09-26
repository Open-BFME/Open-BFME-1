// cl: /O2 /Ob1

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Rva001E27A0
{
public:
	void run();

private:
	template <typename T>
	class Vector
	{
	public:
		T *begin() const { return m_begin; }
		unsigned size() const { return (unsigned)(m_end - m_begin); }

	private:
		T *m_begin;
		T *m_end;
	};

	unsigned char m_pad[8];
	Vector<int> m_values;
};

void Rva001E27A0::run()
{
	unsigned i = 0;
	unsigned count = m_values.size();
	if (count > 0)
	{
		count = m_values.size();
		do
		{
			_ReadWriteBarrier();
			++i;
		} while (i < count);
	}
}
