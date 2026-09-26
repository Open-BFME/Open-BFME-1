// cl: /DNDEBUG /MD /EHsc
// BFME's NetPacket::isAckRepeat dispatcher.  The three repeat helpers are
// already matched ILT-backed members; this TU owns the dispatcher body.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();

	Int getNetCommandType(void) { return m_commandType; }

	UnsignedInt m_timestamp;
	UnsignedInt m_executionFrame;
	UnsignedInt m_playerID;
	UnsignedShort m_id;
	Int m_commandType;
	Int m_referenceCount;
};

class NetCommandRef
{
public:
	NetCommandMsg *getCommand(void) { return m_msg; }

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

extern void j_00046e89(void);
extern void j_00004935(void);
extern void j_0001bbd5(void);

class NetPacket
{
	class AckRepeatReceiver
	{
	public:
		bool isAckBothRepeat(NetCommandRef *msg);
		bool isAckStage1Repeat(NetCommandRef *msg);
		bool isAckStage2Repeat(NetCommandRef *msg);
	};

	union AckRepeatCall
	{
		void (*free_function)(void);
		bool (AckRepeatReceiver::*member_function)(NetCommandRef *msg);
	};

protected:
	bool isAckRepeat(NetCommandRef *msg);

	unsigned char m_pad000[0x1F0];
	NetCommandRef *m_lastCommand;
};

// ?isAckRepeat@NetPacket@@IAE_NPAVNetCommandRef@@@Z
bool NetPacket::isAckRepeat(NetCommandRef *msg)
{
	if (m_lastCommand == 0)
	{
		return false;
	}
	if (m_lastCommand->getCommand()->getNetCommandType() != msg->getCommand()->getNetCommandType())
	{
		return false;
	}
	if (msg->getCommand()->getNetCommandType() == 0)
	{
		AckRepeatCall call;
		call.free_function = &j_00046e89;
		return (((AckRepeatReceiver *)this)->*call.member_function)(msg);
	}
	if (msg->getCommand()->getNetCommandType() == 1)
	{
		AckRepeatCall call;
		call.free_function = &j_00004935;
		return (((AckRepeatReceiver *)this)->*call.member_function)(msg);
	}
	if (msg->getCommand()->getNetCommandType() == 2)
	{
		AckRepeatCall call;
		call.free_function = &j_0001bbd5;
		return (((AckRepeatReceiver *)this)->*call.member_function)(msg);
	}
	return false;
}
