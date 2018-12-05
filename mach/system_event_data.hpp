#ifndef MACH_SYSTEM_EVENT_DATA_HPP
#define MACH_SYSTEM_EVENT_DATA_HPP

#include <cstdint>

namespace mach
{
  //---------------------------------------------------------------------------
  // System_Event_Data
  //---------------------------------------------------------------------------
  // Stores data the game needs that can change on the fly, but is not classed
  // as input data. This is things like a quit flag from an event and the 
  // window resolution. Settings should probably not be in here.

  class System_Event_Data
  {
  private:
    // Member Data
    //============================================================   
    bool m_quitting;

  public:
    // Special 6
    //============================================================
    System_Event_Data() noexcept;

    // Interface
    //============================================================
    bool is_quitting() const noexcept;
    bool not_quitting() const noexcept;
    void set_quitting(bool a_value) noexcept;
    void clear_quitting() noexcept;
        
    void swap(System_Event_Data& a_other) noexcept;

    System_Event_Data clear_copy() const;
  };

  void swap(System_Event_Data& a_lhs, System_Event_Data& a_rhs) noexcept;

} //namespace mach

#endif // MACH_SYSTEM_EVENT_DATA_HPP