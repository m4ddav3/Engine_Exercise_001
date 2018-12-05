#include "system.hpp"

#include <SDL.h>

#include <stdexcept>
#include <type_traits>
#include <cassert>

//------------------------------------------------------------------------------------------------------------------------------------------------------

namespace mach
{
  namespace platform
  {
    namespace sdl
    {
      //---------------------------------------------------------------------------
      // System::Implementation
      //---------------------------------------------------------------------------
      // Does the actual work.

      class System::Implementation
      {
      public:
        // Special 6
        //============================================================
        Implementation();
        ~Implementation();
      };
    }
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// System::Implementation
//---------------------------------------------------------------------------
// Does the actual work.

// Special 6
//============================================================
mach::platform::sdl::System::Implementation::Implementation()
{
  // Initialise the system, stop if fails.
  if (SDL_Init(0) != 0)
  {
    throw std::runtime_error{ "SDL initialisation failed." };
  }
}

mach::platform::sdl::System::Implementation::~Implementation()
{
  // Quit SDL
  SDL_Quit();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// System
//---------------------------------------------------------------------------
// RAII class for SDL startup and shutdown with reference counting.

// Special 6
//============================================================
mach::platform::sdl::System::System() :
  m_implementation{ std::make_shared<Implementation>() }
{
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


/*
SDL_INIT_TIMER
timer subsystem

SDL_INIT_AUDIO
audio subsystem

SDL_INIT_VIDEO
video subsystem; automatically initializes the events subsystem

SDL_INIT_JOYSTICK

joystick subsystem; automatically initializes the events subsystem

SDL_INIT_HAPTIC
haptic(force feedback) subsystem

SDL_INIT_GAMECONTROLLER

controller subsystem; automatically initializes the joystick subsystem

SDL_INIT_EVENTS

events subsystem
*/


namespace mach
{
  namespace platform
  {
    namespace sdl
    {
      //---------------------------------------------------------------------------
      // Subsystem
      //---------------------------------------------------------------------------
      // Forward declared implementation class that is shared between all subsystems.

      class Subsystem
      {
      private:
        static_assert(std::is_same_v<std::uint32_t, ::Uint32>, "Bad typematch on hiding the SDL type ::Uint32, it is not the same as std::uint32_t");

        // Member Data
        //============================================================ 
        std::uint32_t m_flag;
        System m_system;

      public:
        // Special 6
        //============================================================
        Subsystem(std::uint32_t a_flag, System const& a_system);
        ~Subsystem();
      };
    }
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// System::Implementation
//---------------------------------------------------------------------------
// Does the actual work.

// Special 6
//============================================================
mach::platform::sdl::Subsystem::Subsystem(std::uint32_t a_flag, System const& a_system) :
  m_flag{ a_flag },
  m_system{ a_system }
{
  // Initialise the system, stop if fails.
  if (SDL_InitSubSystem(m_flag) != 0)
  {
    throw std::runtime_error{ "SDL initialisation failed." };
  }
}

mach::platform::sdl::Subsystem::~Subsystem()
{
  SDL_QuitSubSystem(m_flag);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Audio_Subsystem
//---------------------------------------------------------------------------
// RAII class for SDL subsystem startup and shutdown with reference counting.

// Special 6
//============================================================
mach::platform::sdl::Audio_Subsystem::Audio_Subsystem(System const& a_system) :
  m_data{ std::make_shared<Subsystem>(SDL_INIT_AUDIO, a_system) }
{}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Event_Subsystem
//---------------------------------------------------------------------------
// RAII class for SDL subsystem startup and shutdown with reference counting.

// Special 6
//============================================================
mach::platform::sdl::Event_Subsystem::Event_Subsystem(System const& a_system) :
  m_data{ std::make_shared<Subsystem>(SDL_INIT_EVENTS, a_system) }
{}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Gamecontroller_Subsystem
//---------------------------------------------------------------------------
// RAII class for SDL subsystem startup and shutdown with reference counting.
// Automatically initializes the joystick subsystem.

// Special 6
//============================================================
mach::platform::sdl::Gamecontroller_Subsystem::Gamecontroller_Subsystem(System const& a_system) :
  m_data{ std::make_shared<Subsystem>(SDL_INIT_GAMECONTROLLER, a_system) }
{}
//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Haptic_Subsystem
//---------------------------------------------------------------------------
// RAII class for SDL subsystem startup and shutdown with reference counting.

// Special 6
//============================================================
mach::platform::sdl::Haptic_Subsystem::Haptic_Subsystem(System const& a_system) :
  m_data{ std::make_shared<Subsystem>(SDL_INIT_HAPTIC, a_system) }
{}
//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Joystick_Subsystem
//---------------------------------------------------------------------------
// RAII class for SDL subsystem startup and shutdown with reference counting.
// Automatically initializes the events subsystem.

// Special 6
//============================================================
mach::platform::sdl::Joystick_Subsystem::Joystick_Subsystem(System const& a_system) :
  m_data{ std::make_shared<Subsystem>(SDL_INIT_JOYSTICK, a_system) }
{}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Timer_Subsystem
//---------------------------------------------------------------------------
// RAII class for SDL subsystem startup and shutdown with reference counting.

// Special 6
//============================================================
mach::platform::sdl::Timer_Subsystem::Timer_Subsystem(System const& a_system) :
  m_data{ std::make_shared<Subsystem>(SDL_INIT_TIMER, a_system) }
{}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Video_Subsystem
//---------------------------------------------------------------------------
// RAII class for SDL subsystem startup and shutdown with reference counting.
// Automatically initializes the events subsystem.

// Special 6
//============================================================
mach::platform::sdl::Video_Subsystem::Video_Subsystem(System const& a_system) :
  m_data{ std::make_shared<Subsystem>(SDL_INIT_VIDEO, a_system) }
{}