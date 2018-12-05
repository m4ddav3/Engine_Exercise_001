#ifndef MACH_COLOUR_HPP
#define MACH_COLOUR_HPP

#include <cstdint>
#include <utility>

namespace mach
{
  template <typename T_Int, T_Int t_min, T_Int t_max>
  constexpr T_Int clamp(T_Int a_value) noexcept
  {
    return (a_value > t_max ? t_max : (a_value < t_min ? t_min : a_value));
  }

  //---------------------------------------------------------------------------
  // Colour_RGB
  //---------------------------------------------------------------------------
  // 24 bit colour.
  class Colour_RGB
  {
  private:
    // Member Data
    //============================================================   
    std::uint8_t m_r;
    std::uint8_t m_g;
    std::uint8_t m_b;

  public:
    // Special 6
    //============================================================
    // Value is 0,0,0
    constexpr Colour_RGB() noexcept;
    // Values are clamped to (0..255)
    constexpr Colour_RGB(int a_red, int a_green, int a_blue) noexcept;

    // Interface
    //============================================================
    constexpr int r() const noexcept;
    constexpr int g() const noexcept;
    constexpr int b() const noexcept;

    void swap(Colour_RGB& a_other) noexcept;
  };

  void swap(Colour_RGB& a_lhs, Colour_RGB& a_rhs) noexcept;

  //---------------------------------------------------------------------------
  // Colour_RGBA
  //---------------------------------------------------------------------------
  // 32 bit colour.
  class Colour_RGBA
  {
  private:
    // Member Data
    //============================================================   
    std::uint8_t m_r;
    std::uint8_t m_g;
    std::uint8_t m_b;
    std::uint8_t m_a;

  public:
    // Special 6
    //============================================================
    // Value is 0,0,0,0
    constexpr Colour_RGBA() noexcept;
    // Values are clamped to (0..255), alpha is set to 255
    constexpr Colour_RGBA(int a_red, int a_green, int a_blue) noexcept;
    // Values are clamped to (0..255)
    constexpr Colour_RGBA(int a_red, int a_green, int a_blue, int a_alpha) noexcept;

    // Interface
    //============================================================
    constexpr int r() const noexcept;
    constexpr int g() const noexcept;
    constexpr int b() const noexcept;
    constexpr int a() const noexcept;

    void swap(Colour_RGBA& a_other) noexcept;
  };
  void swap(Colour_RGBA& a_lhs, Colour_RGBA& a_rhs) noexcept;
}

//---------------------------------------------------------------------------
// Colour_RGB
//---------------------------------------------------------------------------
// 24 bit colour.

// Special 6
//============================================================
// Value is 0,0,0
inline 
constexpr mach::Colour_RGB::Colour_RGB() noexcept :
  m_r{ 0 },
  m_g{ 0 },
  m_b{ 0 }
{
}
// Values are clamped to (0..255)
inline 
constexpr mach::Colour_RGB::Colour_RGB(int a_red, int a_green, int a_blue) noexcept :
  m_r{ static_cast<std::uint8_t>(clamp<int,0,255>(a_red)) },
  m_g{ static_cast<std::uint8_t>(clamp<int,0,255>(a_green)) },
  m_b{ static_cast<std::uint8_t>(clamp<int,0,255>(a_blue)) }
{
}

// Interface
//============================================================
inline
constexpr int mach::Colour_RGB::r() const noexcept
{
  return m_r;
}

inline
constexpr int mach::Colour_RGB::g() const noexcept
{
  return m_g;
}

inline
constexpr int mach::Colour_RGB::b() const noexcept
{
  return m_b;
}

inline
void mach::Colour_RGB::swap(Colour_RGB& a_other) noexcept
{
  std::swap(m_r, a_other.m_r);
  std::swap(m_b, a_other.m_b);
  std::swap(m_g, a_other.m_g);
}

inline
void mach::swap(Colour_RGB& a_lhs, Colour_RGB& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}

//---------------------------------------------------------------------------
// Colour_RGBA
//---------------------------------------------------------------------------
// 32 bit colour.

// Special 6
//============================================================
// Value is 0,0,0,0
inline 
constexpr mach::Colour_RGBA::Colour_RGBA() noexcept :
  m_r{ 0 },
  m_g{ 0 },
  m_b{ 0 },
  m_a{ 0 }
{
}
// Values are clamped to (0..255), alpha is set to 255
inline
constexpr mach::Colour_RGBA::Colour_RGBA(int a_red, int a_green, int a_blue) noexcept :
  m_r{ static_cast<std::uint8_t>(clamp<int,0,255>(a_red)) },
  m_g{ static_cast<std::uint8_t>(clamp<int,0,255>(a_green)) },
  m_b{ static_cast<std::uint8_t>(clamp<int,0,255>(a_blue)) },
  m_a{ 255 }
{
}
// Values are clamped to (0..255)
inline 
constexpr mach::Colour_RGBA::Colour_RGBA(int a_red, int a_green, int a_blue, int a_alpha) noexcept :
  m_r{ static_cast<std::uint8_t>(clamp<int,0,255>(a_red)) },
  m_g{ static_cast<std::uint8_t>(clamp<int,0,255>(a_green)) },
  m_b{ static_cast<std::uint8_t>(clamp<int,0,255>(a_blue)) },
  m_a{ static_cast<std::uint8_t>(clamp<int,0,255>(a_alpha)) }
{
}

// Interface
//============================================================
inline 
constexpr int mach::Colour_RGBA::r() const noexcept
{
  return m_r;
}

inline 
constexpr int mach::Colour_RGBA::g() const noexcept
{
  return m_g;
}

inline 
constexpr int mach::Colour_RGBA::b() const noexcept
{
  return m_b;
}

inline 
constexpr int mach::Colour_RGBA::a() const noexcept
{
  return m_a;
}

inline 
void mach::Colour_RGBA::swap(Colour_RGBA& a_other) noexcept
{
  std::swap(m_r, a_other.m_r);
  std::swap(m_b, a_other.m_b);
  std::swap(m_g, a_other.m_g);
  std::swap(m_a, a_other.m_a);
}

inline 
void mach::swap(Colour_RGBA& a_lhs, Colour_RGBA& a_rhs) noexcept
{
  a_lhs.swap(a_rhs);
}


#endif // MACH_COLOUR_HPP