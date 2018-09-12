#ifndef ROLE_H
#define ROLE_H

#include <Arduino.h>


class Role{
  public:
    void action(int mvspeed, int state);

  private:
    int mvspeed;
    int state;

};

#endif
