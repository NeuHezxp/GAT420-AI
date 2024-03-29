#include "CA.h"
#include "Texture.h"

bool CA::Initialize()
{
	buffer.resize(size.x * size.y);

	return true;
}

void CA::Step()
{
	// "draw" onto buffer
	
	Write<uint8_t>(buffer, size.x / 2, 0, 1);

	// rule 30 = 00011110 (binary)
	static uint8_t rule = 108;
	rule++;
	

	// update buffer
	for (int y = 0; y < size.y - 1; y++)
	{
		for (int x = 0; x < size.x; x++)
		{
			uint8_t i = 0;
			// read surrounding cells (x-1, x, x+2), a value between 0-7 can be created by shifting the bits
			

			i |= Read<uint8_t>(buffer, x - 1, y) << 2;
			i |= Read<uint8_t>(buffer, x, y) << 1;
			i |= Read<uint8_t>(buffer, x + 1, y) << 0;

			// elementary cellular automata rules
			uint8_t state = (rule & 1 << i) ?  1 : 0;
			Write<uint8_t>(buffer, x, y + 1, state); //writes to the buffer after reading 1 down 
		}
	}
	

	// convert buffer data format to color buffer
	//front to end do that element and write to the color buffer. If the v is a value then give it 255 or white color as alive
	//take all the elements then write to the destination.
	std::transform(buffer.begin(), buffer.end(), color_buffer.begin(), [](uint8_t v){
			uint8_t color = v ? 255 : 0;
			return v ? (color << 24 | color << 16 | color << 8 | 0xff) : 0;
		});


	// copy color buffer to texture
	texture->Copy(color_buffer);
	
}

