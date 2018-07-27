#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class gtime : public contract
{
public :
        using contract :: contract;

	void fun()
	{
		// time_t now = time(0);
		print(now());
		print(" ",name{_self});
	}
};

EOSIO_ABI(gtime, (fun));
