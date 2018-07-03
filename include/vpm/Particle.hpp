#ifndef VIM_POWER_MODE_PARTICLE_HPP
#define VIM_POWER_MODE_PARTICLE_HPP

namespace VPM
{
  class Window;

  class Particle
  {
    private:
      unsigned int m_r : 8;
      unsigned int m_g : 8;
      unsigned int m_b : 8;

      Window* m_window;

    public:
      Particle();
      ~Particle();

    public:
      void setPosition(unsigned int x, unsigned int y);
      unsigned long getHexColor() const;
  };
}

#endif

