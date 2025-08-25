#include <DFRobot_NeoPixel.h>


DFRobot_NeoPixel  rgb_display_0(4);

void setup()
{
  rgb_display_0.begin();
}

void loop()
{
  rgb_display_0.setPixelColor(1-1, 0,0,0);
  rgb_display_0.show();

}


