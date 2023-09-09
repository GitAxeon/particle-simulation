#include "WorldInfo.h"

namespace ParticleSimulation
{
    WorldInfo::WorldInfo(Vec2 size)
    {
        m_WorldSize = size;

        m_MinIndex = 0;
        m_MaxIndex = size.x * size.y - 1;

        m_MinPos = Vec2(0, 0);
        m_MaxPos = Vec2(size.x - 1, size.y - 1);
    }

    Vec2 WorldInfo::IndexToPosition(Index index) const
    {
        Vec2 result(index % m_WorldSize.x, index / m_WorldSize.x);

        return Vec2(
            MMath::Clamp(result.x, m_MinPos.x, m_MaxPos.x),
            MMath::Clamp(result.y, m_MinPos.y, m_MaxPos.y)
        );
    }

    Index WorldInfo::PositionToIndex(Vec2 position) const
    {
        Index index = m_WorldSize.x * position.y + position.x;

        return MMath::Clamp(index, m_MinIndex, m_MaxIndex);
    }

    bool WorldInfo::IsValidPosition(Vec2 position) const
    {
        if(position.x < m_MinPos.x || position.x > m_MaxPos.x ||
            position.y < m_MinPos.y || position.y > m_MaxPos.y)
        {  
            return false;
        }

        return true;
    };

}