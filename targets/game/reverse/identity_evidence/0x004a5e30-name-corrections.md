# 0x004A5E30 bank-name corrections

The matched `ControlBar::switchToContext` body at VA `0x0049E780` calls ILT `0x0000D495`, which targets `0x004A5E30` with an `Object *` and a `Bool`. This proves the landed body's owner and arguments. It does not prove the helper types that the banked attempt declared around its calls.

## The banked helper names were local adapters

The banked source at `targets/game/reverse/attempts/0x004a5e30.cpp` declares `BfmePopulate...` views and redirects their methods to retail ILT entries. The retail targets and existing ledger rows identify several of those methods under other owners.

| Banked helper | Retail target and ledger identity | What the evidence shows |
| --- | --- | --- |
| `BfmePopulateButtonImageView` | ILT `0x0002A7ED` targets `0x0049C380`, matched as `BFMERetailCommandButton::setButtonImage` | The target belongs to the matched command-button implementation. The new `Rva00478390` wrapper is a separate window call, so the name checker paired unrelated declarations. |
| `BfmePopulateClearAt004B1720` | ILT `0x00033F19` targets `0x004B1720`, matched as generated `Gen_004B1720::bfmeClear` | The target keeps its generated name because the ledger proves no real owner. |
| `BfmePopulateCommandButtonLookupView` | ILT `0x00003F80` targets `0x0049C590`, matched as `CommandSet::getCommandButton` | The wrapper name does not identify the target's owner. |
| `BfmePopulateCommandButtonView` | ILT `0x00006938` targets anonymous body `0x0049BA80`; ILT `0x00001947` targets generated body `0x0049C4B0` | The bank put a layout view and two call wrappers in one class. The landed source names each target or layout separately. |
| `BfmePopulateCommandSetLookupView` | ILT `0x00048CCA` targets `0x004A0340`, matched as `ControlBar::findCommandSet` | The retail owner is `ControlBar`. |
| `BfmePopulateCommandSetOverride` and `BfmePopulateObjectOverrideView` | ILT `0x0002BF85` targets `0x001CAF20` | The ledger currently calls this body `BfmeHostERH::bfmeGoERH` with an integer result. This caller reads a string-like object at returned `EAX+0x2C`. The conflicting claims do not prove an override getter or its result type. |
| `BfmePopulateCommandTextView` | ILT `0x00046C18` targets address-derived body `0x0013E4D0` | The ledger proves the address and ABI, but it does not name a command-text class. |
| `BfmePopulateControlCommandView` | ILT `0x00015DA7` targets `0x0049EDE0`, matched as `ControlBar::setControlCommand` | The target has a real matched owner. |
| `BfmePopulateGameWindowCloseView` | ILT `0x00027F2A` targets `0x00478390`, matched as `GameWindow::winHide` | The bank's `bfmeClose` label conflicts with the matched target name. |
| `BfmePopulateGlobalsView` | ILT `0x0003367C` targets address-derived thunk `0x0058C040`; ILT `0x0001F0D7` targets address-derived body `0x005976B0` | Two unrelated targets do not establish a shared globals class. |
| `BfmePopulateObjectStore` | ILT `0x0004A66F` targets anonymous body `0x000FA800`; ILT `0x00002135` targets matched `BfmeVecVLH::rva000F9670` | The targets do not establish an object-store class. |
| `BfmePopulatePlayerListView` | ILT `0x00003A85` targets `0x000DF810`, matched as `PlayerList::isLocalAlliedWith` | The helper is an adapter for a real `PlayerList` method. `PlayerList+0x0C` is `m_local`, and the landed source calls `getLocalPlayer()`. |
| `BfmePopulateRallyPointView` | ILT `0x0000D436` targets `0x0049DF00`, matched as `ControlBar::showRallyPoint` | The target has a real matched owner. |

The bank also declared views for `ControlBar`, `Object`, `ContainModuleInterface`, `OpenContain`, and `ExitInterface`. The new source uses the witnessed `m_contain` name at BFME offset `0x1FC` in an address-derived view, because the Zero Hour `Object::getContain()` accessor reads a different offset. It calls `asOpenContain()` for containment slot zero and uses the `BFMERetailExitVTable::getRallyPoint()` slot established in `AIDock.cpp`. The body still calls unnamed containment slot `0xB4` through an address-derived view because the reference interface does not name that BFME slot.

## The old field labels lack witnesses

`name_oracle.py` reports no member witness for `CommandButton+0x68`, `+0xA0`, `+0x14D`, `+0x152`, or `+0x153`. The bank called those fields `m_text`, `m_specialIndex`, `field14d`, `field152`, and `field153`. The landed source uses offset labels for the unknown fields. The oracle does witness `CommandButton+0x14` as `m_upgradeTemplate` and `+0x34` as `m_specialPower`, and the source keeps both names.

The oracle reports no witness for `Player+0x684`, `ControlBar+0x100`, or `+0x150`. It returns Zero Hour hints for `ControlBar+0x28` and `+0x2F0`, but marks both as hints rather than BFME witnesses. The landed source therefore records these fields by offset. The oracle does witness `Object+0x1FC` as `m_contain` and `PlayerList+0x0C` as `m_local`.

## The corrections apply to these source snapshots

The name checker pairs identifiers across the deleted bank and the landed source. Some pairs are false because the bank grouped several adapters into one class, or because one local adapter disappeared when the source started calling an already matched function. Other pairs replace an unsupported field guess with an offset label. The entries in `name_corrections.json` bind each pairing to the exact before and after source hashes.
