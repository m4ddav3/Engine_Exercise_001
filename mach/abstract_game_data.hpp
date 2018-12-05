#ifndef MACH_ABSTRACT_GAME_DATA_HPP
#define MACH_ABSTRACT_GAME_DATA_HPP

#include <cstdint>

namespace mach
{
  class Abstract_Renderer;
  class Event_Data;

  //---------------------------------------------------------------------------
  // Abstract_Game_Data
  //---------------------------------------------------------------------------
  // Defines the rendering interface.

  class Abstract_Game_Data
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Game_Data() = 0;

    // Virtual Interface
    //============================================================
    // Is the game quitting? This may not be the case even if a 
    // quit event was recieved.
    virtual bool is_quitting() const = 0;
    virtual bool not_quitting() const = 0;

    // Return the current tick number since construction. Tick is
    // advanced by 1 each time advance is called.
    virtual std::uintmax_t tick() const = 0;

    // Return the Event_Data used in the last tick.
    virtual Event_Data const& event_data() const = 0;

    // Return the length in seconds of the period of the last tick.
    virtual double period() const = 0;

    // Advance the game state one tick using the supplied data and 
    // time period.
    virtual void advance(Event_Data const& a_event_data, double a_period) = 0;

    // Rather than expose game state we send the renderer to this 
    // do the rendering.
    virtual void render(Abstract_Renderer& a_renderer) const = 0;
  }; 
  
} // namespace mach

//------------------------------------------------------------------------------------------------------------------------------------------------------

inline
mach::Abstract_Game_Data::~Abstract_Game_Data() = default;

#endif // MACH_ABSTRACT_GAME_DATA_HPP
