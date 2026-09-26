// ??0LivingWorldEyeTower@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc

struct EyeTowerHead
{
	unsigned int first[8];
	EyeTowerHead()
	{
		first[0] = 0;
		first[1] = 0;
		first[2] = 0;
		first[3] = 0;
		first[4] = 0;
		first[5] = 0;
		first[6] = 0;
		first[7] = 0;
	}
};

struct EyeTowerFirst
{
	float first;
	float second;
	float third;
	EyeTowerFirst() : first(1930.0f), third(50.0f) {}
};

class LivingWorldEyeTower
{
public:
	LivingWorldEyeTower();
	virtual ~LivingWorldEyeTower();

private:
	EyeTowerHead head;
	EyeTowerFirst first;
	float fields[17];
};

LivingWorldEyeTower::LivingWorldEyeTower()
{
	first.second = 210.0f;
	fields[0] = 0;
	fields[1] = 0;
	fields[2] = 0;
	fields[3] = 0;
	fields[4] = 0;
	fields[5] = 0;
	*(unsigned int *)&fields[6] = 1;
	fields[7] = 0;
	fields[8] = 0;
	fields[9] = 1930.0f;
	fields[10] = 210.0f;
	fields[11] = 1930.0f;
	fields[12] = 210.0f;
	fields[13] = 0;
	fields[14] = 0;
	fields[15] = 0;
	fields[16] = 0;
}
