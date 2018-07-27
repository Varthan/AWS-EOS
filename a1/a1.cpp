#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class a1 : public contract
{
public:
	using contract :: contract;

	void hello(account_name _name)
	{
		print("Hello ", name{_name});
	}
};

EOSIO_ABI(a1, (hello));
