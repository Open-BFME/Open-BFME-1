#include "game_client_random_variable.h"

GameClientRandomVariable::GameClientRandomVariable()
{
    distribution = CONSTANT;
    minimum = 0.0f;
    maximum = 0.0f;
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

void GameClientRandomVariable::setRange(float minimum, float maximum, DistributionType distribution)
{
    this->minimum = minimum;
    this->maximum = maximum;
    this->distribution = distribution;
}

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
