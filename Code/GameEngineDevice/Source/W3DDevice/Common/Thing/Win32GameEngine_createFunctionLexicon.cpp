// Retail 0x006BA930.  The Win32 game-engine factory allocates the 0x38-byte
// W3DFunctionLexicon and calls its proven W3DFunctionLexicon constructor.

class FunctionLexicon
{
public:

	FunctionLexicon();
	virtual ~FunctionLexicon();

private:

	unsigned char m_retailData[0x34];
};

class W3DFunctionLexicon : public FunctionLexicon
{
public:

	W3DFunctionLexicon();
};

class Win32GameEngine
{
public:

	virtual FunctionLexicon *createFunctionLexicon();
};

FunctionLexicon *Win32GameEngine::createFunctionLexicon()
{
	return new W3DFunctionLexicon;
}
