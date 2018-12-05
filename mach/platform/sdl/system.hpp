#ifndef MACH_PLATFORM_SDL_SYSTEM_HPP
#define MACH_PLATFORM_SDL_SYSTEM_HPP

#include <memory>

namespace mach
{
  namespace platform
  {
    namespace sdl
    {
      //---------------------------------------------------------------------------
      // System
      //---------------------------------------------------------------------------
      // RAII class for SDL startup and shutdown with reference counting.

      class System
      {
      private:
        // Member Data
        //============================================================   
        class Implementation;
        std::shared_ptr<Implementation> m_implementation;

      public:
        // Special 6
        //============================================================
        System();
      };

      //---------------------------------------------------------------------------
      // Subsystem
      //---------------------------------------------------------------------------
      // Forward declared implementation class that is shared between all subsystems.

      class Subsystem;

      //---------------------------------------------------------------------------
      // Audio_Subsystem
      //---------------------------------------------------------------------------
      // RAII class for SDL subsystem startup and shutdown with reference counting.

      class Audio_Subsystem
      {
      private:
        // Member Data
        //============================================================   
        std::shared_ptr<Subsystem> m_data;

      public:
        // Special 6
        //============================================================
        explicit Audio_Subsystem(System const& a_system);
      };

      //---------------------------------------------------------------------------
      // Event_Subsystem
      //---------------------------------------------------------------------------
      // RAII class for SDL subsystem startup and shutdown with reference counting.

      class Event_Subsystem
      {
      private:
        // Member Data
        //============================================================   
        std::shared_ptr<Subsystem> m_data;

      public:
        // Special 6
        //============================================================
        explicit Event_Subsystem(System const& a_system);
      };

      //---------------------------------------------------------------------------
      // Gamecontroller_Subsystem
      //---------------------------------------------------------------------------
      // RAII class for SDL subsystem startup and shutdown with reference counting.
      // Automatically initializes the joystick subsystem.

      class Gamecontroller_Subsystem
      {
      private:
        // Member Data
        //============================================================   
        std::shared_ptr<Subsystem> m_data;

      public:
        // Special 6
        //============================================================
        explicit Gamecontroller_Subsystem(System const& a_system);
      };

      //---------------------------------------------------------------------------
      // Haptic_Subsystem
      //---------------------------------------------------------------------------
      // RAII class for SDL subsystem startup and shutdown with reference counting.

      class Haptic_Subsystem
      {
      private:
        // Member Data
        //============================================================   
        std::shared_ptr<Subsystem> m_data;

      public:
        // Special 6
        //============================================================
        explicit Haptic_Subsystem(System const& a_system);
      };

      //---------------------------------------------------------------------------
      // Joystick_Subsystem
      //---------------------------------------------------------------------------
      // RAII class for SDL subsystem startup and shutdown with reference counting.
      // Automatically initializes the events subsystem.

      class Joystick_Subsystem
      {
      private:
        // Member Data
        //============================================================   
        std::shared_ptr<Subsystem> m_data;

      public:
        // Special 6
        //============================================================
        explicit Joystick_Subsystem(System const& a_system);
      };

      //---------------------------------------------------------------------------
      // Timer_Subsystem
      //---------------------------------------------------------------------------
      // RAII class for SDL subsystem startup and shutdown with reference counting.

      class Timer_Subsystem
      {
      private:
        // Member Data
        //============================================================   
        std::shared_ptr<Subsystem> m_data;

      public:
        // Special 6
        //============================================================
        explicit Timer_Subsystem(System const& a_system);
      };

      //---------------------------------------------------------------------------
      // Video_Subsystem
      //---------------------------------------------------------------------------
      // RAII class for SDL subsystem startup and shutdown with reference counting.
      // Automatically initializes the events subsystem.

      class Video_Subsystem
      {
      private:
        // Member Data
        //============================================================   
        std::shared_ptr<Subsystem> m_data;

      public:
        // Special 6
        //============================================================
        explicit Video_Subsystem(System const& a_system);
      };

    } // namespace sdl
  } // namespace platform
} // namespace mach

#endif // MACH_PLATFORM_SDL_SYSTEM_HPP