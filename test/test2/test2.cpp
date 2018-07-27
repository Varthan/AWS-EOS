#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class test2 : public contract
{
public:

	using contract :: contract;
	void fun(uint64_t in)
	{
		require_auth(_self);

		print("auth success ");

		eosio_assert(in == 1, "in is invalid");

		print(" ",in);
	}
};

EOSIO_ABI(test2, (fun));

