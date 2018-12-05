#ifndef MACH_PLATFORM_SDL_RENDER_WINDOW_HPP
#define MACH_PLATFORM_SDL_RENDER_WINDOW_HPP

#include "../../abstract_renderer.hpp"
#include "window.hpp"

#include <SDL.h>

#include <vector>
#include <string>

namespace mach
{
  namespace platform
  {
    namespace sdl
    {
      class System;
      class Window;

      //---------------------------------------------------------------------------
      // Render_Window
      //---------------------------------------------------------------------------

      class Render_Window : 
        public Abstract_Renderer
      {
      private:
        // Member Data
        //============================================================   
        Window m_window;
        SDL_Renderer* m_renderer;
        std::uintmax_t m_render_count;

      public:
        // Special 6
        //============================================================
        Render_Window
        (
          System const& a_system,
          std::string const& a_title,
          int a_xpos,
          int a_ypos,
          int a_width,
          int a_height,
          std::uint32_t a_window_flags,
          std::uint32_t a_renderer_flags
        );

        // Initialise with default window position
        Render_Window
        (
          System const& a_system,
          std::string const& a_title,
          int a_width,
          int a_height,
          std::uint32_t a_window_flags = 0,
          std::uint32_t a_renderer_flags = 0
        );

        ~Render_Window() override final;


        // Virtual Interface
        //============================================================
        // Update the renderer if the event data requires it.
        //void update(Event_Data const& a_event_data) override final;
        
        // Call immediately before starting to render a frame to tell
        // the renderer to fetch a new frame to render to.
        void begin_render() override final;

        // Clears the entire render area with the supplied colour.
        void clear(Colour_RGBA a_colour) override final;

        // Call immediately after rendering a frame to tell the 
        // renderer that this frame is finished and ready to present.
        void end_render() override final;

        // Send the last rendered frame to the screen.
        void present() override final;
      };
    } // namespace sdl
  } // namespace platform
} // namespace mach

  //------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // MACH_PLATFORM_SDL_RENDER_WINDOW_HPP
