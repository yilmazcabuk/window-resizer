#include <windows.h>

#include <iostream>

namespace
{
	bool is_key_pause_pressed()
	{
		return (GetAsyncKeyState(VK_PAUSE) & 0x8000) != 0;
	}

	void resize_active_window_relative()
	{
		HWND hwnd = GetForegroundWindow(); // Get handle to the active window
		if (hwnd)
		{
			RECT screen_rect;
			GetClientRect(GetDesktopWindow(), &screen_rect); // Get screen dimensions
			const int screen_width = screen_rect.right;
			const int screen_height = screen_rect.bottom;

			// Define the desired window size as a fraction of the screen size
			constexpr double width_ratio = 1600.0f / 1920.0f; // Ratio relative to 1920x1080
			constexpr double height_ratio = 900.0f / 1080.0f; // Ratio relative to 1920x1080

			// Calculate the new window dimensions based on the screen size
			const int new_width = static_cast<int>(screen_width * width_ratio);
			const int new_height = static_cast<int>(screen_height * height_ratio);

			// Calculate the relative position to center the window
			const int x = (screen_width - new_width) / 2;
			const int y = (screen_height - new_height) / 2;

			// Resize and reposition the window relative to the screen size
			MoveWindow(hwnd, x, y, new_width, new_height, TRUE);
		}
	}
}


int main()
{
	std::cout << "Press the Pause key to resize the active window relative to "
		"your screen size.\n";
	std::cout << "Press Ctrl + C to exit the program.\n";

	bool key_previously_pressed = false;

	while (true)
	{
		if (is_key_pause_pressed())
		{
			if (!key_previously_pressed)
			{
				resize_active_window_relative();
				std::cout << "Active window resized relative to screen size.\n";
				key_previously_pressed = true;
			}
		}
		else
		{
			key_previously_pressed = false; // Reset when key is released
		}
	}
}
