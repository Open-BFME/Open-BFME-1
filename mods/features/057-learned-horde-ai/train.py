#!/usr/bin/env python3
"""Train the tiny learned-horde tactical policy and export C++ weights.

This is a bootstrap simulator, not BFME itself. It trains from consequences
(reward), not from expert labels. The runtime adapter then executes the learned
policy inside BFME's HordeAIUpdate path.
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
    """Generate balanced tactical situations.

    mode:
      0 nearest visible horde is the best fight
      1 weakest visible horde is the best finish
      2 visible structure is the best value target
      3 retreat is best because the horde is overmatched
      4 no visible target -> HOLD is the only valid tactical action

    The second return value is only a diagnostic scenario id. It is NOT used as
    a supervised label during training.
    """
    mode = torch.randint(0, 5, (batch,), device=device)
    x = torch.zeros(batch, OBS, device=device)

    # Own horde.
    x[:, 0] = _rand(batch, 0.35, 1.0, device)   # average health
    x[:, 1] = _rand(batch, 0.25, 1.2, device)  # coarse combat power

    # Nearest enemy horde.
    x[:, 2] = _rand(batch, 0.2, 1.0, device)   # health
    x[:, 3] = _rand(batch, 0.05, 0.8, device)  # distance
    x[:, 4] = _rand(batch, 0.15, 1.2, device)  # threat/power

    # Weakest visible enemy horde.
    x[:, 5] = _rand(batch, 0.08, 0.75, device)
    x[:, 6] = _rand(batch, 0.08, 0.95, device)
    x[:, 7] = _rand(batch, 0.10, 1.0, device)

    # Nearest visible enemy structure.
    x[:, 8] = _rand(batch, 0.12, 1.0, device)
    x[:, 9] = _rand(batch, 0.10, 0.95, device)
    x[:, 10] = _rand(batch, 0.15, 0.85, device)
    x[:, 11] = 1.0  # structure present

    # Visible counts, normalized like the BFME runtime.
    x[:, 12] = _rand(batch, 0.35, 0.85, device)
    x[:, 13] = _rand(batch, 0.20, 0.70, device)

    # Reserved temporal-memory feature and constant bias.
    x[:, 14] = 0.0
    x[:, 15] = 1.0

    # Family 0: healthy/strong, nearest enemy is exposed.
    m = mode == 0
    x[m, 0] = _rand(int(m.sum()), 0.68, 1.0, device)
    x[m, 1] = _rand(int(m.sum()), 0.65, 1.2, device)
    x[m, 2] = _rand(int(m.sum()), 0.45, 0.9, device)
    x[m, 3] = _rand(int(m.sum()), 0.05, 0.30, device)
    x[m, 4] = _rand(int(m.sum()), 0.15, 0.50, device)
    x[m, 5] = _rand(int(m.sum()), 0.35, 0.70, device)
    x[m, 6] = _rand(int(m.sum()), 0.55, 0.95, device)

    # Family 1: a damaged horde is worth finishing.
    m = mode == 1
    x[m, 0] = _rand(int(m.sum()), 0.55, 1.0, device)
    x[m, 5] = _rand(int(m.sum()), 0.05, 0.24, device)
    x[m, 6] = _rand(int(m.sum()), 0.12, 0.55, device)
    x[m, 7] = _rand(int(m.sum()), 0.10, 0.45, device)
    x[m, 2] = _rand(int(m.sum()), 0.50, 0.95, device)

    # Family 2: undefended/valuable structure opportunity.
    m = mode == 2
    x[m, 0] = _rand(int(m.sum()), 0.62, 1.0, device)
    x[m, 8] = _rand(int(m.sum()), 0.15, 0.55, device)
    x[m, 9] = _rand(int(m.sum()), 0.08, 0.42, device)
    x[m, 10] = _rand(int(m.sum()), 0.05, 0.28, device)
    x[m, 4] = _rand(int(m.sum()), 0.48, 1.0, device)
    x[m, 7] = _rand(int(m.sum()), 0.42, 0.9, device)

    # Family 3: wounded and outmatched -> preserve the horde.
    m = mode == 3
    x[m, 0] = _rand(int(m.sum()), 0.08, 0.38, device)
    x[m, 1] = _rand(int(m.sum()), 0.18, 0.55, device)
    x[m, 3] = _rand(int(m.sum()), 0.05, 0.34, device)
    x[m, 4] = _rand(int(m.sum()), 0.72, 1.2, device)
    x[m, 7] = _rand(int(m.sum()), 0.55, 1.0, device)

    # Family 4: nothing currently visible. Action masking leaves HOLD.
    m = mode == 4
    x[m, 11] = 0.0
    x[m, 12] = 0.0
    x[m, 13] = 0.0
    x[m, 2:11] = 0.0

    return x, mode


def reward_matrix(x: torch.Tensor) -> torch.Tensor:
    """Consequence model used by the bootstrap simulator.

    No action is declared "correct". Each action receives a scalar outcome and
    training maximizes expected reward.
    """
    hp = x[:, 0]
    own = x[:, 1]

    nh, nd, nt = x[:, 2], x[:, 3], x[:, 4]
    wh, wd, wt = x[:, 5], x[:, 6], x[:, 7]
    sh, sd, st = x[:, 8], x[:, 9], x[:, 10]
    has_structure = x[:, 11]
    visible_hordes = x[:, 12]

    n_present = (visible_hordes > 0).float()
    w_present = n_present
    s_present = (has_structure > 0).float()

    # Approximate immediate damage/value opportunity from strength and distance.
    nearest_damage = own * (1.0 - 0.65 * nd) * n_present
    weakest_damage = own * (1.0 - 0.55 * wd) * w_present
    structure_damage = own * (1.0 - 0.50 * sd) * s_present

    r_hold = (
        0.30 * (visible_hordes <= 0).float()
        - 0.45 * n_present
        - 0.20 * w_present
    )

    r_nearest = (
        nearest_damage
        - 0.90 * n_present * nt * (1.30 - hp)
        + 0.45 * (nearest_damage >= nh).float()
    )

    r_weakest = (
        weakest_damage
        - 0.80 * w_present * wt * (1.30 - hp)
        + 0.75 * (weakest_damage >= wh).float()
    )

    r_structure = (
        structure_damage
        + 0.40 * (1.0 - sh) * s_present
        - 1.10 * s_present * st * (1.35 - hp)
        + 0.80 * (structure_damage >= sh).float() * s_present
    )

    danger = n_present * nt + 0.65 * w_present * wt
    r_retreat = (
        1.40 * danger * (1.15 - hp)
        - 0.25 * hp
        - 0.18 * (nd > 0.70).float()
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


def mask_logits(logits: torch.Tensor, x: torch.Tensor) -> torch.Tensor:
    return logits.masked_fill(~valid_action_mask(x), -1.0e9)


def masked_rewards(reward: torch.Tensor, x: torch.Tensor) -> torch.Tensor:
    return reward.masked_fill(~valid_action_mask(x), -1.0e9)


def format_values(values: torch.Tensor, per_line: int = 8) -> str:
    flat = values.detach().cpu().reshape(-1).tolist()
    lines: list[str] = []
    for i in range(0, len(flat), per_line):
        chunk = ", ".join(f"{v:.9g}f" for v in flat[i : i + per_line])
        lines.append("    " + chunk)
    return ",\n".join(lines)


def write_header(model: Policy, path: Path) -> None:
    text = f"""// Generated by train.py. Do not hand-edit.
// 16 -> 8 ReLU -> 5 logits.
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
    x, mode = sample_balanced(samples, device)
    rewards = reward_matrix(x)
    optimal = masked_rewards(rewards, x).argmax(dim=1)
    predicted = mask_logits(model(x), x).argmax(dim=1)

    accuracy = (predicted == optimal).float().mean().item()
    print(f"held-out best-reward agreement: {accuracy * 100:.2f}%")

    names = ["hold", "nearest", "weakest", "structure", "retreat"]
    for family in range(5):
        m = mode == family
        counts = torch.bincount(predicted[m], minlength=ACTIONS).cpu().tolist()
        total = max(1, int(m.sum()))
        percentages = [100.0 * n / total for n in counts]
        summary = ", ".join(
            f"{names[i]}={percentages[i]:.1f}%" for i in range(ACTIONS)
        )
        print(f"scenario family {family}: {summary}")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--steps", type=int, default=1200)
    ap.add_argument("--batch", type=int, default=1000)
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
    optimizer = torch.optim.Adam(model.parameters(), lr=5.0e-3)

    for step in range(args.steps):
        x, _ = sample_balanced(args.batch, device)
        rewards = reward_matrix(x)

        logits = mask_logits(model(x), x)
        probabilities = torch.softmax(logits, dim=1)

        expected_reward = (probabilities * rewards).sum(dim=1).mean()
        entropy = -(
            probabilities * torch.log(probabilities.clamp_min(1.0e-9))
        ).sum(dim=1).mean()

        loss = -expected_reward - 0.006 * entropy
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if step % 200 == 0 or step + 1 == args.steps:
            print(
                f"step {step + 1:4d}/{args.steps}: "
                f"reward={expected_reward.item():.4f} "
                f"entropy={entropy.item():.4f}"
            )

    evaluate(model, device, args.eval_samples)
    write_header(model, args.output)
    params = sum(p.numel() for p in model.parameters())
    print(f"wrote {args.output} ({params} trainable parameters)")


if __name__ == "__main__":
    main()
