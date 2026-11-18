# Current native BFME1 link measurement

This is a new local full-image measurement, not a newly discovered hosted run.
Its immutable, published source input is`6c4dd9e6500d1db23de243d58c406edc7245a78b`. The latest hosted
manual followup at the initial check remains44135612880, source30f455d61089b72c34627f9d8c16a4d87f142d6d.

The unmodified native tools compile current inputs, byte-check1872 data rows,
run the real linker, validate input currency, perform MAP selection and write
the history/status/queue. A successful link-measurement process is not a game
start or a runtime correctness claim. All counters below are project-wide and
include other contributors; they are not credited exclusively to this session.

|Metric|Previous local snapshot|This local snapshot|Change|
|---|---:|---:|---:|
|objects|22,994|22,994|+0|
|files|22,577|22,577|+0|
|files_linked|15,627|15,654|+27|
|linked_bytes|3,282,910|3,286,134|+3,224|
|linked_authored|3,011,806|3,015,030|+3,224|
|unresolved|88,649|88,642|-7|
|duplicates|1,883|1,789|-94|
|comdat_conflicts|6,871|6,763|-108|
|blocking_names|87,892|87,885|-7|
|addresses|71|71|+0|

Previous input:`d4dbfb67b7`; new input:`6c4dd9e6500d1db23de243d58c406edc7245a78b`.
The preceding500 source/type operations preserved234909 distinct row bytes
and added no authored function bytes. Their result is documented separately;
this measurement does not turn source maintenance into exclusive byte credit.

The upstream reference had moved backward to7209b9e7397; the separate supporting
checkpoint advances it to official7115ec08e6a3714f29a5260bbbcabe0f05262e82.
The refreshed BFME2 scan covers53264 donor bodies and790672 placements;
ambiguous/truncated/conflicting matches remain unsuitable for unique recovery.
The AddDecal compile still has two object-exact-multi placements. No body is
imported from that ambiguity. New work is selected using the refreshed queues
and BFME1 identity/ABI/retail proof. No native verifier, baseline or pin changes
are introduced by this report.

The next500 requested tasks start after cumulative source-operation1081.
This reference/measurement bookkeeping is excluded from that count. No crash,
RAM/leak,64-bit,multicore,FPS or game-start result is inferred. The PC stays on.
