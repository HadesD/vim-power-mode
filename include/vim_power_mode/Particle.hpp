#ifndef __VIM_POWER_MODE_PARTICLE_HPP__
#define __VIM_POWER_MODE_PARTICLE_HPP__

class Particle
{
  private:
    int m_r;
    int m_g;
    int m_b;

  public:
    Particle();

  private:
    void setPosition(int x, int y);
};

#endif

