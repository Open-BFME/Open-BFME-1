// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" __declspec(dllimport) double __cdecl ceil(double);

class Drawable
{
public:
    void updateDrawableSupplyStatus(int, int);
};

class SupplyWarehouseObject
{
public:
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
    virtual Drawable *getDrawable();
};

struct SupplyWarehouseModuleData
{
    unsigned char padding[0x10];
    int startingBoxesData;
};

struct SupplyWarehouseGlobalData
{
    unsigned char padding[0xb24];
    int baseValuePerSupplyBox;
};

extern SupplyWarehouseGlobalData *TheSupplyWarehouseGlobalData;

class SupplyWarehouseDockUpdate
{
public:
    void setCashValue(int);

private:
    unsigned int vtable;
    SupplyWarehouseModuleData *moduleData;
    SupplyWarehouseObject *object;
    unsigned char padding[0x7c];
    int boxesStored;
};

// ?setCashValue@SupplyWarehouseDockUpdate@@QAEXH@Z
void SupplyWarehouseDockUpdate::setCashValue(int cashValue)
{
    boxesStored = static_cast<int>(ceil(cashValue / static_cast<double>(TheSupplyWarehouseGlobalData->baseValuePerSupplyBox)));
    Drawable *draw = object->getDrawable();
    if (draw)
        draw->updateDrawableSupplyStatus(moduleData->startingBoxesData, boxesStored);
}
