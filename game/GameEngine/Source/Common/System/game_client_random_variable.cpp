#include "game_client_random_variable.h"

GameClientRandomVariable &GameClientRandomVariable::operator=(const GameClientRandomVariable &that)
{
    struct Raw {
        unsigned int distribution;
        float minimum;
        float maximum;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

GameClientRandomVariable::DistributionType GameClientRandomVariable::getDistributionType() const
{
    return distribution;
}

float GameClientRandomVariable::getMinimumValue() const
{
    return minimum;
}

float GameClientRandomVariable::getMaximumValue() const
{
    return maximum;
}

// getValue() and setRange() are defined once, in random_value.cpp (retail 0x00096F60 / 0x00096F40).

bool operator==(const GameClientRandomVariable &left, const GameClientRandomVariable &right)
{
    return left.distribution == right.distribution &&
        left.minimum == right.minimum &&
        left.maximum == right.maximum;
}

bool operator!=(const GameClientRandomVariable &left, const GameClientRandomVariable &right)
{
    return !(left == right);
}
