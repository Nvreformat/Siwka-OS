#ifndef SNAKE_H
#define SNAKE_H

#define MAX_BLOCKS 1024

struct Position
{
	uint32 X;
	uint32 Y;
};

class SnakeObject
{
	public:
	
	Position Blocks[MAX_BLOCKS];
	uint32 BlockCount;
	
	SnakeObject();
};

#endif