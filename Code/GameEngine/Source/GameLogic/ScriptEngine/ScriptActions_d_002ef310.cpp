// Open-BFME: recovered wrapper at retail 0x002EF310 (44 bytes).

typedef char Byte;

class BfmeAudioManager002EF310
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
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28();
	virtual void slot29(int first, int second, int firstDisabled, int secondDisabled);
};

extern BfmeAudioManager002EF310 * volatile TheAudioClientUpdate;

// ?func002EF310@@YGXDD@Z
void __stdcall func002EF310(Byte first, Byte second)
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
	TheAudioClientUpdate->slot29(0, 1, firstDisabled, secondDisabled);
}
