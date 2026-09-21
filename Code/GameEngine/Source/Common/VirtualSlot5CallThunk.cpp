int __stdcall IgnoreThreeArgumentsReturnZeroThunk(int, int, int)
{
    return 0;
}

int __stdcall IgnoreThreeArgumentsReturnZeroAlternateThunk(int, int, int)
{
    return 0;
}

int __stdcall IgnoreTwoArgumentsReturnOneThunk(int, int)
{
    return 1;
}

struct VirtualSlot5CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void invoke(int value);

    void invokeOne();
};

// ?d_0016bb20@@YAXXZ
void VirtualSlot5CallThunk::invokeOne()
{
    invoke(1);
}

struct VirtualSlot8CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void invoke(int value);

    void invokeZero();
    void invokeZeroAlternate();
    void invokeZeroThird();
    void invokeOne();
    void invokeZeroFourth();
    void invokeZeroFifth();
    void invokeZeroSixth();
    void invokeZeroSeventh();
};

// ?d_001fb260@@YAXXZ
void VirtualSlot8CallThunk::invokeZero()
{
    invoke(0);
}

// ?d_001fbb80@@YAXXZ
void VirtualSlot8CallThunk::invokeZeroAlternate()
{
    invoke(0);
}

// ?d_002043e0@@YAXXZ
void VirtualSlot8CallThunk::invokeZeroThird()
{
    invoke(0);
}

// ?d_0020a800@@YAXXZ
void VirtualSlot8CallThunk::invokeOne()
{
    invoke(1);
}

// ?d_0020a810@@YAXXZ
void VirtualSlot8CallThunk::invokeZeroFourth()
{
    invoke(0);
}

// ?d_0027ffa0@@YAXXZ
void VirtualSlot8CallThunk::invokeZeroFifth()
{
    invoke(0);
}

// ?d_002899f0@@YAXXZ
void VirtualSlot8CallThunk::invokeZeroSixth()
{
    invoke(0);
}

// ?d_002d7a50@@YAXXZ
void VirtualSlot8CallThunk::invokeZeroSeventh()
{
    invoke(0);
}

struct VirtualSlot2CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke();

    void invokeIgnoringArgument(int unused);
};

// ?d_0025a2a0@@YAXXZ
void VirtualSlot2CallThunk::invokeIgnoringArgument(int)
{
    invoke();
}

struct VirtualSlot2IntCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke(int value);

    void invokeSix();
    void invokeSixAlternate();
};

// ?d_0059f200@@YAXXZ
void VirtualSlot2IntCallThunk::invokeSix()
{
    invoke(6);
}

// ?d_0059f5b0@@YAXXZ
void VirtualSlot2IntCallThunk::invokeSixAlternate()
{
    invoke(6);
}

struct VirtualSlot9CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void invoke(int value);

    void invokeOne();
};

// ?d_00695640@@YAXXZ
void VirtualSlot9CallThunk::invokeOne()
{
    invoke(1);
}

struct VirtualSlot11CallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void invoke(int first, int second);

    void invokeZeroOne();
};

// ?d_002a5a30@@YAXXZ
void VirtualSlot11CallThunk::invokeZeroOne()
{
    invoke(0, 1);
}

struct VirtualSlot2MemberCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke(int value);

    unsigned long padding[4];
    int value;

    void invokeMember();
    void invokeMemberAlternate();
    void invokeMemberThird();
    void invokeMemberFourth();
    void invokeMemberFifth();
    void invokeMemberSixth();
    void invokeMemberSeventh();
    void invokeMemberEighth();
};

// ?d_0059d3b0@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMember()
{
    invoke(value);
}

// ?d_0059d950@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMemberAlternate()
{
    invoke(value);
}

// ?d_0059dd80@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMemberThird()
{
    invoke(value);
}

// ?d_0059e1e0@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMemberFourth()
{
    invoke(value);
}

// ?d_0059e7b0@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMemberFifth()
{
    invoke(value);
}

// ?d_0059f8e0@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMemberSixth()
{
    invoke(value);
}

// ?d_0059fd20@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMemberSeventh()
{
    invoke(value);
}

// ?d_005a0420@@YAXXZ
void VirtualSlot2MemberCallThunk::invokeMemberEighth()
{
    invoke(value);
}

struct VirtualSlot10IncrementedMemberCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void invoke(int value);

    unsigned long padding[17];
    int value;

    void invokeNext();
};

// ?d_007e4730@@YAXXZ
void VirtualSlot10IncrementedMemberCallThunk::invokeNext()
{
    invoke(value + 1);
}

struct EmbeddedVirtualSlot1Thunk
{
    virtual void slot0();
    virtual void invoke();

    unsigned long padding[2];
};

struct EmbeddedVirtualSlot1CallFacet
{
    unsigned long value;

    void invokeIgnoringArgument(int unused);
    void invokeIgnoringArgumentAlternate(int unused);
};

struct EmbeddedVirtualSlot1CallOwner : EmbeddedVirtualSlot1Thunk, EmbeddedVirtualSlot1CallFacet
{
};

// ?d_0011a180@@YAXXZ
void EmbeddedVirtualSlot1CallFacet::invokeIgnoringArgument(int)
{
    EmbeddedVirtualSlot1Thunk *owner = reinterpret_cast<EmbeddedVirtualSlot1Thunk *>(
        reinterpret_cast<unsigned char *>(this) - sizeof(EmbeddedVirtualSlot1Thunk));
    owner->invoke();
}

// ?d_00214cf0@@YAXXZ
void EmbeddedVirtualSlot1CallFacet::invokeIgnoringArgumentAlternate(int)
{
    EmbeddedVirtualSlot1Thunk *owner = reinterpret_cast<EmbeddedVirtualSlot1Thunk *>(
        reinterpret_cast<unsigned char *>(this) - sizeof(EmbeddedVirtualSlot1Thunk));
    owner->invoke();
}

struct EmbeddedVirtualSlot2Thunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke();
};

struct EmbeddedVirtualSlot2CallOwner
{
    unsigned long padding[5];
    EmbeddedVirtualSlot2Thunk embedded;

    void invokeIgnoringArgument(int unused);
};

// ?d_001fe4d0@@YAXXZ
void EmbeddedVirtualSlot2CallOwner::invokeIgnoringArgument(int)
{
    embedded.invoke();
}

struct SecondaryBaseVirtualSlot11Primary
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void invoke();

    unsigned long padding[7];
};

struct SecondaryBaseVirtualSlot11Facet
{
    unsigned long value;

    void invokeIgnoringArgument(int unused);
};

struct SecondaryBaseVirtualSlot11Owner : SecondaryBaseVirtualSlot11Primary,
                                         SecondaryBaseVirtualSlot11Facet
{
};

// ?d_00202ec0@@YAXXZ
void SecondaryBaseVirtualSlot11Facet::invokeIgnoringArgument(int)
{
    SecondaryBaseVirtualSlot11Primary *owner = reinterpret_cast<SecondaryBaseVirtualSlot11Primary *>(
        reinterpret_cast<unsigned char *>(this) - sizeof(SecondaryBaseVirtualSlot11Primary));
    owner->invoke();
}

struct VirtualSlot2ArgumentThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void invoke();
};

struct VirtualSlot2ArgumentCallOwner
{
    void invokeArgument(VirtualSlot2ArgumentThunk *target);
};

// ?d_007b77e0@@YAXXZ
void VirtualSlot2ArgumentCallOwner::invokeArgument(VirtualSlot2ArgumentThunk *target)
{
    target->invoke();
}

extern void *TheTerrainLogic;

struct VirtualSlot4GlobalCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void invoke(void *value);

    void invokeTerrainLogic();
};

// ?d_00107270@@YAXXZ
void VirtualSlot4GlobalCallThunk::invokeTerrainLogic()
{
    invoke(TheTerrainLogic);
}

struct VirtualSlot11SecondArgumentCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void invoke(int value);

    void invokeSecond(int unused, int value);
    void invokeSecondAlternate(int unused, int value);
    void invokeSecondThird(int unused, int value);
    void invokeSecondFourth(int unused, int value);
};

// ?d_00259760@@YAXXZ
void VirtualSlot11SecondArgumentCallThunk::invokeSecond(int, int value)
{
    invoke(value);
}

// ?d_00263fc0@@YAXXZ
void VirtualSlot11SecondArgumentCallThunk::invokeSecondAlternate(int, int value)
{
    invoke(value);
}

// ?d_0026b0a0@@YAXXZ
void VirtualSlot11SecondArgumentCallThunk::invokeSecondThird(int, int value)
{
    invoke(value);
}

// ?d_0026cd20@@YAXXZ
void VirtualSlot11SecondArgumentCallThunk::invokeSecondFourth(int, int value)
{
    invoke(value);
}

struct ProducedValue
{
    int value;
};

extern int __stdcall produceStoredValue(int value);

ProducedValue &__stdcall storeProducedValue(ProducedValue &result, int value)
{
    result.value = produceStoredValue(value);
    return result;
}

struct VirtualSlot3FlagThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void invoke();

    unsigned char padding[0x46];
    bool invoked;

    void invokeAndSet();
};

// ?d_00739d90@@YAXXZ
void VirtualSlot3FlagThunk::invokeAndSet()
{
    invoke();
    invoked = true;
}

struct VirtualSlot21FirstArgumentThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void invoke(int value);

    void invokeFirst(int value, int unused1, int unused2, int unused3, int unused4, int unused5);
};

// ?d_0045bab0@@YAXXZ
void VirtualSlot21FirstArgumentThunk::invokeFirst(int value, int, int, int, int, int)
{
    invoke(value);
}

struct VirtualSlot25EmbeddedArgumentsThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void invoke(void *first, void *second);

    unsigned char padding[0x4C - sizeof(void *)];
    int second;

    void invokeEmbedded();
};

// ?d_002206d0@@YAXXZ
void VirtualSlot25EmbeddedArgumentsThunk::invokeEmbedded()
{
    invoke(reinterpret_cast<unsigned char *>(this) + 0x38, &second);
}

struct Offset24IntegerSetterThunk
{
    unsigned char padding[0x18];
    int value;

    void setValue(int newValue);
};

// ?d_0045ba20@@YAXXZ
void Offset24IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset68BooleanSetterThunk
{
    unsigned char padding[0x44];
    bool value;

    void setValue(bool newValue);
};

// ?d_0045b9e0@@YAXXZ
void Offset68BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset64IntegerSetterThunk
{
    unsigned char padding[0x40];
    int value;

    void setValue(int newValue);
};

// ?d_0045bd90@@YAXXZ
void Offset64IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset117BooleanSetterThunk
{
    unsigned char padding[0x75];
    bool value;

    void setValue(bool newValue);
};

// ?d_0045bdc0@@YAXXZ
void Offset117BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset108IntegerSetterThunk
{
    unsigned char padding[0x6C];
    int value;

    void setValue(int newValue);
};

// ?d_0045be10@@YAXXZ
void Offset108IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset118FlagSetterThunk
{
    unsigned char padding[0x76];
    bool value;

    void set();
};

// ?d_0045be60@@YAXXZ
void Offset118FlagSetterThunk::set()
{
    value = true;
}

struct Offset96IntegerPairSetterThunk
{
    unsigned char padding[0x60];
    int first;
    int second;

    void setValues(int firstValue, int secondValue);
};

// ?d_0045be70@@YAXXZ
void Offset96IntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
}

struct SparseIntegerResetThunk
{
    unsigned char padding[0x58];
    int first;
    int second;
    unsigned char gap[8];
    int third;

    void reset();
};

// ?d_0045bed0@@YAXXZ
void SparseIntegerResetThunk::reset()
{
    first = 0;
    second = 0;
    third = 0;
}

struct Offset116BooleanSetterThunk
{
    unsigned char padding[0x74];
    bool value;

    void setValue(bool newValue);
};

// ?d_0045bee0@@YAXXZ
void Offset116BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset112IntegerSetterThunk
{
    unsigned char padding[0x70];
    int value;

    void setValue(int newValue);
};

// ?d_0045bf20@@YAXXZ
void Offset112IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset132BooleanGetterThunk
{
    unsigned char padding[0x84];
    bool value;

    bool get() const;
};

// ?d_0045bf60@@YAXXZ
bool Offset132BooleanGetterThunk::get() const
{
    return value;
}

struct Offset136IntegerGetterThunk
{
    unsigned char padding[0x88];
    int value;

    int get() const;
};

// ?d_0045bf80@@YAXXZ
int Offset136IntegerGetterThunk::get() const
{
    return value;
}

struct Offset432IntegerGetterThunk
{
    unsigned char padding[0x1b0];
    int value;

    int get() const;
};

// ?d_004647f0@@YAXXZ
int Offset432IntegerGetterThunk::get() const
{
    return value;
}

struct Offset592IntegerGetterThunk
{
    unsigned char padding[0x250];
    int value;

    int get() const;
};

// ?d_00465a70@@YAXXZ
int Offset592IntegerGetterThunk::get() const
{
    return value;
}

struct Offset140IntegerPairSetterThunk
{
    unsigned char padding[0x8c];
    int first;
    int second;

    void setValues(int firstValue, int secondValue);
};

// ?d_0045bfb0@@YAXXZ
void Offset140IntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
}

struct Offset140IntegerPairValidityThunk
{
    unsigned char padding[0x8c];
    int first;
    int second;

    bool isValid() const;
};

// ?d_0045bff0@@YAXXZ
bool Offset140IntegerPairValidityThunk::isValid() const
{
    return first != -1 && second != -1;
}

struct IntegerTripleCopyValue
{
    int first;
    int second;
    int third;
};

struct Offset140IntegerTripleCopyThunk
{
    unsigned char padding[0x8c];
    IntegerTripleCopyValue value;

    int *copyTo(int *destination);
};

// ?d_0045c020@@YAXXZ
int *Offset140IntegerTripleCopyThunk::copyTo(int *destination)
{
    *reinterpret_cast<IntegerTripleCopyValue *>(destination) = value;
    return destination;
}

struct Offset152IntegerResetThunk
{
    unsigned char padding[0x98];
    int value;

    void reset();
};

// ?d_0045c0c0@@YAXXZ
void Offset152IntegerResetThunk::reset()
{
    value = 0;
}

struct Offset172IntegerPairSetterThunk
{
    unsigned char padding[0xac];
    int first;
    int second;

    void setValues(int firstValue, int secondValue);
};

// ?d_0045c100@@YAXXZ
void Offset172IntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
}

struct Offset156FloatGetterThunk
{
    unsigned char padding[0x9c];
    float value;

    float get() const;
};

// ?d_0045c140@@YAXXZ
float Offset156FloatGetterThunk::get() const
{
    return value;
}

struct Offset164FloatGetterThunk
{
    unsigned char padding[0xa4];
    float value;

    float get() const;
};

// ?d_0045c150@@YAXXZ
float Offset164FloatGetterThunk::get() const
{
    return value;
}

struct TwoIntegerClearThunk
{
    int first;
    int second;

    TwoIntegerClearThunk();
};

// ?d_0045c420@@YAXXZ
TwoIntegerClearThunk::TwoIntegerClearThunk() :
    first(0),
    second(0)
{
}

struct VirtualSlot9NoArgumentCallThunk
{
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void invoke();

    void call();
};

// ?d_0045c410@@YAXXZ
void VirtualSlot9NoArgumentCallThunk::call()
{
    invoke();
}

struct OffsetZeroIntegerSetterReturningThisThunk
{
    int value;

    OffsetZeroIntegerSetterReturningThisThunk *setValue(int newValue);
    OffsetZeroIntegerSetterReturningThisThunk *setValueAlternate(int newValue);
};

// ?d_0045cb90@@YAXXZ
OffsetZeroIntegerSetterReturningThisThunk *OffsetZeroIntegerSetterReturningThisThunk::setValue(int newValue)
{
    value = newValue;
    return this;
}

// ?d_0045e100@@YAXXZ
OffsetZeroIntegerSetterReturningThisThunk *OffsetZeroIntegerSetterReturningThisThunk::setValueAlternate(int newValue)
{
    value = newValue;
    return this;
}

struct Offset40IntegerSetterThunk
{
    unsigned char padding[0x28];
    int value;

    void setValue(int newValue);
};

// ?d_0045cd70@@YAXXZ
void Offset40IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset60IntegerSetterThunk
{
    unsigned char padding[0x3c];
    int value;

    void setValue(int newValue);
};

// ?d_0045cd80@@YAXXZ
void Offset60IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset4IntegerSetterThunk
{
    unsigned char padding[4];
    int value;

    void setValue(int newValue);
};

// ?d_0045cd90@@YAXXZ
void Offset4IntegerSetterThunk::setValue(int newValue)
{
    value = newValue;
}

struct Offset65BooleanSetterThunk
{
    unsigned char padding[0x41];
    bool value;

    void setValue(bool newValue);
};

// ?d_0045cda0@@YAXXZ
void Offset65BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct Offset64BooleanSetterThunk
{
    unsigned char padding[0x40];
    bool value;

    void setValue(bool newValue);
};

// ?d_0045cdb0@@YAXXZ
void Offset64BooleanSetterThunk::setValue(bool newValue)
{
    value = newValue;
}

struct OffsetZeroIntegerSetterReturningThisAlternateThunk
{
    int value;

    OffsetZeroIntegerSetterReturningThisAlternateThunk *setValue(int newValue);
};

// ?d_0045cfc0@@YAXXZ
OffsetZeroIntegerSetterReturningThisAlternateThunk *OffsetZeroIntegerSetterReturningThisAlternateThunk::setValue(int newValue)
{
    value = newValue;
    return this;
}

struct OffsetZeroIntegerCopyReturningThisThunk
{
    int value;

    OffsetZeroIntegerCopyReturningThisThunk *copyFrom(const OffsetZeroIntegerCopyReturningThisThunk *other);
    OffsetZeroIntegerCopyReturningThisThunk *copyFromAlternate(const OffsetZeroIntegerCopyReturningThisThunk *other);
};

// ?d_0045cfd0@@YAXXZ
OffsetZeroIntegerCopyReturningThisThunk *OffsetZeroIntegerCopyReturningThisThunk::copyFrom(const OffsetZeroIntegerCopyReturningThisThunk *other)
{
    value = other->value;
    return this;
}

// ?d_0045dff0@@YAXXZ
OffsetZeroIntegerCopyReturningThisThunk *OffsetZeroIntegerCopyReturningThisThunk::copyFromAlternate(const OffsetZeroIntegerCopyReturningThisThunk *other)
{
    value = other->value;
    return this;
}

struct OffsetZeroSecondIntegerSetterReturningThisThunk
{
    int value;

    OffsetZeroSecondIntegerSetterReturningThisThunk *setSecond(int unused, int newValue);
    OffsetZeroSecondIntegerSetterReturningThisThunk *setSecondAlternate(int unused, int newValue);
    OffsetZeroSecondIntegerSetterReturningThisThunk *setSecondThird(int unused, int newValue);
    OffsetZeroSecondIntegerSetterReturningThisThunk *setSecondFourth(int unused, int newValue);
    OffsetZeroSecondIntegerSetterReturningThisThunk *setSecondFifth(int unused, int newValue);
};

// ?d_0045cff0@@YAXXZ
OffsetZeroSecondIntegerSetterReturningThisThunk *OffsetZeroSecondIntegerSetterReturningThisThunk::setSecond(int, int newValue)
{
    value = newValue;
    return this;
}

// ?d_0045e960@@YAXXZ
OffsetZeroSecondIntegerSetterReturningThisThunk *OffsetZeroSecondIntegerSetterReturningThisThunk::setSecondAlternate(int, int newValue)
{
    value = newValue;
    return this;
}

// ?d_0045e970@@YAXXZ
OffsetZeroSecondIntegerSetterReturningThisThunk *OffsetZeroSecondIntegerSetterReturningThisThunk::setSecondThird(int, int newValue)
{
    value = newValue;
    return this;
}

// ?d_0045e980@@YAXXZ
OffsetZeroSecondIntegerSetterReturningThisThunk *OffsetZeroSecondIntegerSetterReturningThisThunk::setSecondFourth(int, int newValue)
{
    value = newValue;
    return this;
}

// ?d_0045ea70@@YAXXZ
OffsetZeroSecondIntegerSetterReturningThisThunk *OffsetZeroSecondIntegerSetterReturningThisThunk::setSecondFifth(int, int newValue)
{
    value = newValue;
    return this;
}

void copyIntegerIfDestinationNotNull(int *destination, const int *source)
{
    if (destination != 0)
    {
        *destination = *source;
    }
}

struct IndirectIntegerCopyThunk
{
    const int *source;

    int *copyTo(int *destination) const;
};

// ?d_0045d110@@YAXXZ
int *IndirectIntegerCopyThunk::copyTo(int *destination) const
{
    *destination = *source;
    return destination;
}

struct DirectIntegerCopyThunk
{
    int value;

    int *copyTo(int *destination) const;
};

// ?d_0045e7e0@@YAXXZ
int *DirectIntegerCopyThunk::copyTo(int *destination) const
{
    *destination = value;
    return destination;
}

struct OwnerPairInitializerThunk;

struct OwnerPairValue
{
    int value;
    OwnerPairInitializerThunk *owner;
};

struct OwnerPairInitializerThunk
{
    OwnerPairValue *initialize(OwnerPairValue *destination);
    OwnerPairValue *initializeAlternate(OwnerPairValue *destination);
    OwnerPairValue *initializeThird(OwnerPairValue *destination);
    OwnerPairValue *initializeFourth(OwnerPairValue *destination);
    OwnerPairValue *initializeFifth(OwnerPairValue *destination);
    OwnerPairValue *initializeSixth(OwnerPairValue *destination);
    OwnerPairValue *initializeSeventh(OwnerPairValue *destination);
    OwnerPairValue *initializeEighth(OwnerPairValue *destination);
    OwnerPairValue *initializeNinth(OwnerPairValue *destination);
    OwnerPairValue *initializeTenth(OwnerPairValue *destination);
    OwnerPairValue *initializeEleventh(OwnerPairValue *destination);
    OwnerPairValue *initializeTwelfth(OwnerPairValue *destination);
    OwnerPairValue *initializeThirteenth(OwnerPairValue *destination);
    OwnerPairValue *initializeFourteenth(OwnerPairValue *destination);
    OwnerPairValue *initializeFifteenth(OwnerPairValue *destination);
    OwnerPairValue *initializeSixteenth(OwnerPairValue *destination);
    OwnerPairValue *initializeSeventeenth(OwnerPairValue *destination);
    OwnerPairValue *initializeEighteenth(OwnerPairValue *destination);
    OwnerPairValue *initializeNineteenth(OwnerPairValue *destination);
    OwnerPairValue *initializeTwentieth(OwnerPairValue *destination);
    OwnerPairValue *initializeTwentyFirst(OwnerPairValue *destination);
    OwnerPairValue *initializeTwentySecond(OwnerPairValue *destination);
};

// ?d_0045f3c0@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initialize(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_0045f3f0@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeAlternate(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_0045f480@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeThird(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_0045f970@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeFourth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_0045f990@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeFifth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_0045f9b0@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeSixth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_004677f0@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeSeventh(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467820@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeEighth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467840@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeNinth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467870@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeTenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467900@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeEleventh(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467920@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeTwelfth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467940@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeThirteenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467960@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeFourteenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00467980@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeFifteenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_004681c0@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeSixteenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_004681e0@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeSeventeenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00468200@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeEighteenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00468220@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeNineteenth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00468240@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeTwentieth(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00468260@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeTwentyFirst(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

// ?d_00468280@@YAXXZ
OwnerPairValue *OwnerPairInitializerThunk::initializeTwentySecond(OwnerPairValue *destination)
{
    destination->value = 0;
    destination->owner = this;
    return destination;
}

struct SelfLinkedResetValue
{
    bool active;
    unsigned char padding[3];
    int value;
    SelfLinkedResetValue *first;
    SelfLinkedResetValue *second;
};

struct IndirectSelfLinkedResetThunk
{
    SelfLinkedResetValue *state;

    void reset();
};

// ?d_0045e990@@YAXXZ
void IndirectSelfLinkedResetThunk::reset()
{
    state->active = false;
    state->value = 0;
    state->first = state;
    state->second = state;
}

struct OffsetEightIndirectIntegerCopyThunk
{
    const unsigned char *source;

    int *copyTo(int *destination) const;
};

// ?d_0045e7c0@@YAXXZ
int *OffsetEightIndirectIntegerCopyThunk::copyTo(int *destination) const
{
    *destination = *reinterpret_cast<const int *>(source + 8);
    return destination;
}

struct LinkedNodePopValue
{
    LinkedNodePopValue *next;
};

struct LinkedNodePopThunk
{
    LinkedNodePopValue *head;

    LinkedNodePopValue **popTo(LinkedNodePopValue **destination, int unused);
};

// ?d_0045d130@@YAXXZ
LinkedNodePopValue **LinkedNodePopThunk::popTo(LinkedNodePopValue **destination, int)
{
    LinkedNodePopValue *oldHead = head;
    head = oldHead->next;
    *destination = oldHead;
    return destination;
}

struct VirtualMinusOneConstructorThunk
{
    virtual ~VirtualMinusOneConstructorThunk();

    int value;

    VirtualMinusOneConstructorThunk();
    VirtualMinusOneConstructorThunk(const VirtualMinusOneConstructorThunk &other);
};

// ?d_0045dcf0@@YAXXZ
VirtualMinusOneConstructorThunk::VirtualMinusOneConstructorThunk() :
    value(-1)
{
}

// ?d_0045e070@@YAXXZ
VirtualMinusOneConstructorThunk::VirtualMinusOneConstructorThunk(const VirtualMinusOneConstructorThunk &other) :
    value(other.value)
{
}

// ??1VirtualMinusOneConstructorThunk@@UAE@XZ present-unmatched (only the
// deleting destructor ??_G has a row here, at ?d_0045dd20)
VirtualMinusOneConstructorThunk::~VirtualMinusOneConstructorThunk()
{
}

struct ReferenceCountedReleaseValue
{
    virtual void release(int deletingFlag);

    int referenceCount;

    int decrementReferenceCount()
    {
        return --referenceCount;
    }
};

struct ReferencePointerReleaseThunk
{
    ReferenceCountedReleaseValue *value;

    void release();
    void releaseAlternate();
    void releaseThird();
    void releaseFourth();
    void releaseFifth();
    void releaseSixth();
};

// ?d_0045de60@@YAXXZ
void ReferencePointerReleaseThunk::release()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

// ?d_0045de80@@YAXXZ
void ReferencePointerReleaseThunk::releaseAlternate()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

// ?d_0045def0@@YAXXZ
void ReferencePointerReleaseThunk::releaseThird()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

// ?d_0045e610@@YAXXZ
void ReferencePointerReleaseThunk::releaseFourth()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

// ?d_0045e630@@YAXXZ
void ReferencePointerReleaseThunk::releaseFifth()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

// ?d_0045e650@@YAXXZ
void ReferencePointerReleaseThunk::releaseSixth()
{
    ReferenceCountedReleaseValue *current = value;
    if (current != 0)
    {
        if (current->decrementReferenceCount() <= 0)
        {
            current->release(1);
        }
    }
}

struct ReferencePointerAssignmentThunk
{
    ReferenceCountedReleaseValue *value;

    ReferencePointerAssignmentThunk *assign(const ReferencePointerAssignmentThunk *other);
    ReferencePointerAssignmentThunk *assignAlternate(const ReferencePointerAssignmentThunk *other);
};

// ?d_0045dea0@@YAXXZ
ReferencePointerAssignmentThunk *ReferencePointerAssignmentThunk::assign(const ReferencePointerAssignmentThunk *other)
{
    if (this != other)
    {
        ReferenceCountedReleaseValue *newValue = other->value;
        if (newValue != 0)
        {
            ++newValue->referenceCount;
        }

        ReferenceCountedReleaseValue *oldValue = value;
        if (oldValue != 0 && oldValue->decrementReferenceCount() <= 0)
        {
            oldValue->release(1);
        }

        value = other->value;
    }

    return this;
}

// ?d_0045e670@@YAXXZ
ReferencePointerAssignmentThunk *ReferencePointerAssignmentThunk::assignAlternate(const ReferencePointerAssignmentThunk *other)
{
    if (this != other)
    {
        ReferenceCountedReleaseValue *newValue = other->value;
        if (newValue != 0)
        {
            ++newValue->referenceCount;
        }

        ReferenceCountedReleaseValue *oldValue = value;
        if (oldValue != 0 && oldValue->decrementReferenceCount() <= 0)
        {
            oldValue->release(1);
        }

        value = other->value;
    }

    return this;
}

struct RetainedReferenceCopyConstructorThunk
{
    ReferenceCountedReleaseValue *value;

    RetainedReferenceCopyConstructorThunk(const RetainedReferenceCopyConstructorThunk &other);
};

// ?d_0045e1c0@@YAXXZ
RetainedReferenceCopyConstructorThunk::RetainedReferenceCopyConstructorThunk(const RetainedReferenceCopyConstructorThunk &other) :
    value(other.value)
{
    if (value != 0)
    {
        ++value->referenceCount;
    }
}

struct RetainedReferenceCopyConstructorAlternateThunk
{
    ReferenceCountedReleaseValue *value;

    RetainedReferenceCopyConstructorAlternateThunk(const RetainedReferenceCopyConstructorAlternateThunk &other);
};

// ?d_0045ea50@@YAXXZ
RetainedReferenceCopyConstructorAlternateThunk::RetainedReferenceCopyConstructorAlternateThunk(const RetainedReferenceCopyConstructorAlternateThunk &other) :
    value(other.value)
{
    if (value != 0)
    {
        ++value->referenceCount;
    }
}

struct RetainedReferenceCopyConstructorThirdThunk
{
    ReferenceCountedReleaseValue *value;

    RetainedReferenceCopyConstructorThirdThunk(const RetainedReferenceCopyConstructorThirdThunk &other);
};

// ?d_0045f4c0@@YAXXZ
RetainedReferenceCopyConstructorThirdThunk::RetainedReferenceCopyConstructorThirdThunk(const RetainedReferenceCopyConstructorThirdThunk &other) :
    value(other.value)
{
    if (value != 0)
    {
        ++value->referenceCount;
    }
}

struct RetainedReferenceCopyConstructorFourthThunk
{
    ReferenceCountedReleaseValue *value;

    RetainedReferenceCopyConstructorFourthThunk(const RetainedReferenceCopyConstructorFourthThunk &other);
};

// ?d_004679b0@@YAXXZ
RetainedReferenceCopyConstructorFourthThunk::RetainedReferenceCopyConstructorFourthThunk(const RetainedReferenceCopyConstructorFourthThunk &other) :
    value(other.value)
{
    if (value != 0)
    {
        ++value->referenceCount;
    }
}

struct RetainedReferenceSetterThunk
{
    ReferenceCountedReleaseValue *value;

    RetainedReferenceSetterThunk *setValue(ReferenceCountedReleaseValue *newValue);
    RetainedReferenceSetterThunk *setValueAlternate(ReferenceCountedReleaseValue *newValue);
    RetainedReferenceSetterThunk *setValueThird(ReferenceCountedReleaseValue *newValue);
};

// ?d_0045e480@@YAXXZ
RetainedReferenceSetterThunk *RetainedReferenceSetterThunk::setValue(ReferenceCountedReleaseValue *newValue)
{
    value = newValue;
    if (newValue != 0)
    {
        ++newValue->referenceCount;
    }
    return this;
}

// ?d_0045e4a0@@YAXXZ
RetainedReferenceSetterThunk *RetainedReferenceSetterThunk::setValueAlternate(ReferenceCountedReleaseValue *newValue)
{
    value = newValue;
    if (newValue != 0)
    {
        ++newValue->referenceCount;
    }
    return this;
}

// ?d_0045e4c0@@YAXXZ
RetainedReferenceSetterThunk *RetainedReferenceSetterThunk::setValueThird(ReferenceCountedReleaseValue *newValue)
{
    value = newValue;
    if (newValue != 0)
    {
        ++newValue->referenceCount;
    }
    return this;
}

struct PointerPayloadGetterThunk
{
    unsigned char *base;

    unsigned char *getPayload() const;
    unsigned char *getPayloadAlternate() const;
    unsigned char *getPayloadThird() const;
    unsigned char *getPayloadFourth() const;
    unsigned char *getPayloadFifth() const;
    unsigned char *getPayloadSixth() const;
    unsigned char *getPayloadSeventh() const;
    unsigned char *getPayloadEighth() const;
    unsigned char *getPayloadNinth() const;
    unsigned char *getPayloadTenth() const;
    unsigned char *getPayloadEleventh() const;
    unsigned char *getPayloadTwelfth() const;
    unsigned char *getPayloadThirteenth() const;
    unsigned char *getPayloadFourteenth() const;
    unsigned char *getPayloadFifteenth() const;
    unsigned char *getPayloadSixteenth() const;
    unsigned char *getPayloadSeventeenth() const;
    unsigned char *getPayloadEighteenth() const;
    unsigned char *getPayloadNineteenth() const;
    unsigned char *getPayloadTwentieth() const;
    unsigned char *getPayloadTwentyFirst() const;
    unsigned char *getPayloadTwentySecond() const;
    unsigned char *getPayloadTwentyThird() const;
    unsigned char *getPayloadTwentyFourth() const;
    unsigned char *getPayloadTwentyFifth() const;
    unsigned char *getPayloadTwentySixth() const;
    unsigned char *getPayloadTwentySeventh() const;
    unsigned char *getPayloadTwentyEighth() const;
    unsigned char *getSecondPayload() const;
    unsigned char *getThirdPayload() const;
    unsigned char *getFourthPayload() const;
};

// ?d_0045e010@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayload() const
{
    return base + 4;
}

// ?d_0045e020@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadAlternate() const
{
    return base + 4;
}

// ?d_0045e030@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadThird() const
{
    return base + 4;
}

// ?d_0045e0b0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadFourth() const
{
    return base + 4;
}

// ?d_0045e6f0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadFifth() const
{
    return base + 4;
}

// ?d_0045e700@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadSixth() const
{
    return base + 4;
}

// ?d_0045e710@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadSeventh() const
{
    return base + 4;
}

// ?d_004660b0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadEighth() const
{
    return base + 4;
}

// ?d_004660c0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadNinth() const
{
    return base + 4;
}

// ?d_004660d0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTenth() const
{
    return base + 4;
}

// ?d_004660e0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadEleventh() const
{
    return base + 4;
}

// ?d_004660f0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwelfth() const
{
    return base + 4;
}

// ?d_00466100@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadThirteenth() const
{
    return base + 4;
}

// ?d_00466110@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadFourteenth() const
{
    return base + 4;
}

// ?d_00466120@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadFifteenth() const
{
    return base + 4;
}

// ?d_00466130@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadSixteenth() const
{
    return base + 4;
}

// ?d_00466140@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadSeventeenth() const
{
    return base + 4;
}

// ?d_004669e0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadEighteenth() const
{
    return base + 4;
}

// ?d_004669f0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadNineteenth() const
{
    return base + 4;
}

// ?d_00466a00@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentieth() const
{
    return base + 4;
}

// ?d_00466a10@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentyFirst() const
{
    return base + 4;
}

// ?d_00466a20@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentySecond() const
{
    return base + 4;
}

// ?d_00466a30@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentyThird() const
{
    return base + 4;
}

// ?d_00466a40@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentyFourth() const
{
    return base + 4;
}

// ?d_00466a50@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentyFifth() const
{
    return base + 4;
}

// ?d_00472850@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentySixth() const
{
    return base + 4;
}

// ?d_004728a0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentySeventh() const
{
    return base + 4;
}

// ?d_004728f0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getPayloadTwentyEighth() const
{
    return base + 4;
}

// ?d_0045e0c0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getSecondPayload() const
{
    return base + 8;
}

// ?d_0045e0d0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getThirdPayload() const
{
    return base + 12;
}

// ?d_0045e6e0@@YAXXZ
unsigned char *PointerPayloadGetterThunk::getFourthPayload() const
{
    return base + 16;
}

struct PointerPresenceThunk
{
    void *value;

    bool hasValue() const;
    bool hasValueAlternate() const;
};

// ?d_0045e0a0@@YAXXZ
bool PointerPresenceThunk::hasValue() const
{
    return value != 0;
}

// ?d_0045e770@@YAXXZ
bool PointerPresenceThunk::hasValueAlternate() const
{
    return value != 0;
}

struct IntegerArgumentIdentityThunk
{
    int identity(int value) const;
    int identityAlternate(int value) const;
    int identityThird(int value) const;
    int identityFourth(int value) const;
    int identityFifth(int value) const;
};

// ?d_0045e0e0@@YAXXZ
int IntegerArgumentIdentityThunk::identity(int value) const
{
    return value;
}

// ?d_0045e220@@YAXXZ
int IntegerArgumentIdentityThunk::identityAlternate(int value) const
{
    return value;
}

// ?d_0045e360@@YAXXZ
int IntegerArgumentIdentityThunk::identityThird(int value) const
{
    return value;
}

// ?d_0045e410@@YAXXZ
int IntegerArgumentIdentityThunk::identityFourth(int value) const
{
    return value;
}

// ?d_0045e420@@YAXXZ
int IntegerArgumentIdentityThunk::identityFifth(int value) const
{
    return value;
}

struct Offset4IntegerPointerRangeThunk
{
    unsigned char padding[4];
    int *beginPointer;
    int *endPointer;

    int *begin() const;
    int size() const;
    int sizeAlternate() const;
};

// ?begin@Offset4IntegerPointerRangeThunk@@QBEPAHXZ
int *Offset4IntegerPointerRangeThunk::begin() const
{
    return beginPointer;
}

// ?d_0045e370@@YAXXZ
int Offset4IntegerPointerRangeThunk::size() const
{
    return endPointer - beginPointer;
}

// ?d_0045e4e0@@YAXXZ
int Offset4IntegerPointerRangeThunk::sizeAlternate() const
{
    return endPointer - beginPointer;
}

int integerIdentity(int value)
{
    return value;
}

unsigned char *pointerPlusEight(unsigned char *value)
{
    return value + 8;
}

unsigned char *pointerPlusFour(unsigned char *value)
{
    return value + 4;
}

unsigned char *pointerPlusTwelve(unsigned char *value)
{
    return value + 12;
}

unsigned char *pointerPlusTwelveAlternate(unsigned char *value)
{
    return value + 12;
}

unsigned char *pointerPlusSixteen(unsigned char *value)
{
    return value + 16;
}

unsigned char *pointerPlusSixteenAlternate(unsigned char *value)
{
    return value + 16;
}

unsigned char *pointerPlusSixteenThird(unsigned char *value)
{
    return value + 16;
}

unsigned char *__stdcall pointerIdentityStdcall(unsigned char *value)
{
    return value;
}

bool pointedIntegersDiffer(const int *left, const int *right)
{
    return *left != *right;
}

bool pointedIntegersDifferAlternate(const int *left, const int *right)
{
    return *left != *right;
}

bool pointedIntegersDifferThird(const int *left, const int *right)
{
    return *left != *right;
}

bool pointedIntegersEqual(const int *left, const int *right)
{
    return *left == *right;
}

bool pointedIntegersEqualAlternate(const int *left, const int *right)
{
    return *left == *right;
}

bool pointedIntegersEqualThird(const int *left, const int *right)
{
    return *left == *right;
}

struct FluentIntegerBooleanCopyThunk
{
    int integerValue;
    bool booleanValue;

    FluentIntegerBooleanCopyThunk *copyFrom(const int *integerSource, const bool *booleanSource);
};

// ?d_0045e500@@YAXXZ
FluentIntegerBooleanCopyThunk *FluentIntegerBooleanCopyThunk::copyFrom(const int *integerSource, const bool *booleanSource)
{
    integerValue = *integerSource;
    booleanValue = *booleanSource;
    return this;
}

struct ZeroValueBaseThunk
{
    int value;

    ZeroValueBaseThunk() : value(0) {}
};

struct VirtualZeroDerivedThunk : ZeroValueBaseThunk
{
    virtual ~VirtualZeroDerivedThunk();

    VirtualZeroDerivedThunk();
};

// ?d_0045e520@@YAXXZ
VirtualZeroDerivedThunk::VirtualZeroDerivedThunk()
{
}

struct VirtualZeroDerivedAlternateThunk : ZeroValueBaseThunk
{
    virtual ~VirtualZeroDerivedAlternateThunk();

    VirtualZeroDerivedAlternateThunk();
};

// ?d_0045e570@@YAXXZ
VirtualZeroDerivedAlternateThunk::VirtualZeroDerivedAlternateThunk()
{
}

struct VirtualZeroDerivedThirdThunk : ZeroValueBaseThunk
{
    virtual ~VirtualZeroDerivedThirdThunk();

    VirtualZeroDerivedThirdThunk();
};

// ?d_0045e5c0@@YAXXZ
VirtualZeroDerivedThirdThunk::VirtualZeroDerivedThirdThunk()
{
}

struct FluentIntegerPairSetterThunk
{
    int first;
    int second;

    FluentIntegerPairSetterThunk *setValues(int firstValue, int secondValue);
    FluentIntegerPairSetterThunk *setValuesAlternate(int firstValue, int secondValue);
    FluentIntegerPairSetterThunk *setValuesThird(int firstValue, int secondValue);
    FluentIntegerPairSetterThunk *setValuesFourth(int firstValue, int secondValue);
    FluentIntegerPairSetterThunk *setValuesFifth(int firstValue, int secondValue);
    FluentIntegerPairSetterThunk *setValuesSixth(int firstValue, int secondValue);
    FluentIntegerPairSetterThunk *copyFrom(const FluentIntegerPairSetterThunk *other);
    FluentIntegerPairSetterThunk *copyFromAlternate(const FluentIntegerPairSetterThunk *other);
    FluentIntegerPairSetterThunk *copyFromThird(const FluentIntegerPairSetterThunk *other);
    FluentIntegerPairSetterThunk *copyFromFourth(const FluentIntegerPairSetterThunk *other);
};

// ?d_0045e160@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
    return this;
}

// ?d_0045e180@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::setValuesAlternate(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
    return this;
}

// ?d_0045e1a0@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::setValuesThird(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
    return this;
}

// ?d_0045e9f0@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::setValuesFourth(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
    return this;
}

// ?d_0045ea10@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::setValuesFifth(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
    return this;
}

// ?d_0045ea30@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::setValuesSixth(int firstValue, int secondValue)
{
    first = firstValue;
    second = secondValue;
    return this;
}

// ?d_0045e3d0@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::copyFrom(const FluentIntegerPairSetterThunk *other)
{
    first = other->first;
    second = other->second;
    return this;
}

// ?d_0045e3f0@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::copyFromAlternate(const FluentIntegerPairSetterThunk *other)
{
    first = other->first;
    second = other->second;
    return this;
}

// ?d_0045e430@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::copyFromThird(const FluentIntegerPairSetterThunk *other)
{
    first = other->first;
    second = other->second;
    return this;
}

// ?d_0045e450@@YAXXZ
FluentIntegerPairSetterThunk *FluentIntegerPairSetterThunk::copyFromFourth(const FluentIntegerPairSetterThunk *other)
{
    first = other->first;
    second = other->second;
    return this;
}

struct SingleIntegerZeroConstructorThunk
{
    int value;

    SingleIntegerZeroConstructorThunk();
};

// ?d_0045e110@@YAXXZ
SingleIntegerZeroConstructorThunk::SingleIntegerZeroConstructorThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorAlternateThunk
{
    int value;

    SingleIntegerZeroConstructorAlternateThunk();
};

// ?d_0045e950@@YAXXZ
SingleIntegerZeroConstructorAlternateThunk::SingleIntegerZeroConstructorAlternateThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorThirdThunk
{
    int value;

    SingleIntegerZeroConstructorThirdThunk();
};

// ?d_0045f3e0@@YAXXZ
SingleIntegerZeroConstructorThirdThunk::SingleIntegerZeroConstructorThirdThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorFourthThunk
{
    int value;

    SingleIntegerZeroConstructorFourthThunk();
};

// ?d_004679a0@@YAXXZ
SingleIntegerZeroConstructorFourthThunk::SingleIntegerZeroConstructorFourthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorFifthThunk
{
    int value;

    SingleIntegerZeroConstructorFifthThunk();
};

// ?d_00466150@@YAXXZ
SingleIntegerZeroConstructorFifthThunk::SingleIntegerZeroConstructorFifthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorSixthThunk
{
    int value;

    SingleIntegerZeroConstructorSixthThunk();
};

// ?d_00466170@@YAXXZ
SingleIntegerZeroConstructorSixthThunk::SingleIntegerZeroConstructorSixthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorSeventhThunk
{
    int value;

    SingleIntegerZeroConstructorSeventhThunk();
};

// ?d_004661a0@@YAXXZ
SingleIntegerZeroConstructorSeventhThunk::SingleIntegerZeroConstructorSeventhThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorEighthThunk
{
    int value;

    SingleIntegerZeroConstructorEighthThunk();
};

// ?d_004661f0@@YAXXZ
SingleIntegerZeroConstructorEighthThunk::SingleIntegerZeroConstructorEighthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorNinthThunk
{
    int value;

    SingleIntegerZeroConstructorNinthThunk();
};

// ?d_00466af0@@YAXXZ
SingleIntegerZeroConstructorNinthThunk::SingleIntegerZeroConstructorNinthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorTenthThunk
{
    int value;

    SingleIntegerZeroConstructorTenthThunk();
};

// ?d_00466b70@@YAXXZ
SingleIntegerZeroConstructorTenthThunk::SingleIntegerZeroConstructorTenthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorEleventhThunk
{
    int value;

    SingleIntegerZeroConstructorEleventhThunk();
};

// ?d_00466ba0@@YAXXZ
SingleIntegerZeroConstructorEleventhThunk::SingleIntegerZeroConstructorEleventhThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorTwelfthThunk
{
    int value;

    SingleIntegerZeroConstructorTwelfthThunk();
};

// ?d_00466bf0@@YAXXZ
SingleIntegerZeroConstructorTwelfthThunk::SingleIntegerZeroConstructorTwelfthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorThirteenthThunk
{
    int value;

    SingleIntegerZeroConstructorThirteenthThunk();
};

// ?d_00467700@@YAXXZ
SingleIntegerZeroConstructorThirteenthThunk::SingleIntegerZeroConstructorThirteenthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorFourteenthThunk
{
    int value;

    SingleIntegerZeroConstructorFourteenthThunk();
};

// ?d_00467810@@YAXXZ
SingleIntegerZeroConstructorFourteenthThunk::SingleIntegerZeroConstructorFourteenthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorFifteenthThunk
{
    int value;

    SingleIntegerZeroConstructorFifteenthThunk();
};

// ?d_00467860@@YAXXZ
SingleIntegerZeroConstructorFifteenthThunk::SingleIntegerZeroConstructorFifteenthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorSixteenthThunk
{
    int value;

    SingleIntegerZeroConstructorSixteenthThunk();
};

// ?d_00472630@@YAXXZ
SingleIntegerZeroConstructorSixteenthThunk::SingleIntegerZeroConstructorSixteenthThunk() :
    value(0)
{
}

struct SingleIntegerZeroConstructorSeventeenthThunk
{
    int value;

    SingleIntegerZeroConstructorSeventeenthThunk();
};

// ?d_00472810@@YAXXZ
SingleIntegerZeroConstructorSeventeenthThunk::SingleIntegerZeroConstructorSeventeenthThunk() :
    value(0)
{
}

struct FluentNoOpThunk
{
    FluentNoOpThunk *ignore(int unused);
    FluentNoOpThunk *ignoreAlternate(int unused);
    FluentNoOpThunk *ignoreThird(int unused);
    FluentNoOpThunk *ignoreFourth(int unused);
    FluentNoOpThunk *ignoreFifth(int unused);
    FluentNoOpThunk *ignoreSixth(int unused);
    FluentNoOpThunk *ignoreSeventh(int unused);
    FluentNoOpThunk *ignoreEighth(int unused);
    FluentNoOpThunk *ignoreNinth(int unused);
    FluentNoOpThunk *ignoreTenth(int unused);
    FluentNoOpThunk *ignoreEleventh(int unused);
    FluentNoOpThunk *ignoreTwelfth(int unused);
    FluentNoOpThunk *ignoreThirteenth(int unused);
    FluentNoOpThunk *ignoreFourteenth(int unused);
    FluentNoOpThunk *ignoreFifteenth(int unused);
    FluentNoOpThunk *ignoreSixteenth(int unused);
    FluentNoOpThunk *ignoreSeventeenth(int unused);
    FluentNoOpThunk *ignoreEighteenth(int unused);
    FluentNoOpThunk *ignoreNineteenth(int unused);
    FluentNoOpThunk *ignoreTwentieth(int unused);
    FluentNoOpThunk *ignoreTwentyFirst(int unused);
    FluentNoOpThunk *ignoreTwentySecond(int unused);
    FluentNoOpThunk *ignoreTwentyThird(int unused);
    FluentNoOpThunk *ignoreTwentyFourth(int unused);
    FluentNoOpThunk *ignoreTwentyFifth(int unused);
    FluentNoOpThunk *ignoreTwentySixth(int unused);
    FluentNoOpThunk *ignoreTwentySeventh(int unused);
    FluentNoOpThunk *ignoreTwentyEighth(int unused);
    FluentNoOpThunk *ignoreTwentyNinth(int unused);
    FluentNoOpThunk *ignoreThirtieth(int unused);
    FluentNoOpThunk *ignoreThirtyFirst(int unused);
    FluentNoOpThunk *ignoreThirtySecond(int unused);
    FluentNoOpThunk *ignoreThirtyThird(int unused);
    FluentNoOpThunk *ignoreThirtyFourth(int unused);
    FluentNoOpThunk *ignoreThirtyFifth(int unused);
    FluentNoOpThunk *ignoreThirtySixth(int unused);
    FluentNoOpThunk *ignoreThirtySeventh(int unused);
    FluentNoOpThunk *ignoreThirtyEighth(int unused);
    FluentNoOpThunk *ignoreThirtyNinth(int unused);
    FluentNoOpThunk *ignoreFortieth(int unused);
    FluentNoOpThunk *ignoreFortyFirst(int unused);
};

// ?d_0045e120@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignore(int)
{
    return this;
}

// ?d_0045e130@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreAlternate(int)
{
    return this;
}

// ?d_0045e140@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThird(int)
{
    return this;
}

// ?d_0045e200@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreFourth(int)
{
    return this;
}

// ?d_0045e2f0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreFifth(int)
{
    return this;
}

// ?d_0045e300@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreSixth(int)
{
    return this;
}

// ?d_0045e310@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreSeventh(int)
{
    return this;
}

// ?d_0045e320@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreEighth(int)
{
    return this;
}

// ?d_0045e330@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreNinth(int)
{
    return this;
}

// ?d_0045e340@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTenth(int)
{
    return this;
}

// ?d_0045e350@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreEleventh(int)
{
    return this;
}

// ?d_00466180@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwelfth(int)
{
    return this;
}

// ?d_00466190@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirteenth(int)
{
    return this;
}

// ?d_004661b0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreFourteenth(int)
{
    return this;
}

// ?d_004661c0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreFifteenth(int)
{
    return this;
}

// ?d_004661d0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreSixteenth(int)
{
    return this;
}

// ?d_004661e0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreSeventeenth(int)
{
    return this;
}

// ?d_00466200@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreEighteenth(int)
{
    return this;
}

// ?d_00466490@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreNineteenth(int)
{
    return this;
}

// ?d_004664a0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentieth(int)
{
    return this;
}

// ?d_004664b0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentyFirst(int)
{
    return this;
}

// ?d_004664c0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentySecond(int)
{
    return this;
}

// ?d_004664d0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentyThird(int)
{
    return this;
}

// ?d_004664e0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentyFourth(int)
{
    return this;
}

// ?d_004664f0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentyFifth(int)
{
    return this;
}

// ?d_00466500@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentySixth(int)
{
    return this;
}

// ?d_00466510@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentySeventh(int)
{
    return this;
}

// ?d_00466520@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentyEighth(int)
{
    return this;
}

// ?d_00466530@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreTwentyNinth(int)
{
    return this;
}

// ?d_00466540@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtieth(int)
{
    return this;
}

// ?d_00466550@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtyFirst(int)
{
    return this;
}

// ?d_00466560@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtySecond(int)
{
    return this;
}

// ?d_00470a00@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtyThird(int)
{
    return this;
}

// ?d_00470a10@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtyFourth(int)
{
    return this;
}

// ?d_004729d0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtyFifth(int)
{
    return this;
}

// ?d_00472a10@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtySixth(int)
{
    return this;
}

// ?d_00472a40@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtySeventh(int)
{
    return this;
}

// ?d_00472a70@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtyEighth(int)
{
    return this;
}

// ?d_00472ae0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreThirtyNinth(int)
{
    return this;
}

// ?d_00472af0@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreFortieth(int)
{
    return this;
}

// ?d_00472b00@@YAXXZ
FluentNoOpThunk *FluentNoOpThunk::ignoreFortyFirst(int)
{
    return this;
}

// ?Rva0045E720Noop@@YAXXZ
// Retail 0x0045E720 contains only ret. The carved boundary and generated thunk
// caller prove an empty cdecl body, but no evidence identifies its owner.
void Rva0045E720Noop()
{
}
