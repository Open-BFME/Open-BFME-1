// cl: /DNDEBUG /MD /EHsc

class SkirmishScreenState
{
public:
	void refreshAllPlayerControls(void);
	void refreshPlayerTypeCombo00527220(int index);
	void refreshPlayerFactionControl(int index, bool preserveSelection);
	void refreshPlayerTeamControl(int index);

private:
	unsigned char m_unmodelled[0x16];
	bool m_refreshingControls;
};

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
			refreshPlayerFactionControl(index, false);
			refreshPlayerTeamControl(index);
		}
		m_refreshingControls = false;
	}
}
