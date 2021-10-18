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

The only difference is that the `setColor()` function, rather than taking a gray level, will
select a color from the [Atari color palette]. This palette is quite convenient because it has
256 colors, which when expressed in hexdecimal, has the first nibble indicate one of 16
different hues while the second nibble indicates one of 16 possible values of luminance.

# Examples in this library

The first two examples are the same as bitluni's originals; they run in B&W. The
CompositeColorVideo example is new.

- CompositeVideo shows how to render a 3D mesh and display it on composite in B&W.
- CompositeVideoSimple shows the simple graphics functions except for 3D currently available.
- CompositeColorVideo shows how to display color in either PAL or NTSC.

You need an ESP32 module connect the pin 25 to the inner pin of the yellow AV connector
and ground to the outer.

Please note that because the example is expecting grayscale values, and `setColor()` is now
setting colors instead, it looks pretty bad. Maybe sometime I will try to modify it to look
correct.

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