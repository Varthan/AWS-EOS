#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class a2 : public contract
{
public :
	using contract :: contract;

	/// @abi table abc i64
	struct abc
	{
		uint64_t id;
		account_name ac_name;
		std::string msg;
		uint64_t count;
		// uint64_t amt;

		uint64_t primary_key() const { return ac_name; }

		EOSLIB_SERIALIZE(abc, (id)(ac_name)(msg)(count) /*(amt)*/ )
	};

	typedef multi_index<N(abc),abc> ababa;

	uint64_t count = 1;

	void create(account_name uname)
	{
		ababa abab(_self,_self);

		auto i = abab.find(uname);

		if(i == abab.end())
		{
			abab.emplace(_self, [&](auto& ab)
			{
				ab.id = count;
				ab.ac_name = uname;
				ab.msg = "Hello";
				ab.count = 1;
				// ab.amt = 1000;
				count++;
			});
		}
		else
			print("user have already exist \n");

		print(name{uname},"'s Id is ",count);
	}

};
EOSIO_ABI(a2, (create));
