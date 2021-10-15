//code by bitluni (send me a high five if you like the code)
#include "esp_pm.h"

#include "CompositeGraphics.h"
#include "Image.h"
#include "CompositeColorOutput.h"

#include "luni.h"
#include "font6x8.h"

//Graphics using the fixed resolution for the color graphics
CompositeGraphics graphics(CompositeColorOutput::XRES, CompositeColorOutput::YRES);
//Composite output using the desired mode (PAL/NTSC) and a fixed resolution
CompositeColorOutput composite(CompositeColorOutput::NTSC);

//image and font from the included headers created by the converter. Each iamge uses its own namespace.
Image<CompositeGraphics> luni0(luni::xres, luni::yres, luni::pixels);

//font is based on ASCII starting from char 32 (space), width end height of the monospace characters.
//All characters are staored in an image vertically. Value 0 is background.
Font<CompositeGraphics> font(6, 8, font6x8::pixels);

#include <soc/rtc.h>

void setup()
{
  //highest clockspeed needed
  esp_pm_lock_handle_t powerManagementLock;
  esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "compositeCorePerformanceLock", &powerManagementLock);
  esp_pm_lock_acquire(powerManagementLock);

  //initializing graphics double buffer
  composite.init();
  graphics.init();
  //select font
  graphics.setFont(font);
}

void draw()
{
  //clearing background and starting to draw
  graphics.begin(0);
  //drawing an image
  luni0.draw(graphics, 200, 10);

  //drawing a frame
  graphics.fillRect(27, 18, 160, 30, 0xA8);
  graphics.rect(27, 18, 160, 30, 0xAF);

  //setting text color, transparent background
  graphics.setTextColor(0xA3);
  //text starting position
  graphics.setCursor(30, 20);
  //printing some lines of text
  graphics.print("hello!");
  graphics.print(" free memory: ");
  graphics.print((int)heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
  graphics.print("\nrendered frame: ");
  static int frame = 0;
  graphics.print(frame, 10, 4); //base 10, 6 characters
  graphics.print("\n        in hex: ");
  graphics.print(frame, 16, 4);
  frame++;

  //drawing some lines
  for(int i = 0; i <= 100; i++)
  {
    graphics.line(50, i + 60, 50 + i, 160, i * 2.5);
    graphics.line(150, 160 - i, 50 + i, 60, i * 2.5);
  }

  //draw single pixel
  graphics.dot(20, 190, 10);

  //finished drawing, swap back and front buffer to display it
  graphics.end();
}

void loop()
{
  draw();
  composite.sendFrameHalfResolution(&graphics.frame);
}
