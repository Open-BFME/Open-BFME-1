# GameLogic thiscall member at 0x00383440 (was ?bfmeGo1010B@@YGXPAVBfmeThing1010@@@Z)

The 50-byte body at 0x00383440 (RET 4 at +0x2F) was matched as a `__stdcall` free
function, `?bfmeGo1010B@@YGXPAVBfmeThing1010@@@Z`. The bytes are the same for a
thiscall member that ignores ECX, so the byte match could not tell the two apart.
The call site can.

- **The only caller is Object::~Object at 0x001D4010.** At +0x15E it runs
  `mov ecx,[0x012F0898]; push esi; call 0x0043B1B0`, and ILT 0x0003B1B0 jumps to
  0x00383440. 0x012F0898 is TheGameLogic (dir32_addresses.csv records
  `?TheGameLogic@@3PAVGameLogic@@A` there). A stdcall callee would not need ECX
  loaded, so the call is a GameLogic thiscall member with one stack argument,
  the Object.
- **The body matches Zero Hour's `GameLogic::sendObjectDestroyed` statement for
  statement** (GeneralsMD GameLogic.cpp:4158):
  - return when TheGameClient (0x012F1464) is NULL;
  - call the Object's vftable slot 10 (`+0x28`), which is
    `?getDrawable@Object@@UBEPAVDrawable@@XZ` by the object.h slot map;
  - hand a non-null drawable to TheGameClient's slot 24 (`+0x60`);
  - call ILT 0x0001AA0A with NULL on the Object. That ILT reaches the matched
    `?friend_bindToDrawable@Object@@QAEXPAVDrawable@@@Z` (0x001C96B0).
- **Its caller position also matches Zero Hour.** In `Object::~Object` it sits
  between `TheRadar->removeObject(this)` and `setTeam(NULL)`, where Zero Hour
  calls `TheGameLogic->sendObjectDestroyed(this)`.

The real name is not claimed here. `?sendObjectDestroyed@GameLogic@@QAEXPAVObject@@@Z`
is already matched at 0x0038D090, whose body has Zero Hour's `destroyObject`
shape instead: a null test, two flag bytes, a find over the list at +0x15C, then
push_back. Until those two rows are reconciled, this body keeps an address-derived
name, `?rva00383440@GameLogic@@QAEXPAVObject@@@Z`.

With the old name retired, two pins that existed only for its source are unused:
- `?bfmeFinish1010B@BfmeThing1010@@QAEXH@Z` at ILT 0x0001AA0A, which is
  friend_bindToDrawable's ILT;
- `?g_bfmeSinkB1010@@3PAVBfmeSinkB1010@@A` at 0x00EF1464, which is TheGameClient.

Probe: 50/50 bytes and 3 relocation sites, exact outside the relocation slots.
