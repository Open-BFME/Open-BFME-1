// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class BFMEConnectionManager
{
public:
	bool hasLeaveRequestTimedOut(void);

private:
	char m_retailPrefix[0x12110];
	unsigned long m_leaveRequestTime;
};

// ?hasLeaveRequestTimedOut@BFMEConnectionManager@@QAE_NXZ
bool BFMEConnectionManager::hasLeaveRequestTimedOut(void)
{
	if (m_leaveRequestTime == 0)
		return false;

	return timeGetTime() - m_leaveRequestTime > 10000;
}
