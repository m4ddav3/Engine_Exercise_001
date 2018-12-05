#include "window.hpp"

#include "system.hpp"
#include <SDL.h>
//#include <SDL_vulkan.h>

#include <cassert>
#include <iostream>

namespace mach
{
  namespace platform
  {
    namespace sdl
    {
      namespace
      {
        //---------------------------------------------------------------------------
        // Window_Destroyer
        //---------------------------------------------------------------------------
        // Does the actual work. Stores a reference to the video subsystem. 

        class Window_Destroyer
        {
        public:
          // Member Data
          //============================================================
          Video_Subsystem m_subsystem;

          // Special 6
          //============================================================
          explicit Window_Destroyer(Video_Subsystem && a_subsystem) :
            m_subsystem{ std::move(a_subsystem) }
          {
          }

          // Interface
          //============================================================
          void operator()(SDL_Window* a_window) const noexcept
          {
            SDL_DestroyWindow(a_window);
          }
        };


        // Factory function for the actual window.
        decltype(auto) make_except_window(System const& a_system, std::string const& a_title, int a_xpos, int a_ypos, int a_width, int a_height, uint32_t a_flags)
        {
          // Got to initialis this first.
          Video_Subsystem l_subsystem{ a_system };

          // make sure we have this flag
          //auto l_flags = a_flags | SDL_WINDOW_VULKAN;
          SDL_Window* l_result = SDL_CreateWindow(a_title.c_str(), a_xpos, a_ypos, a_width, a_height, a_flags);
          if (l_result == nullptr)
          {
            throw std::runtime_error{ "SDL: Failed to create window." };
          }

          std::unique_ptr<SDL_Window, Window_Destroyer> l_capture{ l_result, Window_Destroyer{ std::move(l_subsystem) } };

          return std::shared_ptr<SDL_Window>{std::move(l_capture)};
        }
      } // namespace 
    } // namespace sdl
  } // namespace platform
} // namespace mach

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Window
//---------------------------------------------------------------------------
// Manages the SDL window with reference counting.

// Special 6
//============================================================
mach::platform::sdl::Window::Window
(
  System const& a_system,
  std::string const& a_title,
  int a_xpos,
  int a_ypos,
  int a_width,
  int a_height,
  std::uint32_t a_flags
) :
  m_data{ make_except_window(a_system, a_title, a_xpos, a_ypos, a_width, a_height, a_flags) }
{
}

// Initialise with default window position
mach::platform::sdl::Window::Window
(
  System const& a_system,
  std::string const& a_title,
  int a_width,
  int a_height,
  std::uint32_t a_flags
) :
  Window(a_system, a_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, a_width, a_height, a_flags)
{
}

// Interface
//============================================================

std::uint32_t mach::platform::sdl::Window::id() const
{
  return SDL_GetWindowID(get());
}

int mach::platform::sdl::Window::width() const
{
  int l_width{ 0 };
  SDL_GetWindowSize(get(), &l_width, nullptr);
  return l_width;
}

int mach::platform::sdl::Window::height() const
{
  int l_height{ 0 };
  SDL_GetWindowSize(get(), nullptr, &l_height);
  return l_height;
}
/*
int mach::platform::sdl::Window::draw_width() const
{
int l_width{ 0 };
SDL_Vulkan_GetDrawableSize(get(), &l_width, nullptr);
return l_width;
}

int mach::platform::sdl::Window::draw_height() const
{
int l_height{ 0 };
SDL_Vulkan_GetDrawableSize(get(), nullptr, &l_height);
return l_height;
}
*/