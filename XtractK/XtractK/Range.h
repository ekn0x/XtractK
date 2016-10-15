


#include "Symbol.h"

class Range
{
public:
	Range() = delete; // ne peut pas prendre le constructeur par defaut
	Range(symbol_t f, symbol_t l);

	bool isInRange(symbol_t symbol) const;
	bool isNotInRange(symbol_t const & symbol) const;

	// getter
	symbol_t getFirst() { return mFirst;  }
	symbol_t getLast() { return mLast; }

private:
	symbol_t mFirst;
	symbol_t mLast;
};