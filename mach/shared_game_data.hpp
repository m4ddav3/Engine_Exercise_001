#ifndef MACH_SHARED_GAME_DATA_HPP
#define MACH_SHARED_GAME_DATA_HPP

#include "event_data.hpp"

#include <cstdint>

namespace mach
{
  //---------------------------------------------------------------------------
  // Shared_Game_Data
  //---------------------------------------------------------------------------
  // Implementation of parts of the game engine that are unlikely to change and
  // are likely to be the same regardless of engine architechture.

  class Shared_Game_Data
  {
  private:
    // Member Data
    //============================================================   
    bool m_quit_flag;
    double m_period;
    std::uintmax_t m_tick;
    Event_Data m_event_data;

  public:
    // Special 6
    //============================================================
    Shared_Game_Data();
    explicit Shared_Game_Data(Event_Data const& a_event_data);

    // Interface
    //============================================================
    // Is the game quitting? This may not be the case even if a 
    // quit event was recieved.
    bool quit_flag() const noexcept;
    void set_quit_flag(bool a_value) noexcept;

    // Return the current tick number since construction. Tick is
    // advanced by 1 each time advance is called.
    std::uintmax_t tick() const noexcept;

    // Return the Event_Data used in the last tick.
    Event_Data const& event_data() const noexcept;

    // Return the length in seconds of the period of the last tick.
    double period() const noexcept;

    // Advance the tick by 1 and replace the internally stored
    // Event_Data and period with that which is supplied.
    void advance(Event_Data const& a_event_data, double a_period);
  };

} // namespace mach

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MACH_SHARED_GAME_DATA_HPP
