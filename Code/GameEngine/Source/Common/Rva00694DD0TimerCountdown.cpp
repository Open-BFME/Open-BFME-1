// Open-BFME5: clean C++ conversion of the countdown-triggered timer stop.

extern "C" __declspec(dllimport) void __stdcall AIL_stop_timer(int timer);

class Rva00694DD0Timer
{
public:
	void tickStopCountdown();

private:
	char m_pad00[0xB4C];
	int m_timer;
	int m_stopCountdown;
};

void Rva00694DD0Timer::tickStopCountdown()
{
	--m_stopCountdown;
	if (m_stopCountdown <= 0 && m_timer != -1)
		AIL_stop_timer(m_timer);
}
