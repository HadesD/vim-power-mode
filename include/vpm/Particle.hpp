#ifndef VIM_POWER_MODE_PARTICLE_HPP
#define VIM_POWER_MODE_PARTICLE_HPP

namespace VPM
{
  class Window;

  class Particle
  {
    private:
      Window* m_window;

    public:
      Particle();
      ~Particle();
  };
}

#endif

