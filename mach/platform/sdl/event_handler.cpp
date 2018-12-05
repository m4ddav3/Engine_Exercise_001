#include "event_handler.hpp"

#include "../../event_data.hpp"

#include <SDL_events.h>

#include <cassert>

//---------------------------------------------------------------------------
// Event_Handler
//---------------------------------------------------------------------------

// Special 6
//============================================================
mach::platform::sdl::Event_Handler::Event_Handler(System const& a_system) :
  Abstract_Event_Handler{},
  m_event_subsystem{ a_system }
{}

mach::platform::sdl::Event_Handler::~Event_Handler() = default;

// Interface
//============================================================
// Using the supplied data as a starting point, gather all 
// unprocessed events and overwrite the supplied data with the
// result. 
void mach::platform::sdl::Event_Handler::handle_events(Event_Data& a_data)
{
  // Copy the supplied data, we will build into it
  // then swap it at the end. Any flags that persist for
  // only one frame are reset.
  Event_Data l_event_data = a_data.clear_copy();

  // We will read SDL events into this object.
  SDL_Event l_event{};

  // While there are events poll them.
  while (SDL_PollEvent(&l_event) == 1)
  {
    // Messy if we want rebinding.....
    // Also lots of duplicate code so adding more is a pain.

    switch (l_event.type)
    {
    case SDL_QUIT:
      l_event_data.system_event_data().set_quitting(true);
      break;
    case SDL_DROPTEXT:
    case SDL_DROPFILE: // intentional fall-through
      SDL_free(l_event.drop.file);
      break;
    }
  }

  // Swap our built object with the reference supplied.
  swap(l_event_data, a_data);
}