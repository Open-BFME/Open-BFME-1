// cl: /DNDEBUG /MD /EHsc
// Open-BFME: S4ModuleData00116D80::S4ModuleData00116D80, retail 0x0024F390,
// 28 bytes.
//
// The same shape as S4ModuleData00116640 three kilobytes earlier: run
// ContestableContainModuleData, put this class's own vftable down, and set the
// word at +0x1A8. Here it is a float, 0.5.

typedef float Real;

class ContestableContainModuleData
{
public:
	ContestableContainModuleData();				// ILT 0x00031142

	virtual ~ContestableContainModuleData();

private:
	unsigned char m_unmodelled_004[0x1A8 - 0x04];
};

class S4ModuleData00116D80 : public ContestableContainModuleData
{
public:
	S4ModuleData00116D80();

	Real m_fraction;					// +0x1A8
};

S4ModuleData00116D80::S4ModuleData00116D80()
{
	m_fraction = 0.5f;
}
