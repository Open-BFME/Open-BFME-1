// cl: /DNDEBUG /MD /EHsc

// 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined in
// GameLogic/LivingWorld/LivingWorldLogic.cpp; the spelled-out name is the one
// that exists, so it is the one this reference carries (precedent:
// Bfme/Rva000F9940.cpp, Audio/AudioEventRTSClassification.cpp).  Only the
// forward declaration is repeated -- the view below is cast to at the use, so
// no layout is needed or claimed.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Glo012F1028Type
{
public:
	void j_00008c0b(void);
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
		((Glo012F1028Type *)TheLivingWorldLogic)->j_00008c0b();
	j_0002a969();
	j_00021f26();
	j_0002eeec();
}
