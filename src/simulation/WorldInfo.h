
#pragma once

#include "Math.h"

namespace ParticleSimulation
{
    using Index = int;
    using Vec2 = MMath::Vec2<Index>;

    class WorldInfo
    {
    public:
        WorldInfo(Vec2 size = Vec2(0, 0));

        // Calculate position based on given index.
        // The position is quaranteed to be withing the world bounds
        Vec2 IndexToPosition(Index index) const;

        // Calculate index based on given position
        // The index is quaranteed to be withing the world bounds
        Index PositionToIndex(Vec2 position) const;

        // Check wether given position is within the world
        bool IsValidPosition(Vec2 position) const;

        Vec2 GetSize() const { return m_WorldSize; };

        Index GetWidth() const { return m_WorldSize.x; }
        Index GetHeight() const { return m_WorldSize.y; }

        Index GetMaxIndex() const { return m_MaxIndex; }
        

    private:
        Vec2 m_WorldSize;

        Index m_MinIndex;
        Index m_MaxIndex;

        Vec2 m_MinPos;
        Vec2 m_MaxPos;
    };
}