#pragma once
class SnakeBodyPart
{
	const SnakeBodyPart * nextPart;
	const bool isHead;
public:
	SnakeBodyPart(const SnakeBodyPart * nextBodyPart, bool isHead)
		: nextPart(nextBodyPart), isHead(isHead)  {};
	~SnakeBodyPart(void);

	const SnakeBodyPart * getNextBodyPart() const;
	const bool isSnakeHead() const;
};

