
#include "Range.h"

#include "Symbol.h"

Range::Range(symbol_t f, symbol_t l)
	: mFirst{ f }, mLast{ l }
{
}

bool Range::isInRange(symbol_t symbol) const
{
	if (symbol >= mFirst && symbol <= mLast)
		return true;
	else
		return false;
}

bool Range::isNotInRange(symbol_t const & symbol) const
{
	return !isInRange(symbol);
}