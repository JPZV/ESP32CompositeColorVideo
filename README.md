![Venus de Milo Animation][animation]

# ESP32CompositeColorVideo

This repository is a fork of Bitluni's [ESP32CompositeVideo] that adds color in NTSC and PAL
by borrowing code from [ESP_8_BIT]. See [esp32-dali-clock] for an example of what this
modified code can do.

At first, I tried Bitluni's [ESP32SpaceShooter] that implements color in PAL. However, my
monitor had a difficult time keeping sync. After some digging, I came across rossumur's
[ESP_8_BIT] which purported to use the *Audio Phase Locked Loop* capability of the ESP32
to generate a better color signal. Not only that, but it managed to do so for both PAL
*and* NTSC.

Intrigued, I set out to see if I could adapt this code for my own use. But first I had to
free the NTSC/PAL code from the ESP_8_BIT project. The code was written very specifically for
several different emulators, but I was able to tease out the bits for the Atari which would
give me a fixed 336 by 240 pixels of resolution and a 256 color pallete.

I found the [relevant code](https://github.com/rossumur/esp_8_bit/blob/master/src/video_out.h)
and unsucessfully tried to understand how it worked (I assume magic). Nonetheless, I was able
to grasp just enough to make it run standalone without the emulators.

Having done this, I needed a way to draw to the framebuffer. Fortuitously, I found that the
framebuffer was compatible with the graphics library Bitluni had already developed.

# Examples in this library

The two examples from bitluni's original library have been modified to run in color. They
are:

- CompositeVideoSimple: renders text, a few lines and an image in color.
- CompositeVideo: renders a 3D mesh and display it in color.

You need an ESP32 module connect the pin 25 to the inner pin of the yellow AV connector
and ground to the outer ring.

# Drawing colors ([ESP32CompositeVideo] compatibility mode):

To maintain compatibility with Bitluni's original library, the drawing routines all accept
a value from 0 through 54. In the original library, these values specified one of 55
different shades of gray. This version of the library can only show 16 levels of brightness,
but in this mode the original range is preserved for compatibility.

Although it limits the number of brightness levels, this library makes up for it by allowing
the selection one of sixteen different hues, which are then combined with the brightness
values for all subsequent drawing operations. Example:

```
graphics.setHue(hue);                  // Range: 0-15 (0 means B&W)
graphics.fillRect(x,y,w,h,brightness); // Range: 0-54
```

Hence, 256 total colors are available: 16 different shades of 16 different hues.

# Drawing colors (Atari mode):

Alternatively, you can choose to use Atari colors values by declaring `USE_ATARI_COLORS`
before you include "CompositeGraphics.h"

When this mode is enabled, the color argument to the various functions will take a color
from the [Atari color palette]. This palette is quite convenient because when expressed
in hexdecimal, the first nibble indicates one of 16 different hues while the second nibble
indicates one of 16 possible values of brightness.

In this mode, all the 256 colors can be expressed directly and `graphics.setHue()` is not
available. This mode will also be more performant. Example:


```
#define USE_ATARI_COLORS
#include "CompositeGraphics.h"

...

graphics.fillRect(x,y,w,h,color); // Range: 0x00 - 0xFF
```

# License (marciot)

```
Copyright (c) 2021, Marcio Teixeira

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
```

# License (esp32-8-bit)

```
Copyright (c) 2020, Peter Barrett

Permission to use, copy, modify, and/or distribute this software for
any purpose with or without fee is hereby granted, provided that the
above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.
```

# License (bitluni)

```
CC0. Do whatever you like with the code but I will be thankfull 
if you attribute me. Keep the spirit alive :-)

- bitluni
```

[ESP32CompositeVideo]: https://github.com/marciot/ESP32CompositeVideo
[ESP32SpaceShooter]: https://github.com/bitluni/ESP32SpaceShooter
[ESP_8_BIT]: https://github.com/rossumur/esp_8_bit
[Atari color palette]: http://7800.8bitdev.org/index.php/Atari_7800_Color_Documentation
[esp32-dali-clock]: https://github.com/marciot/esp32-dali-clock
[animation]: https://github.com/marciot/ESP32CompositeColorVideo/raw/master/artwork/VenusDeMilo.gif "Venus de Milo Animation"