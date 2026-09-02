// cl: /DNDEBUG /MD /EHsc
// Retail 0x0051B720: destructor of the class whose ctor tail at 0x0051B690
// installs vtable 0x01105FCC. Resets that vfptr, clears a Display flag,
// restores shell audio, showShell(true), then the 0x00490470 base destructor.

class BfmeStrVM0
{
public:
	void bfmeFlagVM0(unsigned char);
};

class Rva0051D690Audio
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68();
	virtual void slot6c(int a, int b, int c);
};

class Shell
{
public:
	void showShell(bool);
};

extern BfmeStrVM0 *TheDisplay;
extern Rva0051D690Audio *TheAudio;
extern Shell *TheShell;

class Gen_0051b720Base
{
public:
	~Gen_0051b720Base();
};

class Gen_0051b720 : public Gen_0051b720Base
{
public:
	~Gen_0051b720();
};

// ??1Gen_0051b720@@QAE@XZ
Gen_0051b720::~Gen_0051b720()
{
	*(unsigned *)this = 0x1105FCCu;
	TheDisplay->bfmeFlagVM0(0);
	TheAudio->slot6c(2, 1, 0);
	TheShell->showShell(true);
}
