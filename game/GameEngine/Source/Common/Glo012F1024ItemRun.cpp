// cl: /DNDEBUG /MD /EHsc

// 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined in
// GameLogic/LivingWorld/LivingWorldLogic.cpp; the spelled-out name is the one
// that exists, so it is the one this reference carries (precedent:
// Bfme/Rva000F9940.cpp, Audio/AudioEventRTSClassification.cpp).  Only the
// forward declaration is repeated -- the view below is cast to at the use, so
// no layout is needed or claimed.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// ILT 0x00008C0B jumps to the matched body 0x003C1230, which the ledger
// defines as Gen_003C1230::bfmeClear.
class Gen_003C1230
{
public:
	void bfmeClear(void);
};

class Glo012F1024Item
{
public:
	bool j_0000ca59(void);
	void j_0002a969(void);
	void j_00021f26(void);
	void j_0002eeec(void);
	void run(void);
};

void Glo012F1024Item::run(void)
{
	if (j_0000ca59())
		((Gen_003C1230 *)TheLivingWorldLogic)->bfmeClear();
	j_0002a969();
	j_00021f26();
	j_0002eeec();
}
