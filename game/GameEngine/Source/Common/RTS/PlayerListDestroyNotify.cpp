// cl: /O2

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	void notify();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void dropA(void *obj);
	void dropB(void *obj);
};

class BfmeLinkRV
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void release();

	unsigned char m_pad[0x104 - 4];
	BfmeLinkRV *m_next;
};

class ClientFrameSubsystem
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1a();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual BfmeLinkRV *first();
};

// The 0x012F1464 global is EA's `GameClient *TheGameClient`, defined once in
// GameClient.cpp; only the pointee type may differ per TU, so it is forward
// declared here and this TU's list view is applied at the use.
class GameClient;
extern PartitionManager *TheShroudManager;
extern ControlBar *TheControlBar;
extern GameClient *TheGameClient;

void __cdecl bfmeFinishRV(int);

void __stdcall destroyNotify(void *obj)
{
	if (!obj)
		return;
	if (TheShroudManager)
		TheShroudManager->notify();
	TheControlBar->dropA(obj);
	TheControlBar->dropB(obj);
	BfmeLinkRV *n = ((ClientFrameSubsystem *)TheGameClient)->first();
	while (n)
	{
		n->release();
		n = n->m_next;
	}
	bfmeFinishRV(0);
}
