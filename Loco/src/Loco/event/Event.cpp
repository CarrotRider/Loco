#include "stdafx.h"
#include "Event.h"

namespace Loco {

	std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}