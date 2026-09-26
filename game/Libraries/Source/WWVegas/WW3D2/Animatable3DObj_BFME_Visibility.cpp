// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Clean C++ recovery of the BFME Animatable3DObjClass visibility virtual at
// retail RVA 0x009823F0 (74 bytes).  BFME inserts this query at RenderObjClass
// slot 50; the public name remains unrecovered, so the existing ABI placeholder
// `_bfme_ro_v50` is retained.  This TU-local view keeps the shared headers
// untouched while recording the proven BFME offsets used by the body.

// BFME HTree layout: W3D_NAME_LEN is 16, placing Pivot at +0x14.  The complete
// PivotClass is 0xb4 bytes here; IsVisible is at +0xa8.
struct BfmePivotClass
{
	char Name[16];
	BfmePivotClass *Parent;
	char BaseTransform[0x30];
	char Transform[0x30];
	char CapTransform[0x30];
	int Index;
	bool IsVisible;
	float PivotFade;
	bool WorldSpaceTranslation;
	bool IsCaptured;
	bool Unused;
};

class HTreeClass
{
public:
	bool Get_Visibility(int pivot) const
	{
		return Pivot[pivot].IsVisible;
	}

private:
	char Name[16];
	int NumPivots;
	BfmePivotClass *Pivot;
	float ScaleFactor;
};

// Only the two inherited virtual slots used by this body are named.  The
// placeholders preserve their retail offsets without creating a header-wide
// class declaration or inventing the unknown slot names.
class Animatable3DObjClass
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void Validate_Transform() const;
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void Update_Sub_Object_Transforms();

	virtual bool _bfme_ro_v50(int boneindex);

protected:
	char RenderObjStorage[0xf4];
	mutable bool IsTreeValid;
	char Padding[3];
	HTreeClass *HTree;
};

// ?_bfme_ro_v50@Animatable3DObjClass@@UAE_NH@Z
bool Animatable3DObjClass::_bfme_ro_v50(int boneindex)
{
	Validate_Transform();

	if (HTree) {
		if (!IsTreeValid) {
			Update_Sub_Object_Transforms();
		}

		return HTree->Get_Visibility(boneindex);
	} else {
		return true;
	}
}
