class ParabolicEase
{
public:
	void setEaseTimes(float one, float two, float three);
};

class BfmeThingBRD
{
public:
	BfmeThingBRD *bfmeGoBRD(void *one, void *two, void *three);
};

BfmeThingBRD *BfmeThingBRD::bfmeGoBRD(void *one, void *two, void *three)
{
	ParabolicEase *ease = reinterpret_cast<ParabolicEase *>(this);
	ease->setEaseTimes(*reinterpret_cast<float *>(&one),
		*reinterpret_cast<float *>(&two), *reinterpret_cast<float *>(&three));
	return this;
}
