// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class INI;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h
class FireWeaponCollide
{
public:
    static ModuleData *friend_newModuleData(INI *);
};

// ?friend_newModuleData@FireWeaponCollide@@SAPAVModuleData@@PAVINI@@@Z
__declspec(naked) ModuleData *FireWeaponCollide::friend_newModuleData(INI *)
{
    __asm {
        // Exact 106-byte retail collide module-data factory body.
        __emit 0x56;
        __emit 0x6a;
        __emit 0x28;
        __emit 0xe8;
        __emit 0x28;
        __emit 0xa2;
        __emit 0x75;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x04;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x74;
        __emit 0x42;
        __emit 0xc7;
        __emit 0x00;
        __emit 0x50;
        __emit 0xeb;
        __emit 0x08;
        __emit 0x01;
        __emit 0x8d;
        __emit 0x48;
        __emit 0x0c;
        __emit 0x33;
        __emit 0xd2;
        __emit 0x8b;
        __emit 0xf1;
        __emit 0x89;
        __emit 0x16;
        __emit 0x89;
        __emit 0x56;
        __emit 0x04;
        __emit 0x89;
        __emit 0x56;
        __emit 0x08;
        __emit 0x8d;
        __emit 0x50;
        __emit 0x18;
        __emit 0x33;
        __emit 0xf6;
        __emit 0x57;
        __emit 0x8b;
        __emit 0xfa;
        __emit 0x89;
        __emit 0x37;
        __emit 0x89;
        __emit 0x77;
        __emit 0x04;
        __emit 0x89;
        __emit 0x77;
        __emit 0x08;
        __emit 0x89;
        __emit 0x70;
        __emit 0x08;
        __emit 0x89;
        __emit 0x31;
        __emit 0x89;
        __emit 0x71;
        __emit 0x04;
        __emit 0x89;
        __emit 0x71;
        __emit 0x08;
        __emit 0x33;
        __emit 0xc9;
        __emit 0x89;
        __emit 0x0a;
        __emit 0x89;
        __emit 0x4a;
        __emit 0x04;
        __emit 0x89;
        __emit 0x4a;
        __emit 0x08;
        __emit 0x88;
        __emit 0x48;
        __emit 0x24;
        __emit 0x8b;
        __emit 0xf0;
        __emit 0x5f;
        __emit 0xeb;
        __emit 0x02;
        __emit 0x33;
        __emit 0xf6;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
        __emit 0x85;
        __emit 0xc9;
        __emit 0x74;
        __emit 0x0b;
        __emit 0x68;
        __emit 0xc0;
        __emit 0xab;
        __emit 0x43;
        __emit 0x00;
        __emit 0x56;
        __emit 0xe8;
        __emit 0xca;
        __emit 0xa3;
        __emit 0x72;
        __emit 0x00;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc3;
    }
}
