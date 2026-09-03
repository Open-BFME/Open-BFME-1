// cl: /DNDEBUG /MD /EHsc
// readable body of ?initTimeOutValues@GameLogic@@QAEXXZ: Code/GameEngine/Source/GameLogic/System/GameLogic.cpp
// Retail 0x00383740: GameLogic::initTimeOutValues. ZH GameLogic.cpp:1512.
// TheNetwork is 0x012F7714, getNumPlayers is vslot +0x94, the timeout array
// sits at +0x128 (same BFME layout as processProgressComplete). timeGetTime
// is the ILT at 0x000481E4, not the import.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36();
	virtual int getNumPlayers(void);
};

extern NetworkInterface *TheNetwork;

extern "C" unsigned long __stdcall bfme_timeGetTime(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void initTimeOutValues(void);

	char m_pad[0x128];
	unsigned int m_progressCompleteTimeout[8];
};

// ?initTimeOutValues@GameLogic@@QAEXXZ
void GameLogic::initTimeOutValues(void)
{
	if (!TheNetwork)
		return;
	int i = 0;
	if (TheNetwork->getNumPlayers() <= 0)
		return;
	unsigned int *p = m_progressCompleteTimeout;
	do
	{
		*p = bfme_timeGetTime();
		++i;
		++p;
	} while (i < TheNetwork->getNumPlayers());
}
