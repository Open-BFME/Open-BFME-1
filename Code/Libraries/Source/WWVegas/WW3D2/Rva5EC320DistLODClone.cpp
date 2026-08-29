class RenderObjClass
{
public:
	virtual ~RenderObjClass();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/distlod.h
class DistLODClass : public RenderObjClass
{
public:
	DistLODClass(const DistLODClass &that);
	virtual RenderObjClass *Clone() const;

private:
	unsigned char m_data[168];
};

// ?Clone@DistLODClass@@ present-unmatched
RenderObjClass *DistLODClass::Clone() const
{
	return new DistLODClass(*this);
}
