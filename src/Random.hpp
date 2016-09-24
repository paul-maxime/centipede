#pragma once

class Random
{
private:
  Random();
public:
  static void init();
  static int nextInt(int max);
};
