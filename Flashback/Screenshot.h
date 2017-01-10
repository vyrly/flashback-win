#ifndef SCREENSHOT_HPP
#define SCREENSHOT_HPP

#include "stdafx.h"

using namespace std;
using chrono::time_point;
using chrono::system_clock;

//------------------------------------------------------------------------------

class Screenshot {
  // TODO: const correctness

  public:

    Screenshot()
      : timestamp(this->TimestampSet())
    {
      originalImage = std::make_shared<sf::Image>();
      Shot();
    }
    // Image
    shared_ptr<sf::Image> ImageGet();
    // Timestamp
    const time_point<system_clock> TimestampGet();
    // Label
    string LabelGet();
    void LabelSet(string text); // Only Label can be set

  private:

    vector<sf::Uint8> Pixels; //TODO: const
    void Shot();

    const time_point<system_clock>  TimestampSet(); // const?
    // Set during construction
    shared_ptr<sf::Image> originalImage;
    const time_point<system_clock> timestamp; // = std::chrono::system_clock::now()

    string label;
};

#endif // SCREENSHOT_HPP
