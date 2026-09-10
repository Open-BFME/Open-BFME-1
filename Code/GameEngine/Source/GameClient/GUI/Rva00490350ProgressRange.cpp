// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the progress-range adapter at retail 0x004903D0.  Its identity
// comes from slot 1 of vtable 0x010F9AE4, installed by the already-matched
// Rva00490350Derived constructor/destructor at 0x004902C0/0x00490350.  Those
// siblings establish the previous-handler link at +0x04 and the range at
// +0x08/+0x0C; their endpoint callbacks are the same slot used below.

extern float g_01076C24;

class Rva00490350Base
{
public:
	virtual ~Rva00490350Base(void);
	virtual void updateProgress(int value);

protected:
	Rva00490350Base *m_previous;
};

class Rva00490350Derived : public Rva00490350Base
{
public:
	virtual ~Rva00490350Derived(void);
	virtual void updateProgress(int value);

private:
	int m_minimum;
	int m_maximum;
};

void Rva00490350Derived::updateProgress(int value)
{
	Rva00490350Base *target = m_previous;

	if (target)
	{
		int low = m_minimum;
		int span = m_maximum - low;
		float spanReal = (float)span;

		target->updateProgress(low +
			(int)(spanReal * ((float)value * g_01076C24)));
	}
}
