// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: WaterSetting scalar-deleting destructor at retail RVA
// 0x0045CCF0 (30 bytes). Its exact constructor at 0x0045CBA0 and complete
// destructor at 0x0045CC80 establish the class. The destructor ILT is
// 0x0003D4B0; this replaces the former generic ICF alias at 0x005BF290.

class WaterSetting
{
public:
	virtual ~WaterSetting();
};

void forceWaterSettingDeletingDestructor()
{
	WaterSetting value;
}
