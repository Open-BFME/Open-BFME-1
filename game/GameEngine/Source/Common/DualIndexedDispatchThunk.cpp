extern int DualIndexedDispatchFirst;
extern int DualIndexedDispatchSecond;
extern int DualIndexedDispatchSixFirst;
extern int DualIndexedDispatchSixSecond;

extern void __cdecl dispatchIndexedValue(
    void *target,
    int index,
    void *value,
    int count,
    int *first,
    int *second);

struct DualIndexedDispatchThunk
{
    unsigned char padding[0x54];
    void *value;

    void dispatch(void *target);
    void dispatchSix(void *target);
};

// ?d_00643c10@@YAXXZ
void DualIndexedDispatchThunk::dispatch(void *target)
{
    dispatchIndexedValue(target, 1, value, 2, &DualIndexedDispatchFirst, &DualIndexedDispatchSecond);
    dispatchIndexedValue(target, 2, value, 2, &DualIndexedDispatchFirst, &DualIndexedDispatchSecond);
}

// ?d_00643bc0@@YAXXZ
void DualIndexedDispatchThunk::dispatchSix(void *target)
{
    dispatchIndexedValue(target, 1, value, 6, &DualIndexedDispatchSixFirst, &DualIndexedDispatchSixSecond);
    dispatchIndexedValue(target, 2, value, 6, &DualIndexedDispatchSixFirst, &DualIndexedDispatchSixSecond);
}
