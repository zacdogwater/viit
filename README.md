# viit (View Image In Terminal)
Most ridiculous way to view an image

### Usage

`viit <image>`

### Issues

- Completely breaks on anything but true color terminal
- If terminal aspect ratio doesn't match image, it will warp the image
- Absolutely no error checking
- Crusty ansi escape codes for color
- Linux only (i don't mind)

### Future plans
- [ ] Add support for 256, 16 and 8 color mode
- [ ] Fix aspect ratio issue
- [ ] Use ncurses for a tui, no ansi escapes, and settings
- [ ] Make this readme better

