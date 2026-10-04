// Open-BFME: the shared two-slot callback body at retail RVA 0x004C6000.

#include <exception>

class FunctorNotSet : public std::exception
{
public:
	FunctorNotSet() : std::exception() {}
};


class Gen004C6000Callback
{
public:
	virtual void slot0();
	virtual void apply();
};

class Gen004C6000CheckedCallback
{
public:
	operator Gen004C6000Callback *() const
	{
		return m_callback;
	}

	Gen004C6000Callback *operator->() const
	{
		if (m_callback == 0)
		{
			throw FunctorNotSet();
		}
		return m_callback;
	}

	Gen004C6000Callback *m_callback;
};

class Gen004C6000
{
public:
	void handle(int event);

	Gen004C6000Callback *m_first;
	Gen004C6000CheckedCallback m_second;
};

void Gen004C6000::handle(int event)
{
	if (event == 0)
	{
		Gen004C6000Callback *callback = m_first;
		if (callback)
			callback->apply();
		return;
	}
	if (event == 1)
	{
		if (m_second)
			m_second->apply();
	}
}
