#ifndef MACH_GAME_DATA_HPP
#define MACH_GAME_DATA_HPP

#include "abstract_game_data.hpp"
#include "abstract_game_state.hpp"
#include "shared_game_data.hpp"
#include "colour.hpp"

#include <memory>

namespace mach
{
  class Abstract_Renderer;

  //---------------------------------------------------------------------------
  // Game_Data
  //---------------------------------------------------------------------------
  // Contains all the game data and manages it.

  class Game_Data :
    public Abstract_Game_Data
  {
  private:
    // Member Data
    //============================================================   
    Shared_Game_Data m_data;
    std::unique_ptr<Abstract_Game_State> m_state; // simple for now...
    Colour_RGBA m_background_colour;

  public:
    // Special 6
    //============================================================
    Game_Data();
    explicit Game_Data(Event_Data const& a_event_data);
    ~Game_Data() override final;
    
    // Virtual Interface
    //============================================================
    // Is the game quitting? This may not be the case even if a 
    // quit event was recieved.
    bool is_quitting() const override final;
    bool not_quitting() const override final;

    // Return the current tick number since construction. Tick is
    // advanced by 1 each time advance is called.
    std::uintmax_t tick() const override final;

    // Return the Event_Data used in the last tick.
    Event_Data const& event_data() const override final;

    // Return the length in seconds of the period of the last tick.
    double period() const override final;

    // Advance the game state one tick using the supplied data and 
    // time period.
    void advance(Event_Data const& a_event_data, double a_period) override final;

    // Rather than expose game state we send the renderer to this 
    // do the rendering.
    void render(Abstract_Renderer& a_renderer) const override final;

    // Interface for Abstract_Game_State
    //============================================================
    void set_quitting(bool a_value) noexcept;
    void set_background_colour(Colour_RGBA a_colour) noexcept;
    
    void abstract_state_change(std::unique_ptr<Abstract_Game_State>&& a_new_state);

    template <typename T_State_Type>
    void state_change(std::unique_ptr<T_State_Type>&& a_new_state)
    {
      // should probably be std::enable_if
      static_assert(std::is_base_of_v<Abstract_Game_State, T_State_Type>,
        "Cannot use a class that is not derived from Abstract_Game_State");
      abstract_state_change(std::unique_ptr<Abstract_Game_State>{ std::move(a_new_state) });
    }
  };

} //namespace mach

#endif // MACH_SYSTEM_DATA_HPP