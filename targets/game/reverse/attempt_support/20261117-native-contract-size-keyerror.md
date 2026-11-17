# Native class-contract size-key error during header preflight

At baseline `9b5dda721b3`, the unmodified native command
`tools/class_contract.py --class ParticleSystemTemplate --sample 12 --jobs 14`
raised `KeyError: 'size'` instead of returning a class-contract inspection.
This is a tooling failure, not an ABI verdict or an observed game fault.

The 80-row cohort stopped before any source experiment or edit. All 80 owned
reservations were released with their original lease fences. No task was counted.
The family is deferred pending a targeted native-tool investigation. Other
families can proceed only after their own native inspection returns a result,
with the original strict per-source CodeView, complete runtime inventory,
ordinary retail-row gates and selected-provider proofs still required.

The native checker, baseline, headers and shared build inputs are unchanged.
Known identical size-key errors in other families are isolated and deferred;
they never qualify as successful contract checks. Unexpected failures still stop.

Observed native traceback:

```text
Traceback (most recent call last):
  File "W:\OpenBFME\Open-BFME-1\tools\class_contract.py", line 418, in <module>
    sys.exit(main())
             ^^^^^^
  File "W:\OpenBFME\Open-BFME-1\tools\class_contract.py", line 398, in main
    contract = decide(args.name, jobs=args.jobs, sample=args.sample)
               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "W:\OpenBFME\Open-BFME-1\tools\class_contract.py", line 281, in decide
    major_size = collections.Counter(L["size"] for L in good.values()).most_common(1)[0][0] if good else 0
                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "C:\Users\micha\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\Lib\collections\__init__.py", line 607, in __init__
    self.update(iterable, **kwds)
  File "C:\Users\micha\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\Lib\collections\__init__.py", line 699, in update
    _count_elements(self, iterable)
  File "W:\OpenBFME\Open-BFME-1\tools\class_contract.py", line 281, in <genexpr>
    major_size = collections.Counter(L["size"] for L in good.values()).most_common(1)[0][0] if good else 0
                                     ~^^^^^^^^
KeyError: 'size'
```
