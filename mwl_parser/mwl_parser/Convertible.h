#pragma once

#include <vector>
#include <memory>

namespace MWLParser
{
	class Convertible
	{
	public:
		virtual ~Convertible() {};

		virtual std::shared_ptr<Convertible> fromBytes(const std::vector<uint8_t>& bytes) = 0;
		virtual std::vector<uint8_t> toBytes() const = 0;
	};
}
