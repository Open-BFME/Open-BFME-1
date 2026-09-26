// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// BFME's two public input gates both dispatch here, passing the address of the
// gate they own.  The method occupies InGameUI vtable slot 72 (+0x120).
class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void setSelecting(bool selecting); // slot 42, +0xa8
	virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48();
	virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60();
	virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66();
	virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70();
	virtual void setRadiusCursorNone(); // slot 71, +0x11c
	virtual void setInputEnabled(bool enabled, bool *gate); // slot 72, +0x120

private:
	char m_pad04[9];
	bool m_engineInputEnabled; // +0x0d
	bool m_scriptInputEnabled; // +0x0e
	char m_pad0f[0x12b0 - 0x0f];
	bool m_modes[12];
};

void InGameUI::setInputEnabled(bool enabled, bool *gate)
{
	bool wasEnabled = m_engineInputEnabled && m_scriptInputEnabled;
	*gate = enabled;

	if (wasEnabled && (!m_engineInputEnabled || !m_scriptInputEnabled))
	{
		setSelecting(false);
		setRadiusCursorNone();
		m_modes[1] = false;
		m_modes[2] = false;
		m_modes[0] = false;
		m_modes[3] = false;
		m_modes[4] = false;
		m_modes[5] = false;
		m_modes[6] = false;
		m_modes[7] = false;
		m_modes[8] = false;
		m_modes[9] = false;
		m_modes[10] = false;
		m_modes[11] = false;
	}
}
