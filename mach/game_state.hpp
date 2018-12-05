#ifndef MACH_GAME_STATE_HPP
#define MACH_GAME_STATE_HPP

#include "abstract_game_state.hpp"
#include "colour.hpp"

#include <cstdint>

namespace mach
{
  //---------------------------------------------------------------------------
  // Starting_State
  //---------------------------------------------------------------------------
  // The state the game is initialised in.
  class Starting_State :
    public Abstract_Game_State
  {
  private:
    double m_timer;
  public:
    Starting_State();
    ~Starting_State() override final;

    void enter(Game_Data& a_game_data) override final;
    void exit(Game_Data& a_game_data) override final;
    void advance(Game_Data& a_game_data, Event_Data const& a_event_data, double a_period) override final;
  };

  //---------------------------------------------------------------------------
  // Idle_State
  //---------------------------------------------------------------------------
  // Test state that just renders a screen. It can transition to Quit_State.
  class Idle_State :
    public Abstract_Game_State
  {
  private:
    double m_timer;
    int m_value;
  public:
    Idle_State();
    ~Idle_State() override final;

    void enter(Game_Data& a_game_data) override final;
    void exit(Game_Data& a_game_data) override final;
    void advance(Game_Data& a_game_data, Event_Data const& a_event_data, double a_period) override final;
  };

  //---------------------------------------------------------------------------
  // Quit_State
  //---------------------------------------------------------------------------
  // The final state the game can get in. It contains nothing, does nothing
  // and rendering it produces a black screen.
  class Quit_State :
    public Abstract_Game_State
  {
  private:
    double m_timer;
  public:
    Quit_State();
    ~Quit_State() override final;

    void enter(Game_Data& a_game_data) override final;
    void exit(Game_Data& a_game_data) override final;
    void advance(Game_Data& a_game_data, Event_Data const& a_event_data, double a_period) override final;
  };

} // namespace mach

#endif // MACH_GAME_STATE_HPP
