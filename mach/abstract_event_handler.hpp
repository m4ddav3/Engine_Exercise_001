#ifndef MACH_ABSTRACT_EVENT_HANDLER_HPP
#define MACH_ABSTRACT_EVENT_HANDLER_HPP

namespace mach
{
  class Event_Data;

  //---------------------------------------------------------------------------
  // Abstract_Event_Handler
  //---------------------------------------------------------------------------
  // Defines the platform independent interface for the event handler.

  class Abstract_Event_Handler
  {
  public:
    // Special 6
    //============================================================
    virtual ~Abstract_Event_Handler() = 0;

    // Interface
    //============================================================
    // Using the supplied data as a starting point, gather all 
    // unprocessed events and overwrite the supplied data with the
    // result. 
    virtual void handle_events(Event_Data& a_data) = 0;
  };
} // namespace mach

//------------------------------------------------------------------------------------------------------------------------------------------------------

inline
mach::Abstract_Event_Handler::~Abstract_Event_Handler() = default;

#endif // MACH_ABSTRACT_EVENT_HANDLER_HPP
