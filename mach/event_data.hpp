#ifndef MACH_EVENT_DATA_HPP
#define MACH_EVENT_DATA_HPP

#include "system_event_data.hpp"

namespace mach
{
  //---------------------------------------------------------------------------
  // Event_Data
  //---------------------------------------------------------------------------
  // When the application processes events all data is cached into this object.
  // This allows for a layer of event interpretation that can be changed, 
  // while subsections of that can be split off as seperate things
  // e.g. This could contain mouse data, gamepad data, window resizing data, 
  // which are all seperate and may not be present on all platforms.

  class Event_Data
  {
  private:
    // Member Data
    //============================================================
    System_Event_Data m_system_event_data;

  public:
    // Special 6
    //============================================================
    Event_Data();

    // Interface
    //============================================================
    System_Event_Data& system_event_data() noexcept;
    System_Event_Data const& system_event_data() const noexcept;
        
    void swap(Event_Data& a_other) noexcept;

    // Copy this while reseting all single frame data.
    Event_Data clear_copy() const;
  };

  void swap(Event_Data& a_lhs, Event_Data& a_rhs) noexcept;
} // namespace mach

#endif // MACH_EVENT_DATA_HPP
