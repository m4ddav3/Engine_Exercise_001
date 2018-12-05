#include "application.hpp"

#include "game_data.hpp"
#include "event_data.hpp"
#include "game_loop.hpp"

#include "platform/sdl/system.hpp"
#include "platform/sdl/window.hpp"
#include "platform/sdl/render_window.hpp"
#include "platform/sdl/event_handler.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <ostream>
#include <thread>

#include <SDL.h>

namespace
{
  std::vector<std::string> make_arg_vector(int argc, char** argv)
  {
    std::vector<std::string> l_result{};
    l_result.reserve(argc);

    for (int i = 0; i != argc; ++i)
    {
      l_result.push_back(argv[i]);
    }

    return l_result;
  }

  std::string make_what(char const* a_func, char const* a_error)
  {
    std::string l_result{ a_func };
    l_result += " failure: ";
    l_result += a_error;
    return l_result;
  }

  double linear_interpolation(double a_prev, double a_next, double a_interpolation)
  {
    // imprecise
    //return a_prev + ((a_next - a_prev) * a_interpolation);
    // precise
    return (1.0 - a_interpolation) * a_prev + a_interpolation * a_next;
  }

  std::int32_t linear_interpolation(std::int32_t a_prev, std::int32_t a_next, double a_interpolation)
  {
    return static_cast<std::int32_t>(linear_interpolation(static_cast<double>(a_prev), static_cast<double>(a_next), a_interpolation));
  }

  std::uint32_t linear_interpolation(std::uint32_t a_prev, std::uint32_t a_next, double a_interpolation)
  {
    return static_cast<std::uint32_t>(linear_interpolation(static_cast<double>(a_prev), static_cast<double>(a_next), a_interpolation));
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Application::Implementation
//---------------------------------------------------------------------------
// Hide all the implementation details and private functions for the 
// application state.

namespace mach
{
  class Application::Implementation
  {
  private:
    using System = platform::sdl::System;
    using Event_Handler = platform::sdl::Event_Handler;
    using Render_Window = platform::sdl::Render_Window;

    std::vector<std::string> m_args;
    System m_system;
    Event_Handler m_event_handler;
    Render_Window m_render_window;
    Game_Data m_game_data;

  public:
    // Special 6
    //============================================================
    Implementation(int argc, char* argv[]);
    ~Implementation();

    Implementation(Implementation const& a_other) = delete;
    Implementation& operator=(Implementation const& a_other) = delete;

    Implementation(Implementation && a_other) = delete;
    Implementation& operator=(Implementation && a_other) = delete;

    // Interface
    //============================================================
    int execute();
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Application::Implementation
//---------------------------------------------------------------------------

// Special 6
//============================================================
mach::Application::Implementation::Implementation(int argc, char* argv[]) :
  m_args{ make_arg_vector(argc, argv) },
  m_system{},
  m_event_handler{ m_system },
  m_render_window{ m_system, "Engine Exercise 001 - a blank window that changes state using only SDL.", 1280, 720 },
  m_game_data{}
{
  //SDL_ShowCursor(SDL_DISABLE);
}

mach::Application::Implementation::~Implementation() = default;

// Interface
//============================================================

int mach::Application::Implementation::execute()
{
  try
  {
    Locked_Sim_Locked_Render_Loop<60>()(m_event_handler, m_render_window, m_game_data);

    std::cout << "Exit after " << m_game_data.tick() << " ticks." << std::endl;
  }
  catch (std::runtime_error& a_exception)
  {
    std::cout << a_exception.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch (...)
  {
    std::cout << u8"Unknown failure." << std::endl;
    return EXIT_FAILURE;
  }

  // Everything worked.
  return EXIT_SUCCESS;
}

//---------------------------------------------------------------------------
// Application
//---------------------------------------------------------------------------
// Manages the application.


// Special 6
//============================================================
mach::Application::Application(int argc, char** argv) :
  m_implementation{ nullptr }
{
  try
  {
    m_implementation = std::make_unique<Implementation>(argc, argv);
  }
  catch (std::runtime_error& a_exception)
  {
    std::cout << a_exception.what() << std::endl;
  }
  catch (...)
  {
    std::cout << "Could not initialise." << std::endl;
  }
}

mach::Application::~Application() = default;

// Interface
//============================================================
int mach::Application::execute()
{
  if (m_implementation)
  {
    return imp()->execute();
  }
  else
  {
    return EXIT_FAILURE;
  }
}