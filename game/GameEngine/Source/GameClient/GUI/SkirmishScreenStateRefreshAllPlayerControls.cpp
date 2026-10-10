// cl: /DNDEBUG /MD /EHsc

class SkirmishScreenState
{
public:
	void refreshAllPlayerControls(void);
	void refreshPlayerTypeCombo00527220(int index);

private:
	unsigned char m_unmodelled[0x16];
	bool m_refreshingControls;
};

// ILT2EA91 -> matched rebuildTeamCombo005268F0(int, bool), RET8;
// ILT2D38A -> matched rva005294F0(int), RET4. Both return void and use ECX.
extern "C" void __identifier("?j_0002ea91@@YAXXZ")();
extern "C" void __identifier("?j_0002d38a@@YAXXZ")();

// Refresh each slot as one transaction so control callbacks cannot recursively
// rebuild the same screen state while their choices are being replaced.
// ?refreshAllPlayerControls@SkirmishScreenState@@QAEXXZ
void SkirmishScreenState::refreshAllPlayerControls(void)
{
	if (!m_refreshingControls)
	{
		m_refreshingControls = true;
		for (int index = 0; index < 8; ++index)
		{
			refreshPlayerTypeCombo00527220(index);
			union {
				void (*raw)();
				void (SkirmishScreenState::*member)(int, bool);
			} faction = { __identifier("?j_0002ea91@@YAXXZ") };
			(this->*faction.member)(index, false);
			union {
				void (*raw)();
				void (SkirmishScreenState::*member)(int);
			} team = { __identifier("?j_0002d38a@@YAXXZ") };
			(this->*team.member)(index);
		}
		m_refreshingControls = false;
	}
}
