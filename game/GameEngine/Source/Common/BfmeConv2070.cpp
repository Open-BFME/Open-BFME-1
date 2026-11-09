extern "C" void * __identifier("??_7AIPlayer@@6B@")[ ];
#define bfmeVftGS __identifier("??_7AIPlayer@@6B@")

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadGS[0x3c];
	int m_frame;
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
	float m_teamSeconds;
};

class AI
{
public:
	unsigned char m_bfmeHeadGS[0x14];
	BfmeAiDataGS *m_aiData;
};

// Retail's GameLogic singleton; only GameLogic.cpp defines it.
class GameLogic;
extern GameLogic *TheGameLogic;
extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

class Player
{
public:
	unsigned char m_bfmeHeadGS[0x294];
	char m_canBuildUnits;
};

class AIPlayer
{
public:
	AIPlayer(Player *a);

	void *volatile m_bfmeVftGS;
	int m_bfme04GS;
	int m_bfme08GS;
	Player *m_bfme0cGS;
	char m_readyToBuildTeam;
	char m_readyToBuildStructure;
	unsigned char m_bfmePad0GS[2];
	int m_teamTimer;
	int m_structureTimer;
	volatile int m_bfme1cGS;
	int m_bfme20GS;
	int m_bfme24GS;
	int m_frameLastBuildingBuilt;
	int m_difficulty;
	int m_skillsetSelector;
	int m_bfme34GS;
	int m_bfme38GS;
	int m_bfme3cGS;
	char m_baseCenterSet;
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

AIPlayer::AIPlayer(Player *a)
{
	m_bfmeVftGS = bfmeVftGS;
	m_bfme04GS = 0;
	m_bfme08GS = 0;
	m_bfme0cGS = a;
	m_readyToBuildTeam = 0;
	m_readyToBuildStructure = 0;
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
	m_skillsetSelector = -1;
	m_bfme44GS = 10.0f;
	m_teamTimer = 2;
	m_structureTimer = 2;
	m_frameLastBuildingBuilt = reinterpret_cast<Rva00367E30Logic *>(TheGameLogic)->m_frame;
	a->m_canBuildUnits = 0;
	m_bfme48GS = 0;
	m_bfme4cGS = 0;
	m_bfme54GS = 0;
	m_bfme58GS = 0;
	m_bfme5cGS = 0;
	m_bfme34GS = 0;
	m_bfme38GS = 0;
	m_bfme3cGS = 0;
	m_baseCenterSet = 0;
	m_difficulty = TheScriptEngine->m_bfmeValueGS;
	m_bfme1cGS = (int)TheAI->m_aiData->m_teamSeconds;
}
