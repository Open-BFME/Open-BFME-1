# ScriptActions command on nearest enemy unit: RVA 0x002F9FF0

Retail executeAction switch table at VA 0x0070D6A0, index424, dispatches arm RVA0x00308EDF; its call at RVA0x00308EFC to ILT RVA0x00040D68 jumps to this body. The repository game/GameEngine/Source/GameLogic/ScriptEngine/script_engine.cpp:3172-3181 template names NAMED_USE_COMMANDBUTTON_ON_NEAREST_ENEMY_UNIT and supplies two string parameters. This establishes action behavior, not the original C++ method spelling. The old bank's doNamedUseCommandButtonOnNearestEnemyUnit spelling has no exact source/caller witness, so this recovery uses the honest address-derived owner Rva002F9FF0::method. The provisional uncommitted named ledger row is retired for that reason.

The retail function ends with RET8 at +0x249, followed by INT3 at +0x24C: extent588 bytes. Calls and the two stack parameters establish thiscall(const AsciiString&,const AsciiString&).

The 24-byte kind mask is addressed at ESP+0x1C. Retail stores 0x200000 at +0x20 (word1 bit21), 0x1000000 at +0x24 (word2 bit24), and2 at +0x2C (word4 bit1); its bits are53,88,129. Earlier retained bank bit97 was incorrect. No semantic flag name is inferred from these constants.

The matched native kind constructor at RVA0x000C3DD0 copies two24-byte references into the56-byte derived PartitionFilter object. The temporary chain constructs kind before valid-target, then links kind->map, valid->kind, player->valid. This is independent of adjacency and agrees with actual caller instructions.

Valid-target constructor ILT RVA0x0003A5AD routes to RVA0x001ED510. Independent decoding through RET16 at RVA0x001ED53B finds only argument loads, field/vptr stores and return: no calls, branches, allocation or exception route. Its TU-scoped nonthrowing declaration is justified by that implementation, and restores the retail EH transition without an extra transient state4 store. Fields are next+4, source+8, button+C, bool+10, sourceType+14; vtable VA0x010A1A5C.

Final intended-source strict gate passes all588 bytes modulo31 relocation operands, including10 DIR32 references. The byte proof supplements this dispatcher, ABI, extent, mask and constructor evidence; it does not supply the semantic identity by itself.
