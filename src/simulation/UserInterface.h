#pragma once

#include "World.h"

#include <SDL3/SDL.h>

struct ApplicationSpec
{
public:
    ApplicationSpec(MMath::i32Vec2 windowSize = MMath::i32Vec2(640, 360))
        : WindowSize(windowSize) { }

public:
    MMath::i32Vec2 WindowSize;
};

namespace ParticleSimulation
{
    enum class BrushType { Pixel, Circular, Rectangular };
    enum class Tool { Brush, Eraser };

    class UserInterface
    {
    public:
        UserInterface(World& world, const ApplicationSpec& spec) : 
            m_World(world), m_Spec(spec), 
            m_BrushType(BrushType::Circular), m_CurrentTool(Tool::Brush) { };

        void HandleInput();
        void KeyDown(SDL_Event& event);
        void KeyUp(SDL_Event& event);
        void MouseDown(SDL_Event& event);
        void MouseUp(SDL_Event& event);
        void MouseWheel(SDL_Event& event);
        MMath::i32Vec2 MousePosition() const;

        void Render(float deltaTime);

        Tool CurrentTool() const { return m_CurrentTool; }
        BrushType CurrentBrush() const { return m_BrushType; }
        int BrushSize() const { return m_BrushSize; }
    
    private:
        ElementID SelectedElement() const;

    private:
        World& m_World;
        ApplicationSpec m_Spec;

        BrushType m_BrushType;
        Tool m_CurrentTool;
        int m_CurrentBrushTypeNumber = 0;

        int m_BrushSize = 3;

        bool m_ShiftDown = false;
        bool m_Paint = false;
        bool m_Erase = false;
        int m_ElementID = 0;
    };
}