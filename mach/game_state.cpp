#include "game_state.hpp"

#include "event_data.hpp"
#include "system_event_data.hpp"
#include "game_data.hpp"

#include <iostream>

//---------------------------------------------------------------------------
// Starting_State
//---------------------------------------------------------------------------
// The state the game is initialised in.

mach::Starting_State::Starting_State() :
  Abstract_Game_State{},
  m_timer{0.0}
{}

mach::Starting_State::~Starting_State() = default;

void mach::Starting_State::enter(Game_Data& a_game_data)
{
  std::cout << "mach::Starting_State::enter" << std::endl;
  a_game_data.set_background_colour(Colour_RGBA{ 125,0,0,255 });


  std::cout 
    << "The window will display a red screen for 2 seconds." << std::endl
    << "All events are ignrored in this phase." << std::endl;
}

void mach::Starting_State::exit(Game_Data& a_game_data)
{
  std::cout << "mach::Starting_State::exit" << std::endl;
}

void mach::Starting_State::advance(Game_Data& a_game_data, Event_Data const& a_event_data, double a_period)
{
  static double const s_end_time_seconds{2.0};

  // advance the timer by period.
  m_timer += a_period;
  // if the timer has passed the end
  if (m_timer > s_end_time_seconds)
  {
    //  switch to the next state.
    // for now just change to the idle state.
    a_game_data.state_change(std::make_unique<Idle_State>());

  }
  // else
  //  update the background colour based on elapsed time.


}


//---------------------------------------------------------------------------
// Idle_State
//---------------------------------------------------------------------------
// Test state that just renders a screen. It can transition to Quit_State.

mach::Idle_State::Idle_State() :
  Abstract_Game_State{},
  m_timer{ 0.0 },
  m_value{ 0 }
{}

mach::Idle_State::~Idle_State() = default;

void mach::Idle_State::enter(Game_Data& a_game_data)
{
  std::cout << "mach::Idle_State::enter" << std::endl;
  a_game_data.set_background_colour(Colour_RGBA{ 0,0,0,255 });

  std::cout
    << "The window will cycle from black to white over 10 seconds, then repeat until quitting." << std::endl
    << "To trigger a quit event, close the window." << std::endl;
}

void mach::Idle_State::exit(Game_Data& a_game_data)
{
  std::cout << "mach::Idle_State::exit" << std::endl;
}

void mach::Idle_State::advance(Game_Data& a_game_data, Event_Data const& a_event_data, double a_period)
{
  if (a_event_data.system_event_data().is_quitting())
  {
    a_game_data.state_change(std::make_unique<Quit_State>());
  }
  else
  {
    // move from black to white every 10 seconds
    static double const c_cycle{ 10.0 };

    // Advance the timer
    m_timer += a_period;

    // Loop around if need be
    if (m_timer > c_cycle)
    {
      m_timer -= c_cycle;
    }

    // Calculate the value
    int l_value = static_cast<int>(m_timer / c_cycle * 255);

    a_game_data.set_background_colour(Colour_RGBA{ l_value,l_value,l_value,255 });
  }
}


//---------------------------------------------------------------------------
// Quit_State
//---------------------------------------------------------------------------
// The final state the game can get in. It contains nothing, does nothing
// and rendering it produces a black screen.


mach::Quit_State::Quit_State() :
  Abstract_Game_State{},
  m_timer{ 0.0 }
{}

mach::Quit_State::~Quit_State() = default;

void mach::Quit_State::enter(Game_Data& a_game_data)
{
  std::cout << "mach::Quit_State::enter" << std::endl;
  a_game_data.set_background_colour(Colour_RGBA{0,0,100,255});

  std::cout
    << "The window will be blue for one second then quit." << std::endl;
}

void mach::Quit_State::exit(Game_Data& a_game_data)
{
  std::cout << "mach::Quit_State::exit" << std::endl;
}

void mach::Quit_State::advance(Game_Data& a_game_data, Event_Data const& a_event_data, double a_period)
{
  static double const s_delay_time{1.0};
  m_timer += a_period;
  if (m_timer >= s_delay_time)
  {
    // Setting this flag is the only way to break the game loop.
    a_game_data.set_quitting(true);
  }
}
