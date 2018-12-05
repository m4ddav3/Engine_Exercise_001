#ifndef MACH_ABSTRACT_GAME_STATE_HPP
#define MACH_ABSTRACT_GAME_STATE_HPP

#include <memory>
#include <type_traits>

namespace mach
{
  class Game_Data;
  class Event_Data;
  class Colour_RGBA;

  //---------------------------------------------------------------------------
  // Abstract_Game_State
  //---------------------------------------------------------------------------
  // Base class for game states. 

  class Abstract_Game_State
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Game_State() = 0;

    // Virtual Interface
    //============================================================
    // Called when this is being installed as the current state for the supplied
    // Game_Data.
    virtual void enter(Game_Data& a_game_data) = 0;

    // Called when this is being removed as the current state for the supplied
    // Game_Data.
    virtual void exit(Game_Data& a_game_data) = 0;
    
    // Called when the supplied Game_Data is advancing by a tick, using the 
    // supplied System_Data, Input_Data and time period in seconds.
    virtual void advance(Game_Data& a_game_data, Event_Data const& a_event_data, double a_period) = 0;
  };


  // generifying
  template 
  <
    typename T_Data,
    typename T_Input
  >
  class Abstract_Finite_State
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Finite_State() = default;

    // Virtual Interface
    //============================================================
    // Called when this is being installed as the current state for the supplied
    // data.
    virtual void enter(T_Data& a_data) = 0;

    // Called when this is being removed as the current state for the supplied
    // data.
    virtual void exit(T_Data& a_data) = 0;

    // Called when the supplied data is advancing by a tick, using the 
    // supplied input and time period in seconds.
    virtual void advance(T_Data& a_data, T_Input const& a_input, double a_period) = 0;
  };
  
} //namespace mach

#endif // MACH_ABSTRACT_GAME_STATE_HPP