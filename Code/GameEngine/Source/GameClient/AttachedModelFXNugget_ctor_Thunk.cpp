// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of the BFME AttachedModel FX constructor.

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();

private:
	char *m_text;
};

class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

private:
	unsigned char m_bfmeBaseData[0xB0];
};

class AttachedModelFXNugget : public FXNugget
{
public:
	AttachedModelFXNugget();
	virtual ~AttachedModelFXNugget();

private:
	AsciiString m_modelName;
	bool m_randomlyRotate;
	unsigned char m_padding[3];
	int m_expireTimer;
};

AttachedModelFXNugget::AttachedModelFXNugget() :
	m_randomlyRotate(false),
	m_expireTimer(0x28)
{
}
