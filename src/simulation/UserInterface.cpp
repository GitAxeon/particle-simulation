#include "UserInterface.h"

namespace ParticleSimulation
{
    void UserInterface::KeyDown(SDL_Event& event)
    {
        SDL_Keycode key = event.key.keysym.sym;

        switch(key)
        {
            case SDLK_1:
                m_BrushType = BrushType::Pixel;
            break;
            case SDLK_2:
                m_BrushType = BrushType::Circular;
            break;
            case SDLK_3:
                m_BrushType = BrushType::Rectangular;
            break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                m_ShiftDown = true;
            break;
        }
    }

    void UserInterface::KeyUp(SDL_Event& event)
    {
        SDL_Keycode key = event.key.keysym.sym;

        switch(key)
        {
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                m_ShiftDown = false;
            break;
        }
    }

    void UserInterface::MouseDown(SDL_Event& event)
    {
        uint8_t button = event.button.button;

        switch(button)
        {
            case SDL_BUTTON_LEFT:
                m_Paint = true;
            break;
            case SDL_BUTTON_RIGHT:
                m_Erase = true;
            break;
        }
    }

    void UserInterface::MouseUp(SDL_Event& event)
    {
        uint8_t button = event.button.button;
        switch(button)
        {
            case SDL_BUTTON_LEFT:
                m_Paint = false;
            break;
            case SDL_BUTTON_RIGHT:
                m_Erase = false;
            break;
        }
    }

    void UserInterface::MouseWheel(SDL_Event& e)
    {
        SDL_MouseWheelEvent wheel = e.wheel;
        
        if(wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
        {
            wheel.x *= -1;
            wheel.y *= -1;
        }

        if(m_ShiftDown)
        {
            m_BrushSize = MMath::Clamp(m_BrushSize + wheel.y, 3.f, 30.f);
        }
        else
        {
            m_ElementID = MMath::Clamp(m_ElementID + wheel.y * -1, 0.f, 4.f);
            std::cout << "Current element ID: " << m_ElementID << std::endl;
        }
    }

    MMath::i32Vec2 UserInterface::MousePosition() const
    {
        float mouseXF, mouseYF;
        SDL_GetMouseState(&mouseXF, &mouseYF);
        
        int mouseX = MMath::Clamp<int>(static_cast<int>(mouseXF), 0, m_Spec.WindowSize.x - 1);
        int mouseY = MMath::Clamp<int>(static_cast<int>(mouseYF), 0, m_Spec.WindowSize.y - 1);

        return MMath::i32Vec2(mouseX, mouseY);
    }

    void UserInterface::HandleInput() const 
    {
        if(!m_Paint && !m_Erase)
            return;

        switch(m_BrushType)
        {
            case BrushType::Pixel:
            {
                m_World.PlaceParticle(SelectedElement(), MousePosition());
            } break;
            case BrushType::Circular:
            {
                MMath::i32Vec2 center = MousePosition();
                for(int i = -m_BrushSize; i < m_BrushSize; i++)
                {
                    for(int j = m_BrushSize; j > -m_BrushSize; j--)
                    {
                        MMath::i32Vec2 position(center.x + i, center.y + j);
                        MMath::f32Vec2 offset(i ,j);

                        float distance = offset.Length();

                        float circleMargin = 0.3f;
                        if(distance <= (m_BrushSize - circleMargin))
                            m_World.PlaceParticle(SelectedElement(), position);
                    }
                }
            } break;
            case BrushType::Rectangular:
            {
                MMath::i32Vec2 center = MousePosition();
                for(int i = -m_BrushSize; i < m_BrushSize; i++)
                {
                    for(int j = m_BrushSize; j > -m_BrushSize; j--)
                    {
                        MMath::i32Vec2 position(center.x + i, center.y + j);
                        m_World.PlaceParticle(SelectedElement(), position);
                    }
                }
            } break;
        }
    }

    Particle* UserInterface::SelectedElement() const
    {
        if(m_Erase)
            return new NullParticle;

        switch(static_cast<int>(m_ElementID))
        {
            case 0:
                return new Sand;
            case 1:
                return new Rock;
            case 2:
                return new Water;
            default:
                return new NullParticle;
        }
    }
}