#ifndef MACH_GAME_LOOP_HPP
#define MACH_GAME_LOOP_HPP

#include <chrono>
#include <thread>

namespace mach
{
  class Abstract_Event_Handler;
  class Abstract_Renderer;
  class Abstract_Game_Data;

  //---------------------------------------------------------------------------
  // Unlocked_Sim_Unlocked_Render_Loop
  //---------------------------------------------------------------------------
  // Events->Update->Render->Present at the fastest speed possible.

  template <typename T_Event_Handler, typename T_Render_Window>
  class Unlocked_Sim_Unlocked_Render_Loop
  {
  private:
    T_Event_Handler & m_event_handler;
    T_Render_Window& m_render_window;
    Game_Data& m_game_data;

  public:
    Unlocked_Sim_Unlocked_Render_Loop
    (
      T_Event_Handler& a_event_handler,
      T_Render_Window& a_render_window,
      Game_Data& a_game_state
    ) :
      m_event_handler{ a_event_handler },
      m_render_window{ a_render_window },
      m_game_data{ a_game_state }
    {}

    void do_loop()
    {
      System_Event_Data l_system_data{};
      Input_Event_Data l_input_data{};

      while (m_game_data.not_quitting())
      {
        l_input_data = m_event_handler.handle_events(m_game_data.input_data());
        m_game_data.advance(l_input_data);

        m_render_window.render(m_game_data);
        m_render_window.present();
      }
    }
  };

  //---------------------------------------------------------------------------
  // Locked_Sim_Locked_Render_Loop
  //---------------------------------------------------------------------------
  // Events->Update->Render->Present X times per second.
  
  template <unsigned int t_simulate_frames_per_second>
  class Locked_Sim_Locked_Render_Loop
  {
  private:
    using Clock = std::chrono::steady_clock;
    using Duration = std::chrono::steady_clock::duration;
    using Period = typename Clock::period;
    using Time_Point = typename Clock::time_point;

    using Simulate_Ratio = std::ratio<1, t_simulate_frames_per_second>;
    using Simulate_Duration = std::chrono::duration<std::intmax_t, Simulate_Ratio>;
    static constexpr Simulate_Duration const c_tick{ 1 };
    
  public:
    void operator()(Abstract_Event_Handler& a_event_handler, Abstract_Renderer& a_renderer, Abstract_Game_Data& a_game_data) const
    {
      // Time of a tick in seconds.
      double const c_tick_seconds{ std::chrono::duration<double, std::ratio<1>>{c_tick}.count() };

      // We will write event data into this object each loop.
      Event_Data l_event_data{};

      // Initialise the timer.
      Time_Point l_next_tick{ Clock::now() };

      // Do the loop while the game is not quitting, which is a flag
      // held somewhere in game data.
      while (a_game_data.not_quitting())
      {
        // Process all the waiting events and write the data.
        a_event_handler.handle_events(l_event_data);
        
        // Advance the game data with the new event data.
        a_game_data.advance(l_event_data, c_tick_seconds);
        
        // Render the game data. If the game data or event data require
        // the renderer to have settings changed (e.g. resizing) then it
        // is the game data's responsiblity to do that, using the 
        // renderer's interface.
        a_game_data.render(a_renderer); // Not the right way to do this if we want to change renderer on the fly...

        // Present the frame to the screen.
        a_renderer.present();

        // Set the next tick time.
        l_next_tick += std::chrono::duration_cast<Duration>(c_tick);

        // Check if we are before or after that time.
        auto l_now = Clock::now();

        // If before
        if (l_now <= l_next_tick)
        {
          // We're done this tick.
          std::this_thread::sleep_until(l_next_tick);
        }
        else
        {
          // We're behind, so shift up the tick time.
          l_next_tick = l_now;

          // Could log that we're behind...
        }
      }

      // Exit code goes here.
    }
  };

} // namespace mach

#endif // MACH_GAME_LOOP_HPP