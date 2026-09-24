// Retail RVA0018E210..0018E3A5, complete405B stdcall(Object*,float).
// The original owner/name is unresolved; this address-labelled view records
// the observed two-stack-argument ABI and the Object field touched by retail.
// Name-table VA012A6918 indices273..276 are TURRET_ANGLE_0/90/180/270.
// The320-bit field begins atObject+110; retail word+130 is its word8.
// Float literals below independently match retail bits 00000000/40C90FDB/
// 3F490FDB/4016CBE4/407B53D2/40AFEDE0, respectively.
// cl: /DNDEBUG /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template <int NUMBITS>
class BitFlags
{
public:
    Bool test(Int bit) const { return m_bits.test(bit); }
    void set(Int bit) { m_bits.set(bit); }
    void reset(Int bit) { m_bits.reset(bit); }

private:
    _STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<320> ModelConditionFlags;
typedef char Rva0018E210ModelConditionFlagsSizeCheck[
    (sizeof(ModelConditionFlags) == 40) ? 1 : -1];

#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS \
	void notifyModelConditionChanged();
#include "object.h"

#define RVA0018E210_ZERO 0.0f
#define RVA0018E210_TWO_PI 6.2831854820251465f
#define RVA0018E210_PI_OVER_FOUR 0.7853981852531433f
#define RVA0018E210_THREE_PI_OVER_FOUR 2.3561944961547852f
#define RVA0018E210_FIVE_PI_OVER_FOUR 3.9269909858703613f
#define RVA0018E210_SEVEN_PI_OVER_FOUR 5.4977874755859375f

class Rva0018E210Owner
{
public:
    static void __stdcall apply(Object *object, float angle);
};

static __forceinline void clearModelCondition(Object *object,
    Int bit)
{
    if (object->m_modelConditionFlags.test(bit))
    {
        object->m_modelConditionFlags.reset(bit);
        object->notifyModelConditionChanged();
    }
}

static __forceinline void setModelCondition(Object *object,
    Int bit)
{
    if (!object->m_modelConditionFlags.test(bit))
    {
        object->m_modelConditionFlags.set(bit);
        object->notifyModelConditionChanged();
    }
}

enum Rva0018E210TurretAngleCondition {
    BFME_TURRET_ANGLE_0 = 273,
    BFME_TURRET_ANGLE_90 = 274,
    BFME_TURRET_ANGLE_180 = 275,
    BFME_TURRET_ANGLE_270 = 276
};

void __stdcall Rva0018E210Owner::apply(Object *object, float angle)
{
    clearModelCondition(object, BFME_TURRET_ANGLE_0);
    clearModelCondition(object, BFME_TURRET_ANGLE_90);
    clearModelCondition(object, BFME_TURRET_ANGLE_180);
    clearModelCondition(object, BFME_TURRET_ANGLE_270);

    if (angle < RVA0018E210_ZERO)
    {
        angle += RVA0018E210_TWO_PI;
    }

    if (angle > RVA0018E210_PI_OVER_FOUR &&
        angle <= RVA0018E210_THREE_PI_OVER_FOUR)
    {
        setModelCondition(object, BFME_TURRET_ANGLE_90);
        return;
    }

    if (angle > RVA0018E210_THREE_PI_OVER_FOUR &&
        angle <= RVA0018E210_FIVE_PI_OVER_FOUR)
    {
        setModelCondition(object, BFME_TURRET_ANGLE_180);
        return;
    }

    if (angle > RVA0018E210_FIVE_PI_OVER_FOUR &&
        angle <= RVA0018E210_SEVEN_PI_OVER_FOUR)
    {
        setModelCondition(object, BFME_TURRET_ANGLE_270);
        return;
    }

    setModelCondition(object, BFME_TURRET_ANGLE_0);
}

