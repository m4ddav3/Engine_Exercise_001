#include "game_data.hpp"

#include "abstract_renderer.hpp"
#include "abstract_game_state.hpp"
#include "game_state.hpp"
#include "colour.hpp"

#include <cassert>

//---------------------------------------------------------------------------
// Game_Data
//---------------------------------------------------------------------------
// Contains all the game data and manages it.

// Special 6
//============================================================
mach::Game_Data::Game_Data() :
  m_data{},
  m_state{ std::make_unique<Starting_State>() }
{
  m_state->enter(*this);
}

mach::Game_Data::Game_Data(Event_Data const& a_event_data) :
  m_data{ a_event_data  },
  m_state{ std::make_unique<Starting_State>() }
{
  m_state->enter(*this);
}

mach::Game_Data::~Game_Data() = default;

// Virtual Interface
//============================================================
// Is the game quitting? This may not be the case even if a 
// quit event was recieved.
bool mach::Game_Data::is_quitting() const
{
  return m_data.quit_flag();
}

bool mach::Game_Data::not_quitting() const
{
  return !(m_data.quit_flag());
}

// Return the current tick number since construction. Tick is
// advanced by 1 each time advance is called.
std::uintmax_t mach::Game_Data::tick() const
{
  return m_data.tick();
}

// Return the Event_Data used in the last tick.
mach::Event_Data const& mach::Game_Data::event_data() const
{
  return m_data.event_data();
}

// Return the length in seconds of the period of the last tick.
double mach::Game_Data::period() const
{
  return m_data.period();
}

// Advance the game state one tick using the supplied data and 
// time period.
void mach::Game_Data::advance(Event_Data const& a_event_data, double a_period)
{
  assert(m_state);
  m_state->advance(*this, a_event_data, a_period);
  m_data.advance(a_event_data, a_period);
}

// Rather than expose game state we send the renderer to this 
// do the rendering.
void mach::Game_Data::render(Abstract_Renderer& a_renderer) const
{
  a_renderer.begin_render();
  // Where the actual rendering happens....
  a_renderer.clear(m_background_colour);
  // You would need to have an editable collection of things to the renderer
  // or have an interface to get that from the states.
  //a_renderer.screen_render_rect(100, 100, 100, 100, Colour_RGBA{0,125,0,255});

  a_renderer.end_render();
}


// Interface for Abstract_Game_State
//============================================================
void mach::Game_Data::set_quitting(bool a_value) noexcept
{
  m_data.set_quit_flag(a_value);
}

void mach::Game_Data::set_background_colour(Colour_RGBA a_colour) noexcept
{
  m_background_colour = a_colour;
}

void mach::Game_Data::abstract_state_change(std::unique_ptr<Abstract_Game_State>&& a_new_state)
{
  if (a_new_state)
  {
    m_state->exit(*this);
    a_new_state->enter(*this);
    std::swap(m_state, a_new_state);
  }
}

