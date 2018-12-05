#ifndef MACH_PLATFORM_SDL_WINDOW_HPP
#define MACH_PLATFORM_SDL_WINDOW_HPP

#include <vector>
#include <string>

struct SDL_Window;

namespace mach
{
  namespace platform
  {
    namespace sdl
    {
      class System;

      //---------------------------------------------------------------------------
      // Window
      //---------------------------------------------------------------------------
      // RAII manages the SDL window with reference counting.

      class Window
      {
      private:
        // Member Data
        //============================================================   
        using Data_Type = std::shared_ptr<SDL_Window>;
        Data_Type m_data;

      public:
        // Special 6
        //============================================================
        Window
        (
          System const& a_system,
          std::string const& a_title,
          int a_xpos,
          int a_ypos,
          int a_width,
          int a_height,
          std::uint32_t a_flags
        );

        // Initialise with default window position
        Window
        (
          System const& a_system,
          std::string const& a_title,
          int a_width,
          int a_height,
          std::uint32_t a_flags
        );

        // Interface
        //============================================================
        SDL_Window* get() const noexcept { return m_data.get(); }
        operator SDL_Window*() const noexcept { return m_data.get(); }

        std::uint32_t id() const;

        int width() const;
        int height() const;

        //int draw_width() const;
        //int draw_height() const;
      };
    } // namespace sdl
  } // namespace platform
} // namespace mach

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MACH_PLATFORM_SDL_WINDOW_HPP
