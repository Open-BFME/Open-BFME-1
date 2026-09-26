#!/usr/bin/env python3
"""WorldBuilder's explicit, hash-bound recovery and ledger entry point."""

import argparse
from contextlib import contextmanager
import csv
from datetime import datetime, timezone
import hashlib
import io
import json
import os
from pathlib import Path, PurePosixPath
import re
import subprocess
import sys

from ledger_io import atomic_write_bytes
from portable_lock import lock
import target_verify
import worldbuilder_donors
from targets import load_target


FIELDS = ("name", "target_rva", "target_size", "status", "source", "profile", "evidence", "model")


def number(value):
    if isinstance(value, bool) or not isinstance(value, (str, int)):
        raise ValueError(f"expected an integer or integer string, got {value!r}")
    return int(value, 0) if isinstance(value, str) else value


def relative_path(target, value):
    if (not isinstance(value, str) or not value or "\\" in value or ":" in value
            or PurePosixPath(value).is_absolute() or ".." in PurePosixPath(value).parts):
        raise ValueError(f"expected repository-relative path without '..': {value!r}")
    result = (target.root / value).resolve()
    if not result.is_relative_to(target.root):
        raise ValueError(f"path escapes repository: {value}")
    return result


def packet_hash(packet):
    if isinstance(packet, dict):
        packet = {key: value for key, value in packet.items() if key != "packet_sha256"}
    return hashlib.sha256(json.dumps(packet, sort_keys=True, separators=(",", ":"))
                          .encode("utf-8")).hexdigest()


def load_candidates(target):
    target.verify_hash()
    path = target.ledger_root / "candidates.json"
    inventory = json.loads(path.read_text(encoding="utf-8"))
    if (inventory.get("schema_version") != 1
            or inventory.get("target_id") != target.target_id
            or inventory.get("binary_sha256") != target.expected_sha256):
        raise ValueError(f"{path}: candidate schema or target hash mismatch; regenerate inventory")
    candidates = inventory["candidates"]
    if not isinstance(candidates, list):
        raise ValueError(f"{path}: candidates must be a list")
    names, identities, ranges = set(), set(), set()
    for candidate in candidates:
        if not all(candidate.get(key) for key in (
                "id", "name", "target_rva", "target_size", "source", "profile", "evidence")):
            raise ValueError(f"{path}: candidate is missing its identity, extent or source/profile")
        if not all(isinstance(candidate[key], str) for key in ("id", "name", "source", "profile", "evidence")):
            raise ValueError(f"{path}: candidate identities, source and profile must be text")
        extent = number(candidate["target_rva"]), number(candidate["target_size"])
        raw = target.read_rva(*extent)
        relative_path(target, candidate["source"])
        if candidate.get("packet_sha256") != packet_hash(candidate):
            raise ValueError(f"{path}: stale candidate packet hash; regenerate inventory")
        if candidate.get("bytes_sha256") != hashlib.sha256(raw).hexdigest():
            raise ValueError(f"{path}: candidate body differs from the selected image")
        for donor in candidate.get("donor_files", []):
            from worldbuilder_inventory import text_sha256
            if donor.get("normalization") != "CRLF-to-LF":
                raise ValueError(f"{path}: unsupported donor hash normalization")
            if text_sha256(relative_path(target, donor["path"])) != donor["sha256"]:
                raise ValueError(f"{path}: stale donor {donor['path']}; regenerate inventory")
        if candidate["profile"] not in target.profiles:
            raise ValueError(f"{path}: unknown candidate compiler profile {candidate['profile']}")
        if candidate["name"] in names or candidate["id"] in identities or extent in ranges:
            raise ValueError(f"{path}: duplicate candidate identity/range {candidate['name']}")
        names.add(candidate["name"])
        identities.add(candidate["id"])
        ranges.add(extent)
    return candidates


def read_attempts(target):
    path = target.ledger_root / "attempts.jsonl"
    if not path.exists():
        if list((target.ledger_root / "attempts").rglob("*.cpp")):
            raise ValueError(f"{path}: banked sources exist without an attempt log")
        return []
    attempts = []
    banks = set()
    raw = path.read_text(encoding="utf-8")
    if raw and not raw.endswith("\n"):
        raise ValueError(f"{path}: truncated attempt log; expected a final newline")
    for line in raw.splitlines():
        item = json.loads(line)
        required = ("target_id", "binary_sha256", "name", "target_rva", "target_size",
                    "status", "evidence", "model", "blocker", "time", "packet_sha256")
        if not isinstance(item, dict) or not all(item.get(key) for key in required):
            raise ValueError(f"{path}: incomplete attempt metadata")
        if item["target_id"] != target.target_id or item["binary_sha256"] != target.expected_sha256:
            raise ValueError(f"{path}: attempt belongs to another target image")
        for field in ("name", "evidence", "model", "blocker"):
            if not isinstance(item[field], str) or not item[field].strip():
                raise ValueError(f"{path}: attempt {field} must be nonempty text")
        if not isinstance(item["packet_sha256"], str) or not re.fullmatch("[0-9a-f]{64}", item["packet_sha256"]):
            raise ValueError(f"{path}: attempt needs its original packet SHA-256")
        if not isinstance(item["time"], str) or datetime.fromisoformat(item["time"]).tzinfo is None:
            raise ValueError(f"{path}: attempt timestamp needs its timezone")
        target.read_rva(number(item["target_rva"]), number(item["target_size"]))
        if item["status"] not in ("blocked", "partial"):
            raise ValueError(f"{path}: unsupported attempt status {item['status']!r}")
        if item["status"] == "partial":
            score = item.get("score")
            if (not item.get("stash") or not isinstance(score, (int, float)) or isinstance(score, bool)
                    or not 0 <= score < 1):
                raise ValueError(f"{path}: partial attempt needs banked source and score in [0, 1)")
        elif any(field in item for field in ("stash", "stash_sha256", "score")):
            raise ValueError(f"{path}: blocked attempt must not declare a partial body")
        if item.get("stash"):
            stash = relative_path(target, item["stash"])
            if not stash.is_relative_to(target.ledger_root / "attempts"):
                raise ValueError(f"{path}: banked attempt is outside this target's attempts directory")
            digest = hashlib.sha256(stash.read_bytes()).hexdigest()
            if digest != item.get("stash_sha256"):
                raise ValueError(f"{stash}: banked attempt hash mismatch")
            if stash.name != f"{number(item['target_rva']):08x}-{digest}.cpp":
                raise ValueError(f"{stash}: banked attempt filename must identify its RVA and content hash")
            banks.add(stash)
        attempts.append(item)
    unreferenced = set((target.ledger_root / "attempts").rglob("*.cpp")) - banks
    if unreferenced:
        raise ValueError(f"{path}: banked sources have no attempt record: {sorted(map(str, unreferenced))}")
    return attempts


def with_attempt_history(target, candidates):
    attempts = read_attempts(target)
    return [dict(candidate, previous_attempts=[item for item in attempts
            if number(item["target_rva"]) == number(candidate["target_rva"])
            and number(item["target_size"]) == number(candidate["target_size"])])
            for candidate in candidates]


def open_candidates(target):
    rows = target_verify.read_rows(target)
    target_verify.validate_rows(target, rows)
    landed = [(number(row["target_rva"]), number(row["target_size"])) for row in rows]
    result = []
    for candidate in load_candidates(target):
        start, size = number(candidate["target_rva"]), number(candidate["target_size"])
        if (start, size) in landed:
            continue
        if any(start < rva + count and rva < start + size for rva, count in landed):
            raise ValueError(f"candidate {candidate['name']} overlaps an accepted extent; rebuild inventory")
        result.append(candidate)
    return sorted(with_attempt_history(target, result), key=lambda candidate: bool(candidate["previous_attempts"]))


def select(rows, selectors):
    if not selectors:
        return list(rows)
    result = []
    for selector in selectors:
        try:
            rva = number(selector)
        except ValueError:
            rva = None
        matches = [row for row in rows if selector in (row["name"], row["source"], row.get("id"))
                   or rva == number(row["target_rva"])]
        if not matches:
            raise ValueError(f"no WorldBuilder row matches {selector!r}")
        for row in matches:
            if row not in result:
                result.append(row)
    return result


@contextmanager
def ledger_lock(target):
    target.build_root.mkdir(parents=True, exist_ok=True)
    with (target.build_root / "ledger.lock").open("a+b") as handle:
        lock(handle, exclusive=True, wait_notice="worldbuilder: waiting for target ledger lock")
        yield


def serialize(rows):
    output = io.StringIO(newline="")
    writer = csv.DictWriter(output, fieldnames=FIELDS, lineterminator="\n")
    writer.writeheader()
    writer.writerows(rows)
    return output.getvalue().encode("utf-8")


def land(target, row):
    relative_path(target, row["source"])
    with ledger_lock(target):
        target.verify_hash()
        rows = target_verify.read_rows(target)
        ledger_before = target.ledger_path.read_bytes()
        target_verify.validate_rows(target, [*rows, row])
        source = relative_path(target, row["source"])
        source_hash = hashlib.sha256(source.read_bytes()).hexdigest()
        result = target_verify.verify(target, [*rows, row], selectors=[row["source"]])
        if hashlib.sha256(source.read_bytes()).hexdigest() != source_hash:
            raise ValueError("source changed during verification; ledger was not modified")
        target.verify_hash()
        if target.ledger_path.read_bytes() != ledger_before:
            raise ValueError("ledger changed outside its lock during verification; refusing to overwrite it")
        atomic_write_bytes(target.ledger_path, serialize([*rows, row]))
    return result


def record(target, args):
    candidates = select(load_candidates(target), [args.selector])
    if len(candidates) != 1:
        raise ValueError("record needs one candidate name or RVA, not a source family")
    candidate = candidates[0]
    if args.status == "partial" and (args.stash is None or args.score is None):
        raise ValueError("partial requires both --stash and --score")
    if args.status == "blocked" and (args.stash is not None or args.score is not None):
        raise ValueError("use partial when banking a source body and score")
    if args.score is not None and not 0 <= args.score < 1:
        raise ValueError("partial score must be at least zero and less than one")
    if not args.model.strip() or not args.evidence.strip() or not args.blocker.strip():
        raise ValueError("attempt model, evidence and blocker must be nonempty")
    item = {"target_id": target.target_id, "binary_sha256": target.expected_sha256,
            "name": candidate["name"], "target_rva": candidate["target_rva"],
            "target_size": candidate["target_size"], "status": args.status,
            "evidence": args.evidence, "model": args.model, "blocker": args.blocker,
            "time": datetime.now(timezone.utc).isoformat(), "packet_sha256": packet_hash(candidate)}
    body = None
    if args.stash:
        source = relative_path(target, args.stash)
        if source.suffix != ".cpp":
            raise ValueError("--stash must name a C++ source file")
        body = source.read_bytes()
        digest = hashlib.sha256(body).hexdigest()
        bank = target.ledger_root / "attempts" / f"{number(candidate['target_rva']):08x}-{digest}.cpp"
        item.update(stash=bank.relative_to(target.root).as_posix(), stash_sha256=digest, score=args.score)
    with ledger_lock(target):
        target.verify_hash()
        read_attempts(target)
        if any(number(row["target_rva"]) == number(candidate["target_rva"])
               for row in target_verify.read_rows(target)):
            raise ValueError("candidate already landed; cannot record a new blocked or partial attempt")
        if body is not None:
            bank.parent.mkdir(parents=True, exist_ok=True)
            atomic_write_bytes(bank, body)
        path = target.ledger_root / "attempts.jsonl"
        old = path.read_bytes() if path.exists() else b""
        atomic_write_bytes(path, old + (json.dumps(item, sort_keys=True) + "\n").encode("utf-8"))
    return item


def totals(rows):
    values = {"editor": {"functions": 0, "bytes": 0}, "engine": {"functions": 0, "bytes": 0}}
    for row in rows:
        category = "editor" if row["source"].startswith("worldbuilder/src/") else "engine"
        values[category]["functions"] += 1
        values[category]["bytes"] += number(row["target_size"])
    return values


def progress(target, rows, ref=None):
    report = totals(rows)
    report["text_bytes"] = target.text_section.virtual_size
    report["verified_bytes"] = sum(number(row["target_size"]) for row in rows)
    report["percent"] = 100 * report["verified_bytes"] / report["text_bytes"]
    if ref:
        subprocess.run(["git", "rev-parse", "--verify", ref + "^{commit}"], cwd=target.root,
                       check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        ledger = target.ledger_path.relative_to(target.root).as_posix()
        names = subprocess.run(["git", "ls-tree", "--name-only", ref, "--", ledger], cwd=target.root,
                               check=True, capture_output=True, text=True).stdout.splitlines()
        before = []
        if ledger in names:
            raw = subprocess.run(["git", "show", ref + ":" + ledger], cwd=target.root,
                                 check=True, capture_output=True, text=True).stdout
            reader = csv.DictReader(io.StringIO(raw))
            if reader.fieldnames != list(FIELDS):
                raise ValueError(f"{ref}:{ledger}: unexpected target ledger schema")
            before = list(reader)
        report["reference"] = ref
        report["delta_bytes"] = report["verified_bytes"] - sum(number(row["target_size"]) for row in before)
        report["delta_pp"] = 100 * report["delta_bytes"] / report["text_bytes"]
    return report


def parser():
    cli = argparse.ArgumentParser(description=__doc__)
    commands = cli.add_subparsers(dest="command", required=True)
    commands.add_parser("check", help="validate WorldBuilder ledger, queue, attempts and donor index")
    verify = commands.add_parser("verify", help="compile and compare selected accepted bodies")
    verify.add_argument("selectors", nargs="*")
    for command in ("probe", "land"):
        action = commands.add_parser(command)
        for field in ("name", "rva", "size", "source", "profile", "evidence"):
            action.add_argument("--" + field, required=True)
        action.add_argument("--model", required=command == "land", default="probe")
    counter = commands.add_parser("progress")
    counter.add_argument("--ref")
    next_command = commands.add_parser("next", help="show the next open source family")
    next_command.add_argument("--all", action="store_true")
    show = commands.add_parser("show", help="show a candidate or source-family packet")
    show.add_argument("selector")
    attempt = commands.add_parser("record")
    attempt.add_argument("selector")
    attempt.add_argument("status", choices=("blocked", "partial"))
    for field in ("model", "evidence", "blocker"):
        attempt.add_argument("--" + field, required=True)
    attempt.add_argument("--stash")
    attempt.add_argument("--score", type=float)
    return cli


def main(argv=None):
    args = parser().parse_args(argv)
    try:
        target = load_target("worldbuilder")
        if os.environ.get("BFME_TARGET", target.target_id) != target.target_id:
            raise ValueError("BFME_TARGET disagrees with the explicit WorldBuilder command")
        if os.environ.get("BFME_TARGET_SHA256", target.expected_sha256) != target.expected_sha256:
            raise ValueError("BFME_TARGET_SHA256 disagrees with the WorldBuilder image; packet is stale")
        print(f"worldbuilder: target={target.target_id} sha256={target.expected_sha256}", file=sys.stderr)
        if args.command in ("check", "verify", "progress"):
            rows = target_verify.read_rows(target)
            target_verify.validate_rows(target, rows)
            if args.command == "check":
                result = {"valid_rows": len(rows), "valid_candidates": len(load_candidates(target)),
                          "valid_attempts": len(read_attempts(target)),
                          "valid_donor_suggestions": len(worldbuilder_donors.lookup(target))}
            elif args.command == "verify":
                selected = select(rows, args.selectors)
                result = target_verify.verify(target, rows, selectors=[row["name"] for row in selected])
            else:
                result = progress(target, rows, args.ref)
        elif args.command in ("probe", "land"):
            row = dict(zip(FIELDS, (args.name, f"0x{number(args.rva):08X}", str(number(args.size)),
                       "matched", args.source, args.profile, args.evidence, args.model)))
            relative_path(target, args.source)
            print(f"worldbuilder: profile={args.profile} source={args.source}", file=sys.stderr)
            result = land(target, row) if args.command == "land" else target_verify.probe(
                target, args.source, args.name, number(args.rva), number(args.size), args.profile, args.evidence)
        elif args.command in ("next", "show"):
            candidates = open_candidates(target) if args.command == "next" else load_candidates(target)
            if args.command == "show":
                candidates = with_attempt_history(target, select(candidates, [args.selector]))
            elif candidates and not args.all:
                candidates = select(candidates, [candidates[0]["source"]])
            candidates = [dict(candidate, donor_suggestions=worldbuilder_donors.lookup(
                target, candidate["name"], exact=True)) for candidate in candidates]
            result = {"target_id": target.target_id, "binary_sha256": target.expected_sha256,
                      "candidates": candidates, "packet_sha256": packet_hash(candidates)}
        elif args.command == "record":
            result = record(target, args)
        print(json.dumps(result, indent=2, default=str))
        return 0
    except (ValueError, OSError, KeyError, subprocess.CalledProcessError) as error:
        print(f"worldbuilder: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
