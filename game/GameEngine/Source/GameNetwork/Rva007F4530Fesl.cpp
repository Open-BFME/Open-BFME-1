// cl: /GS
// EA FESL game-browser endpoint callback.
// Full161B ends0x007F45D1 CC afterret4; /GS reproducesretailcookie.
//
// The 0x007F4530 body is the callback immediately before the recovered
// address-remapping parser at 0x007F45E0.  Its matched sibling constructor
// 0x007F4130 supplies the endpoint record layout; the callback's receiver
// vtable fetches the endpoint record, forwards both endpoint strings/ports to
// the record channel, callsservicevirtualslot2 with4/0, then invokes setAddressRemapping
// on the same receiver.  The original SDK method spelling is not present, so
// the method name remains address-derived.

class Rva007E8810Message
{
public:
	bool hasError();
};

class Rva007F4130Endpoints
{
public:
	Rva007F4130Endpoints(Rva007E8810Message *msg);

	Rva007E8810Message *m_msg;
	char m_theaterIp[0x40];
	char m_messengerIp[0x40];
	char m_addressRemapping[0x400];
	int m_theaterPort;
	int m_messengerPort;
};

class Rva007F4530Channel
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void sendTheater(char *address, int port);
	virtual void sendMessenger(char *address, int port);
};

struct Rva007F4530Record
{
	char m_pad00[0x0c];
	Rva007F4530Channel *m_channel;
};

class Rva007F4530Factory
{
public:
	virtual Rva007F4530Record *getRecord();
};

class Rva007F4530Service
{
public:
	virtual void v0();
	virtual void v1();
	virtual void slot08(int kind, int flags);

	char m_pad00[0x6a4];
	void *m_service;
};

class Rva007F45E0Aries
{
public:
	virtual void v0();
	virtual Rva007F4530Service *slot04();

	void setAddressRemapping(const char *source);
	void rva007F4530(Rva007E8810Message *msg);

private:
	Rva007F4530Factory m_factory;
	char m_pad08[0x08];
};

void Rva007F45E0Aries::rva007F4530(Rva007E8810Message *msg)
{
	if (msg->hasError())
		return;

	Rva007F4130Endpoints endpoints(msg);
	Rva007F4530Record *record = m_factory.getRecord();
	Rva007F4530Channel *channel = record->m_channel;
	channel->sendTheater(endpoints.m_theaterIp, endpoints.m_theaterPort);
	channel->sendMessenger(endpoints.m_messengerIp,
		endpoints.m_messengerPort);

	Rva007F4530Service *service = slot04();
	((Rva007F4530Service *)service->m_service)->slot08(4, 0);
	setAddressRemapping(endpoints.m_addressRemapping);
}
