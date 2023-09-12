#include "UserInterface.h"

namespace ParticleSimulation
{
    void UserInterface::KeyDown(SDL_Event& event)
    {
        SDL_Keycode key = event.key.keysym.sym;

        switch(key)
        {
            case SDLK_p:

            break;
        }
    }

    void UserInterface::KeyUp(SDL_Event& event)
    {

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
        
        if(wheel.direction != SDL_MOUSEWHEEL_FLIPPED)
        {
            wheel.x *= -1;
            wheel.y *= -1;
        }

        m_ElementID += wheel.y;
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
        if(m_Erase)
        {
            m_World.PlaceParticle(new NullParticle, MousePosition());
        }
        else if(m_Paint)
        {
            m_World.PlaceParticle(new Sand, MousePosition());
        }
    }
}