#!/usr/bin/env python3
"""Train the tiny learned-horde tactical policy and export C++ weights.

This is a bootstrap tactical simulator, not BFME itself. It produces reward
outcomes for possible horde actions, trains a tiny network to approximate those
action values, and exports the resulting Q-policy into the CRT-free BFME
runtime. There are no replay labels, expert actions, or language models here.
"""

from __future__ import annotations

import argparse
from pathlib import Path

import torch
from torch import nn


OBS = 16
HIDDEN = 8
ACTIONS = 5

HOLD = 0
ATTACK_NEAREST = 1
ATTACK_WEAKEST = 2
ATTACK_STRUCTURE = 3
RETREAT = 4


class Policy(nn.Module):
    def __init__(self) -> None:
        super().__init__()
        self.fc1 = nn.Linear(OBS, HIDDEN)
        self.fc2 = nn.Linear(HIDDEN, ACTIONS)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.fc2(torch.relu(self.fc1(x)))


def _rand(n: int, lo: float, hi: float, device: torch.device) -> torch.Tensor:
    return lo + (hi - lo) * torch.rand(n, device=device)


def sample_balanced(
    batch: int, device: torch.device
) -> tuple[torch.Tensor, torch.Tensor]:
    """Generate five deliberately different tactical situation families.

    The family id is used only for diagnostics. Training never receives it as
    an action label.

      0: nearest visible horde is the attractive engagement
      1: a wounded visible horde is worth finishing
      2: a weakly defended visible structure is the best value
      3: the horde is wounded/outmatched and should preserve itself
      4: no enemy is currently visible
    """
    mode = torch.randint(0, 5, (batch,), device=device)
    x = torch.zeros(batch, OBS, device=device)

    # Generic state before the scenario-family overrides.
    x[:, 0] = _rand(batch, 0.40, 1.00, device)  # own average health
    x[:, 1] = _rand(batch, 0.30, 1.20, device)  # own coarse power

    x[:, 2] = _rand(batch, 0.30, 0.90, device)  # nearest horde health
    x[:, 3] = _rand(batch, 0.10, 0.80, device)  # nearest horde distance
    x[:, 4] = _rand(batch, 0.20, 1.00, device)  # nearest horde threat

    x[:, 5] = _rand(batch, 0.10, 0.70, device)  # weakest horde health
    x[:, 6] = _rand(batch, 0.10, 0.90, device)  # weakest horde distance
    x[:, 7] = _rand(batch, 0.20, 0.90, device)  # weakest horde threat

    x[:, 8] = _rand(batch, 0.20, 0.95, device)  # structure health
    x[:, 9] = _rand(batch, 0.10, 0.90, device)  # structure distance
    x[:, 10] = _rand(batch, 0.10, 0.80, device) # structure threat
    x[:, 11] = 1.0                              # structure present

    # Same normalization used by the BFME runtime.
    x[:, 12] = _rand(batch, 0.35, 0.85, device) # visible horde count / 6
    x[:, 13] = _rand(batch, 0.20, 0.70, device) # visible structure count / 5
    x[:, 14] = 0.0                              # reserved memory feature
    x[:, 15] = 1.0                              # bias / presence constant

    # 0: nearest horde is close, relatively safe, and useful to engage.
    m = mode == 0
    n = int(m.sum())
    x[m, 0] = _rand(n, 0.80, 1.00, device)
    x[m, 1] = _rand(n, 0.80, 1.20, device)
    x[m, 2] = _rand(n, 0.40, 0.70, device)
    x[m, 3] = _rand(n, 0.05, 0.20, device)
    x[m, 4] = _rand(n, 0.15, 0.35, device)
    x[m, 5] = _rand(n, 0.25, 0.40, device)
    x[m, 6] = _rand(n, 0.75, 0.95, device)
    x[m, 7] = _rand(n, 0.70, 1.00, device)
    x[m, 8] = _rand(n, 0.80, 1.00, device)
    x[m, 9] = _rand(n, 0.70, 0.95, device)
    x[m, 10] = _rand(n, 0.65, 0.85, device)

    # 1: weakest horde is genuinely finishable; alternatives are expensive.
    m = mode == 1
    n = int(m.sum())
    x[m, 0] = _rand(n, 0.70, 1.00, device)
    x[m, 1] = _rand(n, 0.70, 1.20, device)
    x[m, 2] = _rand(n, 0.70, 0.95, device)
    x[m, 3] = _rand(n, 0.15, 0.35, device)
    x[m, 4] = _rand(n, 0.70, 1.00, device)
    x[m, 5] = _rand(n, 0.05, 0.20, device)
    x[m, 6] = _rand(n, 0.20, 0.45, device)
    x[m, 7] = _rand(n, 0.10, 0.35, device)
    x[m, 8] = _rand(n, 0.75, 1.00, device)
    x[m, 9] = _rand(n, 0.65, 0.95, device)
    x[m, 10] = _rand(n, 0.60, 0.85, device)

    # 2: structure opportunity; enemy hordes are worse engagements.
    m = mode == 2
    n = int(m.sum())
    x[m, 0] = _rand(n, 0.75, 1.00, device)
    x[m, 1] = _rand(n, 0.80, 1.20, device)
    x[m, 2] = _rand(n, 0.60, 0.90, device)
    x[m, 3] = _rand(n, 0.40, 0.70, device)
    x[m, 4] = _rand(n, 0.70, 1.00, device)
    x[m, 5] = _rand(n, 0.30, 0.50, device)
    x[m, 6] = _rand(n, 0.60, 0.90, device)
    x[m, 7] = _rand(n, 0.50, 0.80, device)
    x[m, 8] = _rand(n, 0.15, 0.45, device)
    x[m, 9] = _rand(n, 0.10, 0.30, device)
    x[m, 10] = _rand(n, 0.05, 0.25, device)

    # 3: wounded, low-power horde facing close high-threat enemies.
    m = mode == 3
    n = int(m.sum())
    x[m, 0] = _rand(n, 0.10, 0.35, device)
    x[m, 1] = _rand(n, 0.20, 0.50, device)
    x[m, 2] = _rand(n, 0.70, 1.00, device)
    x[m, 3] = _rand(n, 0.05, 0.25, device)
    x[m, 4] = _rand(n, 0.90, 1.20, device)
    x[m, 5] = _rand(n, 0.35, 0.60, device)
    x[m, 6] = _rand(n, 0.15, 0.35, device)
    x[m, 7] = _rand(n, 0.70, 1.00, device)
    x[m, 8] = _rand(n, 0.60, 0.90, device)
    x[m, 9] = _rand(n, 0.40, 0.80, device)
    x[m, 10] = _rand(n, 0.60, 0.85, device)

    # 4: no currently visible enemy. Masking removes every target action.
    m = mode == 4
    x[m, 11] = 0.0
    x[m, 12] = 0.0
    x[m, 13] = 0.0
    x[m, 2:11] = 0.0

    return x, mode


def reward_matrix(x: torch.Tensor) -> torch.Tensor:
    """Score the consequences of each tactical action.

    The network is not told a hand-authored action. It is shown state -> reward
    values and learns to approximate those values. In real BFME training these
    synthetic values are intended to be replaced by observed match outcomes.
    """
    hp = x[:, 0]
    own = x[:, 1]

    nh, nd, nt = x[:, 2], x[:, 3], x[:, 4]
    wh, wd, wt = x[:, 5], x[:, 6], x[:, 7]
    sh, sd, st = x[:, 8], x[:, 9], x[:, 10]

    horde_present = (x[:, 12] > 0).float()
    structure_present = (x[:, 11] > 0).float()

    r_hold = torch.where(
        horde_present > 0,
        torch.full_like(horde_present, -0.70),
        torch.full_like(horde_present, 0.70),
    )

    r_nearest = horde_present * (
        1.00 * (1.0 - nd)
        + 0.70 * (1.0 - nh)
        + 0.60 * own
        - 1.20 * nt * (1.20 - hp)
    )

    r_weakest = horde_present * (
        0.80 * (1.0 - wd)
        + 1.20 * (1.0 - wh)
        + 0.50 * own
        - 1.00 * wt * (1.20 - hp)
    )

    r_structure = structure_present * (
        1.10 * (1.0 - sd)
        + 1.00 * (1.0 - sh)
        + 0.60 * own
        - 1.30 * st * (1.30 - hp)
    )

    danger = torch.maximum(nt, wt)
    r_retreat = horde_present * (
        1.80 * (1.0 - hp)
        + 1.00 * danger
        - 0.90 * own
        + 0.40 * (1.0 - nd)
        - 0.40
    )

    return torch.stack(
        [r_hold, r_nearest, r_weakest, r_structure, r_retreat], dim=1
    )


def valid_action_mask(x: torch.Tensor) -> torch.Tensor:
    mask = torch.ones(x.shape[0], ACTIONS, dtype=torch.bool, device=x.device)
    no_horde = x[:, 12] <= 0
    no_structure = x[:, 11] <= 0

    mask[no_horde, ATTACK_NEAREST] = False
    mask[no_horde, ATTACK_WEAKEST] = False
    mask[no_horde, RETREAT] = False
    mask[no_structure, ATTACK_STRUCTURE] = False
    return mask


def mask_values(values: torch.Tensor, x: torch.Tensor) -> torch.Tensor:
    return values.masked_fill(~valid_action_mask(x), -1.0e9)


def format_values(values: torch.Tensor, per_line: int = 8) -> str:
    flat = values.detach().cpu().reshape(-1).tolist()
    lines: list[str] = []
    for i in range(0, len(flat), per_line):
        chunk = ", ".join(f"{v:.9g}f" for v in flat[i : i + per_line])
        lines.append("    " + chunk)
    return ",\n".join(lines)


def write_header(model: Policy, path: Path) -> None:
    text = f"""// Generated by train.py. Do not hand-edit.
// 16 -> 8 ReLU -> 5 action values.
// Actions: 0 HOLD, 1 ATTACK_NEAREST, 2 ATTACK_WEAKEST, 3 ATTACK_STRUCTURE, 4 RETREAT.
#pragma once
enum {{ POLICY_OBS = {OBS}, POLICY_HIDDEN = {HIDDEN}, POLICY_ACTIONS = {ACTIONS} }};
static const float POLICY_W1[{OBS * HIDDEN}] = {{
{format_values(model.fc1.weight)}
}};
static const float POLICY_B1[{HIDDEN}] = {{
{format_values(model.fc1.bias)}
}};
static const float POLICY_W2[{HIDDEN * ACTIONS}] = {{
{format_values(model.fc2.weight)}
}};
static const float POLICY_B2[{ACTIONS}] = {{
{format_values(model.fc2.bias)}
}};
"""
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


@torch.no_grad()
def evaluate(model: Policy, device: torch.device, samples: int) -> None:
    x, family = sample_balanced(samples, device)
    rewards = mask_values(reward_matrix(x), x)
    predicted = mask_values(model(x), x).argmax(dim=1)
    optimal = rewards.argmax(dim=1)

    agreement = (predicted == optimal).float().mean().item()
    print(f"held-out best-reward agreement: {agreement * 100:.2f}%")

    names = ["hold", "nearest", "weakest", "structure", "retreat"]
    for scenario in range(5):
        m = family == scenario
        counts = torch.bincount(predicted[m], minlength=ACTIONS).cpu().tolist()
        total = max(1, int(m.sum()))
        summary = ", ".join(
            f"{names[action]}={100.0 * counts[action] / total:.1f}%"
            for action in range(ACTIONS)
        )
        print(f"scenario family {scenario}: {summary}")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--steps", type=int, default=800)
    ap.add_argument("--batch", type=int, default=2000)
    ap.add_argument("--seed", type=int, default=7)
    ap.add_argument("--eval-samples", type=int, default=10000)
    ap.add_argument(
        "--output",
        type=Path,
        default=Path(__file__).resolve().parent / "src/policy_weights.inc",
    )
    args = ap.parse_args()

    torch.manual_seed(args.seed)
    device = torch.device("cpu")
    model = Policy().to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=3.0e-3)

    # A contextual-bandit/Q bootstrap: learn the value each action receives
    # under the consequence model, then choose argmax at runtime.
    for step in range(args.steps):
        x, _ = sample_balanced(args.batch, device)
        rewards = reward_matrix(x)
        predicted_values = model(x)
        loss = torch.mean((predicted_values - rewards) ** 2)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if step % 100 == 0 or step + 1 == args.steps:
            print(
                f"step {step + 1:4d}/{args.steps}: "
                f"q_mse={loss.item():.6f}"
            )

    evaluate(model, device, args.eval_samples)
    write_header(model, args.output)
    params = sum(p.numel() for p in model.parameters())
    print(f"wrote {args.output} ({params} trainable parameters)")


if __name__ == "__main__":
    main()
