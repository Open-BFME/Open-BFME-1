// cl: /DNDEBUG /MD /EHsc

class Glo012F1028Type
{
public:
	void j_00008c0b(void);
};

extern Glo012F1028Type *Glo012F1028;

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
		Glo012F1028->j_00008c0b();
	j_0002a969();
	j_00021f26();
	j_0002eeec();
}
