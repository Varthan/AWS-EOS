#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class vect : public contract
{
public:
	using contract::contract;

	vector<string> key;

	void inp()
	{

		std::vector<int> myints;
		print( " 0. size: " , myints.size());

 		for (int i=0; i<10; i++) myints.push_back(i);
 		print( " 1. size: ", myints.size() );

 		myints.insert (myints.end(),10,100);
 		print( " 2. size: ", myints.size() );

 		myints.pop_back();
 		print( " 3. size: ", myints.size() );



//		key.push_back(in);
//		print("LENGTH ",key.size());
//		print(" KEY_VALUE ",key[key.size() - 1]);
//		 vector<uint64_t> key;

/*		for(uint64_t i = 0; i<10; i++)
		{
			key.push_back(100+i);
			print(" ",i," ");
		}

		print("Hello ",key[4]);
*/
	}

	void oup(uint64_t index)
	{
//		print("LENGTH ",key.length);
//		print(" OUTPUT ",key[index]);
	}

};

EOSIO_ABI(vect, (inp)(oup))
