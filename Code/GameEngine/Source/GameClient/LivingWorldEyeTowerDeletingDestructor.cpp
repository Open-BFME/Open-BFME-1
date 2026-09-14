// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x0060CF60 calls LivingWorldEyeTower::~LivingWorldEyeTower through ILT 0x0003ABB6.

class LivingWorldEyeTower
{
public:
	virtual ~LivingWorldEyeTower();
};

__declspec(noinline) LivingWorldEyeTower::~LivingWorldEyeTower() {}

void Force_LivingWorldEyeTower_Deleting_Destructor(LivingWorldEyeTower *tower)
{
	delete tower;
}
