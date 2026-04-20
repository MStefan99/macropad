#ifndef OPTIONS_HPP
#define OPTIONS_HPP


// How many plugins to allocate space for. Increase as you add more plugins
constexpr uint8_t MAX_PLUGINS {16};

// Times are in milliseconds
constexpr uint32_t keyDebounceTime {5};
constexpr uint32_t encoderDebounceTime {2};
constexpr uint32_t longPressDuration {750};
constexpr uint32_t transitionDuration {500};


#endif
