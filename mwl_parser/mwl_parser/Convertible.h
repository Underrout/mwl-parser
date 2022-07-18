#pragma once

#include <vector>
#include <memory>

namespace MWLParser
{
	class Convertible
	{
	public:
		virtual ~Convertible() {};

		virtual std::vector<uint8_t> toBytes() const = 0;
	};
}

