#ifndef MACH_ABSTRACT_RENDERER_HPP
#define MACH_ABSTRACT_RENDERER_HPP

namespace mach
{
  class Colour_RGBA;
  class Screen_Rectangle_Sprite;
  class Event_Data;

  //---------------------------------------------------------------------------
  // Abstract_Renderer
  //---------------------------------------------------------------------------
  // Defines the rendering interface.

  class Abstract_Renderer
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Renderer() = 0;

    // Virtual Interface
    //============================================================
    // Update the renderer if the event data requires it.
    //virtual void update(Event_Data const& a_event_data) = 0;

    // Call immediately before starting to render a frame to tell
    // the renderer to fetch a new frame to render to.
    virtual void begin_render() = 0;

    // Clears the entire render area with the supplied colour.
    virtual void clear(Colour_RGBA a_colour) = 0;

    // Call immediately after rendering a frame to tell the 
    // renderer that this frame is finished and ready to present.
    virtual void end_render() = 0;

    // Send the last rendered frame to the screen.
    virtual void present() = 0;
  };
  
} // namespace mach

//------------------------------------------------------------------------------------------------------------------------------------------------------

inline
mach::Abstract_Renderer::~Abstract_Renderer() = default;


#endif // MACH_ABSTRACT_RENDERER_HPP