#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class ret : public contract
{
public :
        using contract :: contract;

        uint64_t fun()
        {
                print("HELLO");
		return 5;
        }

};
EOSIO_ABI(ret, (fun));

