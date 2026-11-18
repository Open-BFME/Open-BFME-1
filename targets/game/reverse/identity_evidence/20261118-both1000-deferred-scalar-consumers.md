# Deferred primitive-header adoption

GameSpyStagingRoom_ctor.cpp remains on its original private typedefs. Its
original source passes both existing rows. Adding the full narrow ScalarTypes
header renumbers the compiler's cleanup labels, and the normal gate cannot
resolve the existing dup_00C41408 row's $L2038 label in that candidate.
Other labels the gate proves by unwind state are recognized independently.
No manual EH label, alias or pin is added, and no verifier or baseline changes.
The whole unbanked cohort was restored before selecting the other consumers.
This file and the failed native experiment count as zero completed tasks.
Revisit only when native funclet identity evidence or the consumer context changes.

## Additional consumers with the same native refusal

`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehaviorCalcFlightPath.cpp`: `?dup_00C0A890@@YAXXZ` remains at its original definition. The original source passes the native gate; the proposed header causes a compiler-label binding the native verifier cannot establish. No new label or alias is forced; zero task credit.

## Additional consumers with the same native refusal

`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineIsAudioComplete.cpp`: `?dup_00C19013@@YAXXZ` remains at its original definition. The original source passes the native gate; the proposed header causes a compiler-label binding the native verifier cannot establish. No new label or alias is forced; zero task credit.

`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineIsSpeechComplete.cpp`: `?dup_00C19053@@YAXXZ` remains at its original definition. The original source passes the native gate; the proposed header causes a compiler-label binding the native verifier cannot establish. No new label or alias is forced; zero task credit.

`game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarViewBoxRva006C0FA0.cpp`: `?dup_00C49C80@@YAXXZ` remains at its original definition. The original source passes the native gate; the proposed header causes a compiler-label binding the native verifier cannot establish. No new label or alias is forced; zero task credit.
