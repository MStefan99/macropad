#ifndef OPTIONS_HPP
#define OPTIONS_HPP


// How many plugins to allocate space for. Increase as you add more plugins
constexpr uint8_t MAX_PLUGINS {16};

// Times are in milliseconds
constexpr uint32_t keyDebounceTime {5};
constexpr uint32_t encoderDebounceTime {2};
constexpr uint32_t longPressDuration {750};
constexpr uint32_t transitionDuration {500};

/* Encoder mode being reset when you return back to the combo plugin can be annoying.
 * Use this option to keep the previously used mode
 */
#define COMBO_PLUGIN_KEEP_ENCODER_MODE true


#endif
