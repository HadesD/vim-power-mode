#ifndef VIM_POWER_MODE_PARTICLE_HPP
#define VIM_POWER_MODE_PARTICLE_HPP

class Particle
{
  private:
    unsigned int m_r : 8;
    unsigned int m_g : 8;
    unsigned int m_b : 8;

  public:
    Particle();

  public:
    void setPosition(const unsigned int x, const unsigned int y);
    unsigned long getHexColor() const;
};

#endif

