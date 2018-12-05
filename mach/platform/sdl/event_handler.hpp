#ifndef MACH_PLATFORM_SDL_EVENT_HANDLER_HPP
#define MACH_PLATFORM_SDL_EVENT_HANDLER_HPP

#include "system.hpp"
#include "../../abstract_event_handler.hpp"

namespace mach
{
  class Event_Data;

  namespace platform
  {
    namespace sdl
    {
      //---------------------------------------------------------------------------
      // Event_Handler
      //---------------------------------------------------------------------------

      class Event_Handler :
        public Abstract_Event_Handler
      {
      private:
        // Member Data
        //============================================================   
        Event_Subsystem m_event_subsystem;

      public:
        // Special 6
        //============================================================
        explicit Event_Handler(System const& a_system);
        ~Event_Handler() override final;

        // Interface
        //============================================================
        // Using the supplied data as a starting point, gather all 
        // unprocessed events and overwrite the supplied data with the
        // result. 
        void handle_events(Event_Data& a_data) override final;
      };
    } // namespace sdl
  } // namespace platform
} // namespace mach

  //------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MACH_PLATFORM_SDL_EVENT_HANDLER_HPP
