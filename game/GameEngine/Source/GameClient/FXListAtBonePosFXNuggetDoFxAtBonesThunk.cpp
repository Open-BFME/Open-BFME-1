class Object;

class FXListAtBonePosFXNugget
{
protected:
	void doFxAtBones(const Object *, int) const;
};

class FXListAtBonePosDoFxAtBonesShim
{
public:
	void run(const Object *obj, int bone) const;
};

void FXListAtBonePosFXNugget::doFxAtBones(const Object *obj, int bone) const
{
	((const FXListAtBonePosDoFxAtBonesShim *)this)->run(obj, bone);
}
