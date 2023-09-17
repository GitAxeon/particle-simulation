#include "UserInterface.h"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

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
    }

    MMath::i32Vec2 UserInterface::MousePosition() const
    {
        float mouseXF, mouseYF;
        SDL_GetMouseState(&mouseXF, &mouseYF);
        
        int mouseX = MMath::Clamp<int>(static_cast<int>(mouseXF), 0, m_Spec.WindowSize.x - 1);
        int mouseY = MMath::Clamp<int>(static_cast<int>(mouseYF), 0, m_Spec.WindowSize.y - 1);

        return MMath::i32Vec2(mouseX, mouseY);
    }

    void UserInterface::HandleInput() 
    {
        switch(m_CurrentBrushTypeNumber)
        {
            case 0:
                m_BrushType = BrushType::Pixel;
            break;
            case 1:
                m_BrushType = BrushType::Circular;
            break;
            case 2:
                m_BrushType = BrushType::Rectangular;
            break;
        };
        if(!m_Paint && !m_Erase)
            return;

        switch(m_BrushType)
        {
            case BrushType::Pixel:
            {
                bool res = m_World.PlaceParticle(m_World.GetParticleDatabase().Get(SelectedElement()) , MousePosition());
                
                if(res)
                    std::cout << "Placed particle id: " << SelectedElement() << std::endl;
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
                            m_World.PlaceParticle(m_World.GetParticleDatabase().Get(SelectedElement()), position);
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
                        m_World.PlaceParticle(m_World.GetParticleDatabase().Get(SelectedElement()), position);
                    }
                }
            } break;
        }
    }

    ParticleID UserInterface::SelectedElement() const
    {
        if(m_Erase)
            return 0;

        switch(m_ElementID)
        {
            case 0:
                return 1;
            case 1:
                return 2;
            case 2:
                return 3;
            default:
                return 4;
        }
    }

    void UserInterface::Render(float deltaTime)
    {
        // ImGui::SetNextWindowSize(ImVec2(250, 125));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        flags |= ImGuiWindowFlags_NoTitleBar;
        flags |= ImGuiWindowFlags_NoMove;
        flags |= ImGuiWindowFlags_NoResize;
        flags |= ImGuiWindowFlags_NoSavedSettings;
        flags |= ImGuiWindowFlags_AlwaysAutoResize;
        flags |= ImGuiWindowFlags_NoNav;

        ImGui::Begin("Tools!", nullptr, flags);

        ImGui::Text("Current tool: %s", (!m_Erase ? "Brush" : "Eraser"));

        ImGui::Text("Brush type"); ImGui::SameLine();
        const char* brushTypes[] = { "Pixel", "Circular", "Rectangular" };
        ImGui::Combo("##BrushTypeCombo", &m_CurrentBrushTypeNumber, brushTypes, 3, 3);

        if(m_CurrentBrushTypeNumber != 0)
        {   
            ImGui::Text("Size"); ImGui::SameLine();
            ImGui::SliderInt("##BrushSizeSlider", &m_BrushSize, 3, 30);
        }

        ImGui::Text("Element"); ImGui::SameLine();
        const char* elements[] = { "Sand", "Rock", "Water", "Null" };
        ImGui::Combo("##ElementCombo", &m_ElementID, elements, 4, 4);
        
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(
            m_World.Info.GetWidth() - 35,
            0
        ));

        ImGuiWindowFlags fpsFlags = ImGuiWindowFlags_None;
        fpsFlags |= ImGuiWindowFlags_NoNav;
        fpsFlags |= ImGuiWindowFlags_AlwaysAutoResize;
        fpsFlags |= ImGuiWindowFlags_NoResize;
        fpsFlags |= ImGuiWindowFlags_NoBackground;
        fpsFlags |= ImGuiWindowFlags_NoTitleBar;

        ImGui::Begin("FPS", nullptr, fpsFlags);
        
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,255,255,255));
            ImGui::Text("%.0f", 1.0/deltaTime);
        ImGui::PopStyleColor();
        
        ImGui::End();
    }
}