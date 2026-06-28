#pragma once

class GameClientRandomVariable {
public:
    enum DistributionType {
        CONSTANT = 0,
    };

    GameClientRandomVariable();

    DistributionType getDistributionType() const;
    float getMinimumValue() const;
    float getMaximumValue() const;
    void setRange(float minimum, float maximum, DistributionType distribution);

    DistributionType distribution;
    float minimum;
    float maximum;
};

bool operator==(const GameClientRandomVariable &left, const GameClientRandomVariable &right);
bool operator!=(const GameClientRandomVariable &left, const GameClientRandomVariable &right);
