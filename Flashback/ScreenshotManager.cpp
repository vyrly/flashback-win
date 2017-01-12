// ScreenshotManager.cpp : 
//

#include "stdafx.h"
#include "ScreenshotManager.h"

void ScreenshotManager::Shot() {
	// Take screenshot and it in set
	(*itCurrentSet)->push_front(std::make_shared<Screenshot>()); // <--- Screenshot
	// Set iterator to latest screenshot in set
	itCurrentScr = (*itCurrentSet)->begin();
	LOG(INFO) << (*itCurrentSet)->size() << " Screenshot placed in " << currentSession.size() << " Set";
}

string time_point_To_String(const time_point<system_clock> &timestamp) {
	// Convert time_point to string
	struct tm timeinfo;
	struct tm buf;

	string timestampString;

	auto in_time_t = std::chrono::system_clock::to_time_t(timestamp);
	std::stringstream ss;
	localtime_s(&timeinfo, &in_time_t);
	ss << std::put_time(&timeinfo, "%Y-%m-%d %X");
	timestampString = ss.str();

	return timestampString;
}

void ScreenshotManager::RedrawScr() {
	// TODO: Describe it properly

	// Prepare screenshot to be drawn
	screenshotImage = (*itCurrentScr)->ImageGet(); // Get Image pointer
	screenshotTexture.loadFromImage(*screenshotImage); // Load a texture from Image
	screenshotSprite.setTexture(screenshotTexture); // Assign it to a sprite

	// Prepare timestamp to be drawn
	string timestamp = time_point_To_String((*itCurrentScr)->TimestampGet());

	timestampText.setString(timestamp); // set the string to display
}

void ScreenshotManager::Main() {
	RedrawScr();

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Flashback", sf::Style::Fullscreen);

	// the event/logic/whatever loop
	while (window.isOpen()) {
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)) {
			// check the type of the event...
			switch (event.type) {
				// "close requested" event: close the window
			case sf::Event::Closed:
				window.close();
				LOG(INFO) << "SCR_MAN Close";
				break;
				// key pressed
			case sf::Event::KeyPressed:
				// "ESC": close the window
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					LOG(INFO) << "SCR_MAN Close";
				}
				// "Down": change displayed screenshot
				if (event.key.code == sf::Keyboard::Down) {
					if (itCurrentScr != --(*itCurrentSet)->end()) {
						itCurrentScr = std::next(itCurrentScr);
						RedrawScr();
					}
					LOG(INFO) << "SCR_MAN Next screenshot (Key: Down)";
				}
				// "Up": change displayed screenshot
				if (event.key.code == sf::Keyboard::Up) {
					LOG(INFO) << "SCR_MAN Previous screenshot (Key: Up)";
					if (itCurrentScr != (*itCurrentSet)->begin()) {
						itCurrentScr = std::prev(itCurrentScr);
						RedrawScr();
					}
				}
				// "Right": next set
				if (event.key.code == sf::Keyboard::Right) {
					LOG(INFO) << "TODO: SCR_MAN Next set (Key: Right)";
				}
				// "Left": previous set
				if (event.key.code == sf::Keyboard::Left) {
					LOG(INFO) << "TODO: SCR_MAN Previous set (Key: Left)";
				}
				break;
				// don't process other types of events
			default:
				break;
			}
		}
		// clear the window with black color
		window.clear(sf::Color::Black);

		// Draw everything here...
		window.draw(screenshotSprite); // Textured sprite
		window.draw(timestampText); // Timestamp string
		// TODO: Draw UI

		// end the current frame
		window.display();
		displayON = true;
	}
}
