#include "event_data.hpp"

//---------------------------------------------------------------------------
// Event_Data
//---------------------------------------------------------------------------
// When the application processes events all data is cached into this object.
// This allows for a layer of event interpretation that can be changed, 
// while subsections of that can be split off as seperate things
// e.g. This could contain mouse data, gamepad data, window resizing data, 
// which are all seperate and may not be present on all platforms.

// Special 6
//============================================================
mach::Event_Data::Event_Data() = default;

// Interface
//============================================================
mach::System_Event_Data& mach::Event_Data::system_event_data() noexcept
{
  return m_system_event_data;
}

mach::System_Event_Data const& mach::Event_Data::system_event_data() const noexcept
{
  return m_system_event_data;
}

void mach::Event_Data::swap(Event_Data& a_other) noexcept
{
  mach::swap(m_system_event_data, a_other.m_system_event_data);
}

// Copy this while reseting all single frame data.
mach::Event_Data mach::Event_Data::clear_copy() const
{
  Event_Data l_copy{*this};
  l_copy.m_system_event_data = m_system_event_data.clear_copy();
  return l_copy;
}

void mach::swap(Event_Data& a_lhs, Event_Data& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}