#include "shared_game_data.hpp"

//---------------------------------------------------------------------------
// Shared_Game_Data
//---------------------------------------------------------------------------
// Implementation of parts of the game engine that are unlikely to change and
// are likely to be the same regardless of engine architechture.

// Special 6
//============================================================
mach::Shared_Game_Data::Shared_Game_Data() :
  m_quit_flag{ false },
  m_period{ 0.0 }, 
  m_tick{ 0 },
  m_event_data{}
{}
mach::Shared_Game_Data::Shared_Game_Data(Event_Data const& a_event_data) :
  m_quit_flag{ false },
  m_period{ 0.0 },
  m_tick{ 0 },
  m_event_data{ a_event_data }
{}

// Interface
//============================================================
// Is the game quitting? This may not be the case even if a 
// quit event was recieved.
bool mach::Shared_Game_Data::quit_flag() const noexcept
{
  return m_quit_flag;
}

void mach::Shared_Game_Data::set_quit_flag(bool a_value) noexcept
{
  m_quit_flag = a_value;
}

// Return the current tick number since construction. Tick is
// advanced by 1 each time advance is called.
std::uintmax_t mach::Shared_Game_Data::tick() const noexcept
{
  return m_tick;
}

// Return the Event_Data used in the last tick.
mach::Event_Data const& mach::Shared_Game_Data::event_data() const noexcept
{
  return m_event_data;
}

// Return the length in seconds of the period of the last tick.
double mach::Shared_Game_Data::period() const noexcept
{
  return m_period;
}

// Advance the tick by 1 and replace the internally stored
// Event_Data and period with that which is supplied.
void mach::Shared_Game_Data::advance(Event_Data const& a_event_data, double a_period)
{
  m_event_data = a_event_data.clear_copy();
  m_period = a_period;
  ++m_tick;
}
