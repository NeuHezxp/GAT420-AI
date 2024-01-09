#include "GameOFLife.h"
#include "Random.h"
#include "Texture.h"

bool GameOfLife::Initialize()
{
	frame = 0;

	bufferA.resize(size.x * size.y);
	bufferB.resize(size.x * size.y);

	buffer.resize(size.x * size.y);
	return true;
}

void GameOfLife::Step()
{
	// "draw" onto buffer
	frame++;
	Write<uint8_t>(buffer, size.x / 2, 0, 1);

	std::vector<uint8_t>& readBuffer = (frame % 2 == 1) ? bufferA : bufferB;
	std::vector<uint8_t>& writeBuffer = (frame % 2 == 1) ? bufferB : bufferA;

	// rule 30 = 00011110 (binary)
	static uint8_t rule = 108;
	rule = 22;


	// update buffer
// clear write buffer
	std::fill(writeBuffer.begin(), writeBuffer.end(), 0);

	for (int y = 0; y < size.y; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			int weight = 0; //amount of surviving neighbors

			// read surrounding 8 cells, accumulate weight
			// XXX
			// X0X
			// XXX
			weight += Read<uint8_t>(readBuffer, x - 1, y - 1);
			weight += Read<uint8_t>(readBuffer, x, y - 1);
			weight += Read<uint8_t>(readBuffer, x + 1, y - 1);
			weight += Read<uint8_t>(readBuffer, x - 1, y);
			weight += Read<uint8_t>(readBuffer, x + 1, y);
			weight += Read<uint8_t>(readBuffer, x - 1, y + 1);
			weight += Read<uint8_t>(readBuffer, x, y + 1);
			weight += Read<uint8_t>(readBuffer, x + 1, y + 1);

			// game of life rules
		   // if cell is alive, update
			if (Read<uint8_t>(readBuffer, x, y))
			{
				if (weight < 2) Write<uint8_t>(writeBuffer, x, y, 0);
				else if (weight == 2 || weight == 3) Write<uint8_t>(writeBuffer, x, y, 1);
				else if (weight > 3) Write<uint8_t>(writeBuffer, x, y, 0);
			}
			else
			{
				// if cell is dead, update
				if (weight == 3) Write<uint8_t>(writeBuffer, x, y, 1);
			}
		}
	}
	// convert buffer data format to color buffer
	//front to end do that element and write to the color buffer. If the v is a value then give it 255 or white color as alive
	//take all the elements then write to the destination.

	// convert buffer data format to color buffer
	std::transform((writeBuffer).begin(), (writeBuffer).end(), color_buffer.begin(), [](uint8_t v)
		{
			{ return  v ? 0xffffffff : 0; }
		});

	// copy color buffer to texture
	texture->Copy(color_buffer);
}
void GameOfLife::KeyDown(SDL_Keycode keycode)
{
	if (keycode == SDLK_r)
	{
		// write random 'alive' cells to buffer
		std::vector<uint8_t>& writeBuffer = (frame % 2) ? bufferB : bufferA;
		for (int i = 0; i < writeBuffer.size(); i++) writeBuffer[i] = (random(0, 10) == 0) ? 1 : 0;
	}
}


