#include "identifier.h"

Identifier::Identifier()
{
	highestId = 0;
}

int Identifier::get()
{
	int id = 0;
	if (!removedIds.empty())
	{
		id = removedIds.top();
		removedIds.pop();
	}
	else
	{
		id = ++highestId;
	}
	return id;
}

void Identifier::remove(int id, std::size_t remaining)
{
	if(remaining > 0)
	{
		removedIds.push(id);
	}
	else
	{
		reset();
	}
}

void Identifier::reset()
{
	highestId = 0;
	removedIds = std::priority_queue<int, std::vector<int>, std::greater<int>>();
}
