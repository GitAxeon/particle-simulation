
#pragma once

#include "Math.h"

namespace ParticleSimulation
{
    using Index = size_t;
    using Vec2 = MMath::u32Vec2;

    class WorldInfo
    {
    public:
        WorldInfo(Vec2 size = Vec2(0, 0))
        {
            m_WorldSize = size;

            m_MinIndex = 0;
            m_MaxIndex = size.x * size.y - 1;

            m_MinPos = Vec2(0, 0);
            m_MaxPos = Vec2(size.x - 1, size.y - 1);
        }

        // Calculate position based on given index.
        // The position is quaranteed to be withing the world bounds
        Vec2 IndexToPosition(Index index) const
        {
            Vec2 result(index % m_WorldSize.x, index / m_WorldSize.y);

            return Vec2(
                MMath::Clamp(result.x, m_MinPos.x, m_MaxPos.x),
                MMath::Clamp(result.y, m_MinPos.y, m_MaxPos.y)
            );
        }

        // Calculate index based on given position
        // The index is quaranteed to be withing the world bounds
        Index PositionToIndex(Vec2 position) const
        {
            Index index = m_WorldSize.x * position.y + position.x;

            return MMath::Clamp(index, m_MinIndex, m_MaxIndex);
        }

        // Check wether given position is within the world
        bool IsValidPosition(Vec2 position) const
        {
            if(position.x < m_MinPos.x || position.x > m_MaxPos.x ||
                position.y < m_MinPos.y ||position.y > m_MaxPos.y)
            {  
                return false;
            }

            return true;
        };

        Vec2 GetSize() const { return m_WorldSize; };

    private:
        Vec2 m_WorldSize;

        Index m_MinIndex;
        Index m_MaxIndex;

        Vec2 m_MinPos;
        Vec2 m_MaxPos;
    };
}