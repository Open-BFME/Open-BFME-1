extern "C" void *bfmeVftGS[];

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadGS[0x3c];
	int m_bfmeFrameGS;
};

class ScriptEngine
{
public:
	unsigned char m_bfmeHeadGS[0x17620];
	int m_bfmeValueGS;
};

class BfmeAiDataGS
{
public:
	unsigned char m_bfmeHeadGS[8];
	float m_bfmeRateGS;
};

class AI
{
public:
	unsigned char m_bfmeHeadGS[0x14];
	BfmeAiDataGS *m_bfmeDataGS;
};

extern Rva00367E30Logic *TheBfmeGameLogic;
extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class BfmeArgGS
{
public:
	unsigned char m_bfmeHeadGS[0x294];
	char m_bfmeFlagGS;
};

class BfmeStateGS
{
public:
	BfmeStateGS(BfmeArgGS *a);

	void *volatile m_bfmeVftGS;
	int m_bfme04GS;
	int m_bfme08GS;
	BfmeArgGS *m_bfme0cGS;
	char m_bfme10GS;
	char m_bfme11GS;
	unsigned char m_bfmePad0GS[2];
	int m_bfme14GS;
	int m_bfme18GS;
	volatile int m_bfme1cGS;
	int m_bfme20GS;
	int m_bfme24GS;
	int m_bfme28GS;
	int m_bfme2cGS;
	int m_bfme30GS;
	int m_bfme34GS;
	int m_bfme38GS;
	int m_bfme3cGS;
	char m_bfme40GS;
	unsigned char m_bfmePad1GS[3];
	float m_bfme44GS;
	int m_bfme48GS;
	int m_bfme4cGS;
	int m_bfme50GS;
	int m_bfme54GS;
	int m_bfme58GS;
	int m_bfme5cGS;
	int m_bfme60GS;
	char m_bfme64GS;
	char m_bfme65GS;
	unsigned char m_bfmePad2GS[2];
	int m_bfme68GS;
	int m_bfme6cGS;
	int m_bfme70GS;
	int m_bfme74GS;
};

BfmeStateGS::BfmeStateGS(BfmeArgGS *a)
{
	m_bfmeVftGS = bfmeVftGS;
	m_bfme04GS = 0;
	m_bfme08GS = 0;
	m_bfme0cGS = a;
	m_bfme10GS = 0;
	m_bfme11GS = 0;
	m_bfme20GS = 0;
	m_bfme24GS = 0;
	m_bfme50GS = 0;
	m_bfme60GS = 0;
	m_bfme64GS = 0;
	m_bfme65GS = 0;
	m_bfme68GS = 0;
	m_bfme6cGS = 0;
	m_bfme70GS = 0;
	m_bfme74GS = 0;
	m_bfme1cGS = 0xa;
	m_bfme30GS = -1;
	m_bfme44GS = 10.0f;
	m_bfme14GS = 2;
	m_bfme18GS = 2;
	m_bfme28GS = TheBfmeGameLogic->m_bfmeFrameGS;
	a->m_bfmeFlagGS = 0;
	m_bfme48GS = 0;
	m_bfme4cGS = 0;
	m_bfme54GS = 0;
	m_bfme58GS = 0;
	m_bfme5cGS = 0;
	m_bfme34GS = 0;
	m_bfme38GS = 0;
	m_bfme3cGS = 0;
	m_bfme40GS = 0;
	m_bfme2cGS = TheScriptEngine->m_bfmeValueGS;
	m_bfme1cGS = (int)TheAI->m_bfmeDataGS->m_bfmeRateGS;
}
