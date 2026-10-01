// Open-BFME: recovered wrapper at retail 0x002EF2A0 (47 bytes).

typedef unsigned char Byte;

class BfmeAudioManager002EF2A0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual void slot26(int first, int second, int firstDisabled, int secondDisabled);
};

// Retail's AudioManager singleton (0x012ED668); the TU-local view above only
// names the slot this body calls.
class AudioManager;

extern AudioManager *TheAudio;

static inline BfmeAudioManager002EF2A0 *localAudioManagerView()
{
	return (BfmeAudioManager002EF2A0 *)TheAudio;
}

// ?func002EF2A0@@YGXEEH@Z
void __stdcall func002EF2A0(Byte first, Byte second, int value)
{
	int firstDisabled;
	int secondDisabled;
	if (first == 0)
		firstDisabled = 1;
	else
		firstDisabled = 0;
	if (second == 0)
		secondDisabled = 1;
	else
		secondDisabled = 0;
	localAudioManagerView()->slot26(0, value, firstDisabled, secondDisabled);
}
