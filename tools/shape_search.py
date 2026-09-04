#!/usr/bin/env python3
"""Bounded MSVC shape search over explicit, reviewable source alternatives.

choices.json is [{"before":"unique source text", "after":["alternative", ...]}].
The unchanged source is always trial zero. Agents supply the hypotheses; this
tool compiles their finite combinations and stops at a trial budget or plateau.
Scores mask relocations and are NOT acceptance. Review the selected source,
restore it at its intended Code/ path, then run the ordinary add_match gates.
"""
import argparse
import hashlib
import itertools
import json
from pathlib import Path
import re
import time
import uuid

import build
from experiment_store import compile_cached, record_result
from probe import masked


def variants(source, choices):
    occupied = []
    for choice in choices:
        before = choice["before"]
        if not before or source.count(before) != 1:
            raise ValueError("each 'before' must occur exactly once in the original source")
        if not isinstance(choice["after"], list) or not all(isinstance(s, str) for s in choice["after"]):
            raise ValueError("'after' must be a list of source alternatives")
        start = source.index(before)
        end = start + len(before)
        if any(start < hi and end > lo for lo, hi in occupied):
            raise ValueError("overlapping edits must be expressed as one choice")
        occupied.append((start, end))
    seen = set()
    for combination in itertools.product(*([c["before"]] + c["after"] for c in choices)):
        candidate = source
        for (start, end), replacement in sorted(zip(occupied, combination), reverse=True):
            candidate = candidate[:start] + replacement + candidate[end:]
        if re.search(r"\b(?:__asm|_asm|__emit|_emit|naked)\b", candidate):
            raise ValueError("shape search accepts C++ only; no assembly injection")
        key = hashlib.sha256(candidate.encode()).hexdigest()
        if key not in seen:
            seen.add(key)
            yield key, candidate


def scratch_source(text, source):
    # Preserve local quoted includes without editing an active Code/ source.
    # A final recompile at the intended path is mandatory (__FILE__, anonymous
    # namespace mangling and relative include chains may depend on that path).
    def include(match):
        path = (source.parent / match[1]).resolve()
        return f'#include "{path.as_posix()}"' if path.exists() else match[0]
    return re.sub(r'^\s*#\s*include\s*"([^"\n]+)"', include, text, flags=re.M)


def evaluate(source, symbol, rva, target):
    obj, reused = compile_cached(source)
    data, relocs = build.read_object_symbol_bytes(obj, symbol)
    data = bytes(data)
    result = record_result(source, symbol, rva, target, data, relocs)
    left, right = masked(data, relocs), masked(target, relocs)
    extent = max(len(left), len(right))
    equal = sum(a == b for a, b in zip(left, right))
    return dict(score=equal / max(extent, 1), size=len(data), target_size=len(target),
                shape=result["shape"], prior_outcomes=result["seen_before"], cached=reused,
                masked_shape_equal=left == right)


def search(source, symbol, rva, size, choices, max_trials=32, plateau=8, seconds=600,
           evaluator=evaluate):
    if min(max_trials, plateau, seconds, size) <= 0:
        raise ValueError("budgets and target size must be positive")
    original = source.read_text(encoding="utf-8-sig")
    directory = build.ROOT / "build/shape_search" / uuid.uuid4().hex
    directory.mkdir(parents=True)
    (directory / "original.cpp").write_text(original, encoding="utf-8")
    (directory / "choices.json").write_text(json.dumps(choices, indent=2), encoding="utf-8")
    target = build.read_target_bytes(rva, size)
    if len(target) != size:
        raise ValueError("target extent is outside the retail image")
    manifest = dict(source=str(source), symbol=symbol, rva=f"0x{rva:08x}", size=size,
                    target_sha256=hashlib.sha256(target).hexdigest(), trials=[], best=None,
                    acceptance="none: masked shape search only", stop="budget")
    start = time.monotonic()
    stale = 0
    best_score = -1
    shapes = set()
    for number, (key, candidate) in enumerate(itertools.islice(variants(original, choices), max_trials)):
        if time.monotonic() - start >= seconds:
            manifest["stop"] = "time budget (checked between compiles)"
            break
        # One stable compiler input path lets identical sources share a cache.
        trial = directory / f"{number:03d}-{key[:12]}.cpp"
        trial.write_text(candidate, encoding="utf-8")
        scratch = directory / "candidate.cpp"
        scratch.write_text(scratch_source(candidate, source), encoding="utf-8")
        record = dict(number=number, source=trial.name, sha256=key)
        try:
            record.update(evaluator(scratch, symbol, rva, target))
            record["new_shape"] = record["shape"] not in shapes
            shapes.add(record["shape"])
            if record["score"] > best_score:
                best_score = record["score"]
                manifest["best"] = trial.name
                stale = 0
            else:
                stale += 1
        except (Exception, SystemExit) as error:
            record["error"] = str(error)
            stale += 1
        manifest["trials"].append(record)
        (directory / "result.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
        if record.get("masked_shape_equal"):
            manifest["stop"] = "masked shape reached; relocation and identity verification required"
            break
        if stale >= plateau:
            manifest["stop"] = "no improving output"
            break
    else:
        manifest["stop"] = "variants exhausted or trial budget reached"
    manifest["seconds"] = time.monotonic() - start
    (directory / "result.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
    return directory, manifest


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("source", type=Path)
    ap.add_argument("symbol")
    ap.add_argument("rva", type=lambda s: int(s, 16))
    ap.add_argument("--size", type=int, required=True)
    ap.add_argument("--choices", type=Path, required=True)
    ap.add_argument("--max-trials", type=int, default=32)
    ap.add_argument("--plateau", type=int, default=8)
    ap.add_argument("--seconds", type=int, default=600)
    a = ap.parse_args()
    path, result = search(a.source.resolve(), a.symbol, a.rva, a.size,
                          json.loads(a.choices.read_text(encoding="utf-8")),
                          a.max_trials, a.plateau, a.seconds)
    print(f"{len(result['trials'])} trials; {result['stop']}")
    print(f"Best candidate: {path / result['best'] if result['best'] else 'none compiled'}")
    print(f"Evidence: {path / 'result.json'}")


if __name__ == "__main__":
    main()
