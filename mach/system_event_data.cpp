#include "system_event_data.hpp"

#include <utility>

//---------------------------------------------------------------------------
// System_Data
//---------------------------------------------------------------------------
// Stores data the game needs that can change on the fly, but is not classed
// as input data. This is things like a quit flag from an event and the 
// window resolution. Settings should probably not be in here.

// Special 6
//============================================================
mach::System_Event_Data::System_Event_Data() noexcept :
  m_quitting{ false }
{}


// Interface
//============================================================
bool mach::System_Event_Data::is_quitting() const noexcept
{
  return m_quitting;
}

bool mach::System_Event_Data::not_quitting() const noexcept
{
  return !m_quitting;
}

void mach::System_Event_Data::set_quitting(bool a_value) noexcept
{
  m_quitting = a_value;
}

void mach::System_Event_Data::clear_quitting() noexcept
{
  m_quitting = false;
}

void mach::System_Event_Data::swap(System_Event_Data& a_other) noexcept
{
  std::swap(m_quitting, a_other.m_quitting);
}

mach::System_Event_Data mach::System_Event_Data::clear_copy() const
{
  System_Event_Data l_copy{ *this };

  l_copy.clear_quitting();

  return l_copy;
}

void mach::swap(System_Event_Data& a_lhs, System_Event_Data& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}