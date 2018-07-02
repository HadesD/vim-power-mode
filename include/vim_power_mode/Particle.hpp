#ifndef VIM_POWER_MODE_PARTICLE_HPP
#define VIM_POWER_MODE_PARTICLE_HPP

class Particle
{
  private:
    unsigned int m_r;
    unsigned int m_g;
    unsigned int m_b;

  public:
    Particle();

  public:
    void setPosition(int x, int y);
    unsigned long getHexColor() const;
};

#endif

