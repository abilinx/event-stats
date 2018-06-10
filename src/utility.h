#pragma once
#include <string>
#include <exception>

namespace eventstats
{
	unsigned int getSecondsFromEpoch();

	class InvalidQuery: public std::exception
	{
	public:
		InvalidQuery(const std::string& query);
		virtual const char* what() const noexcept override;
	private:
		std::string mMessage;
	};
}