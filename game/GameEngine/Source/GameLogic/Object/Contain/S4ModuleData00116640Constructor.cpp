// cl: /DNDEBUG /MD /EHsc
// Open-BFME: S4ModuleData00116640::S4ModuleData00116640, retail 0x0021D6E0,
// 25 bytes.
//
// A module data constructor of the plainest kind: run
// ContestableContainModuleData, put this class's own vftable down, and set the
// byte at +0x1A8 to 4.

class ContestableContainModuleData
{
public:
	ContestableContainModuleData();				// ILT 0x00031142

	virtual ~ContestableContainModuleData();

private:
	unsigned char m_unmodelled_004[0x1A8 - 0x04];
};

class S4ModuleData00116640 : public ContestableContainModuleData
{
public:
	S4ModuleData00116640();

	unsigned char m_kind;					// +0x1A8
};

S4ModuleData00116640::S4ModuleData00116640()
{
	m_kind = 4;
}
