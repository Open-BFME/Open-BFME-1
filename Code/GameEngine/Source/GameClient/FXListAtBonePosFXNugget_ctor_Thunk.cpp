// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the BFME FX-at-bone-position nugget constructor.

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();
	void clear();

private:
	char *m_text;
};

class FXList;

class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class FXListAtBonePosFXNugget : public FXNugget
{
public:
	FXListAtBonePosFXNugget();
	virtual ~FXListAtBonePosFXNugget();

private:
	const FXList *m_fx;
	AsciiString m_boneName;
};

FXListAtBonePosFXNugget::FXListAtBonePosFXNugget()
{
	m_fx = 0;
	m_boneName.clear();
	m_nuggetType = 10;
}
