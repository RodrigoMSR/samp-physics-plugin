#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <queue>

class Identifier
{
public:
	Identifier();

	int get();
	void remove(int id, std::size_t remaining);
	void reset();
private:
	int highestId;
	std::priority_queue<int, std::vector<int>, std::greater<int>> removedIds;
};

#endif
