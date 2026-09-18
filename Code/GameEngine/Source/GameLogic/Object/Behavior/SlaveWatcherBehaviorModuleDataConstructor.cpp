// cl: /DNDEBUG /MD /EHsc

// Factory 0x00117540 passes callback VA 0x0042C115 -> 0x002072E0, which
// registers table RVA 0x00CA63CC: GrantUpgrade at +0x08 and RemoveUpgrade
// at +0x0c, both parsed by INI::parseAsciiString (0x00851EE0).
// This constructor view clears the four-byte string handles directly and
// naturally emits scalar wrapper 0x002074E0; the novtable complete destructor
// uses the canonical AsciiString definition in its separate ABI view.

class SlaveWatcherBehaviorModuleData
{
public:
	SlaveWatcherBehaviorModuleData();
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_grantUpgrade;
	unsigned int m_removeUpgrade;
};

// ??0SlaveWatcherBehaviorModuleData@@QAE@XZ
SlaveWatcherBehaviorModuleData::SlaveWatcherBehaviorModuleData()
{
	m_grantUpgrade = 0;
	m_removeUpgrade = 0;
}