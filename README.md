## Adafruit macropad firmware

A customizable and extensible firmware for Adafruit Macropad. Set up hundreds of shortcuts, program custom logic and enjoy automatic app switching or have
your macropad respond to actions on your computer.


### Installation
1. Install Arduino IDE and RP2040 Board Support Package as described [here][setup-bsp]
2. Install `Adafruit NeoPixel` and `Adafruit SH110X` libraries with add dependencies
3. Compile and upload to your macropad!


### Adding apps
This firmware uses "plugins" to extend the functionality of your macropad. You can think of them as little apps that do certain things in response to the inputs.
There are two ready-made plugins you can use immediately to make the most of the macropad:

- `QuickPlugin` allows you to set up one shortcut for every button on a macropad and three for the knob (up, down, push).
- `ComboPlugin` can do everything the `QuickPlugin` can, but adds key combinations. Holding down any of the keys activates a layer that can have
shortcuts for any of the other keys plus its own knob action. This gives you 144 shortcuts and 12 knob actions.
By holding down a key and pressing the knob, the knob will stay in that mode.

Both plugins show shortcut names on the screen. `ComboPlugin` allows you to cycle through help pages (quick shortcuts, layers, knob actions)
by pressing the knob.


You can use the built-in plugins with as many apps as you like. All you need to do is to do is add app-specific definitions 
(found in [pluginDefinitions](./src/pluginDefinitions) folder that tell the plugin what shortcuts to send for each key. 
Start by copying the Firefox definition (a `QuickPlugin` definition) or Krita definition (a `ComboPlugin` definition).
After that, make sure to register your plugin so that the macropad can find it. This is done by adding an `#include` for your .hpp
definition file in the [plugins.cpp](./src/plugins.cpp) file (technically, you can do this in any `.cpp` file but then the order cannot be guaranteed).
The C++ compiler must know in advance how many plugins to allocate space for. If you run out of space and your plugin doesn't show up,
you can increase it in [options.hpp](./src/options.hpp) along with some other options.


If you wish, you can design a black-and-white icon that will show up in the app list. The icon must be 32x32 pixels.
The [provided python script][py-comp] will convert it to the C++ array you can use in your definition.


### System menu and options
By holding down the knob, you can open the system menu. From here you can switch apps or change system settings: key brightness, knob speed and 
timeout. Press the knob to enter a sub-menu, hold down the knob to move up a layer or use keys to navigate.

You can quickly adjust the brightness by pressing and turning the knob from any screen.


### App switching
The [companion python script](./companion.py) can automatically watch the currently active app on your computer and tell the Macropad to switch
the plugins automatically. Simply make the script run on boot and keep it running at all times.
If you want an app to open a plugin with a different name (i.e. open a numpad plugin when you use Excel), you can add aliases in 
[aliases.json](./aliases.json) as follows: `"excel": "numpad"`, the `.exe` on Windows is removed automatically. You can map multiple apps to one plugin.

The script has been tested on Windows 11 and Fedora 43.


### Extending
You can add your own logic by creating custom plugins by extending the [Plugin](./src/Plugin.hpp), [QuickPlugin](./src/QuickPlugin.hpp) or 
[ComboPlugin](./src/ComboPlugin.hpp).

The [companion script][py-comp] starts a web server on port 6227. By sending a POST request to the server, you can send custom data to the macropad
to trigger actions. The data will be made available in the `onData()` plugin hook. Keep in mind that you need to add the `Profile` header matching
the name of the currently active plugin, otherwise the data will be discarded. For security, the server only accepts requests originating from
your computer itself.

clang-format code style is provided to keep code clean and readable. Run clang-format using this command: `clang-format *.ino **/*.[ch]pp **/**/*.hpp -i`

**Do not modify any of the existing code for easy updates!**


[setup-bsp]: https://learn.adafruit.com/adafruit-macropad-rp2040/arduino-ide-setup
[py-comp]: ./companion.py
