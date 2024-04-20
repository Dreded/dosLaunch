/*
 * Copyright (C) 2016, Michiel Sikma <michiel@sikma.org>
 * MIT License
 */
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>
#include <allegttf.h>

// General RGB map speeds up almost all 256 color stuff
RGB_MAP rgb_table;

/**
 * Allegro example script. Switches to graphics mode to print "hello world",
 * then waits for a keypress and exits the program.
 * Taken from <https://wiki.allegro.cc/index.php?title=Example_ExHello>.
 */
int main(int argc, const char **argv)
{
  FONT *thefont_20point;
  PALETTE pal;
	RGB black;

	black.r = 0;
	black.g = 0;
	black.b = 0;
  // Initializes the Allegro library.
  if (allegro_init() != 0) {
    return 1;
  }

  // Installs the Allegro keyboard interrupt handler.
  install_keyboard();

  // Switch to graphics mode, 320x200.
  set_color_depth(8);
  if (set_gfx_mode(GFX_AUTODETECT, 1152, 864, 0, 0) != 0) {
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    allegro_message("Cannot set graphics mode:\r\n%s\r\n", allegro_error);
    return 1;
  }

  // Print a single line of "hello world" on a white screen.
  // set_palette(desktop_palette);
  // Load the large font data in
	thefont_20point = load_ttf_font("dejavu.ttf", 20, 0);
	if (thefont_20point == NULL) {
	  set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
		printf("Could not load ttf slicker.ttf [20 point]\n");
		return 1;
	}
	// Create the color maps and RGB table for the antialiased fonts
	generate_332_palette(pal);
	set_palette(pal);

	// Make sure that we have black as colour zero
	set_color(0, &black);
  // Make the super speed RGB table for fast 8 bit mode color searches
	create_rgb_table(&rgb_table, pal, NULL);
	rgb_map = &rgb_table;

  int items = 20;
  int space = 30;
  int start = (864-(items*space))/2;
  int end = 864-start;
  int y =start;
  int pos = 0;

  int done = 0;
  while (!done) {
  clear_to_color(screen, makecol(0, 0, 0));
    if (pos<0) { pos=0;}
    for (int i=0;i<items;i++) {
      char buf[128];
      snprintf(buf, sizeof(buf), "Item %2d",i+pos);
      y+=space;
      textout(screen, thefont_20point, buf, 10, y, makecol(255, 0, 0));
      if (y >= end) { y=start; }
    }
    while(keypressed()){
      int val = readkey();
      switch (val>>8) {
        case KEY_UP: pos-=1; break;
        case KEY_DOWN: pos+=1; break;
        case KEY_Q: done=1; break;
      }
    }
    //alert("Bob","Was'o","Here","&Continue",NULL,'c',0);
    //file_select_ex("Hello","c:","NULL;+d",20,600,600);
  }

  return 0;
}

END_OF_MAIN()
