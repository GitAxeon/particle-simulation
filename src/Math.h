#pragma once

int Min(int lhs, int rhs)
{    
    return lhs < rhs ? lhs : rhs;
}

int Max(int lhs, int rhs)
{
    return lhs > rhs ? lhs : rhs;
}

int Clamp(int value, int min, int max)
{
    return Max(min, Min(value, max));
}