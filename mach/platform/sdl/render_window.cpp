#include "render_window.hpp"

#include "../../event_data.hpp"
#include "../../colour.hpp"

#include <cassert>
#include <iostream>

//---------------------------------------------------------------------------
// Render_Window
//---------------------------------------------------------------------------

// Special 6
//============================================================
mach::platform::sdl::Render_Window::Render_Window
(
  System const& a_system,
  std::string const& a_title,
  int a_xpos,
  int a_ypos,
  int a_width,
  int a_height,
  std::uint32_t a_window_flags,
  std::uint32_t a_renderer_flags
) :
  m_window{ a_system, a_title, a_xpos, a_ypos, a_width, a_height, SDL_WINDOW_SHOWN | a_window_flags },
  m_renderer{ SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED | a_renderer_flags) }
  //m_renderer { SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) } 
  // vsync gets rid of stutter...
  // Also appears to block presentation until the right time.
{
  assert(m_window.get());
  assert(m_renderer);
}

mach::platform::sdl::Render_Window::Render_Window
(
  System const& a_system,
  std::string const& a_title,
  int a_width,
  int a_height,
  std::uint32_t a_window_flags,
  std::uint32_t a_renderer_flags
) :
  Render_Window(a_system, a_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, a_width, a_height, a_window_flags, a_renderer_flags)
{
  assert(m_window.get());
  assert(m_renderer);
}

mach::platform::sdl::Render_Window::~Render_Window()
{
  SDL_DestroyRenderer(m_renderer);
}

// Interface
//============================================================
// Call immediately before starting to render a frame to tell
// the renderer to fetch a new frame to render to.
void mach::platform::sdl::Render_Window::begin_render()
{
  // Initalise the frame to black.
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);
}

// Clears the entire render area with the supplied colour.
void mach::platform::sdl::Render_Window::clear(Colour_RGBA a_colour)
{
  SDL_SetRenderDrawColor(m_renderer, a_colour.r(), a_colour.g(), a_colour.b(), 255);
  SDL_RenderClear(m_renderer);
}

// Call immediately after rendering a frame to tell the 
// renderer that this frame is finished and ready to present.
void mach::platform::sdl::Render_Window::end_render()
{

}

void mach::platform::sdl::Render_Window::present()
{
  SDL_RenderPresent(m_renderer);
}
