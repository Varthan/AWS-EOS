#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class test1 : public contract
{
public :
        using contract :: contract;

        /// @abi table ab1 i64
        struct ab1
        {
                account_name ac_name;
                uint64_t count;
                std::vector<string> msg;

                uint64_t primary_key() const { return ac_name; }

                EOSLIB_SERIALIZE(ab1, (ac_name)(count)(msg))
        };

        typedef multi_index<N(ab1),ab1> ab;

        void reg(account_name user, string mssg)
        {
                ab aba(_self, _self);

                auto i = aba.find(user);

                if(i == aba.end())
                {
                        aba.emplace(_self, [&](auto& reg)
                        {
                                reg.ac_name = user;
                                reg.count = 1;
                                reg.msg.push_back(mssg);
                                print("Successfully Registered");
                        });
                }
                else
                {
                        aba.modify(i,_self,[&](auto& mod)
                        {
                                mod.count += 1;
                                mod.msg.push_back(mssg);
                        });

                        print("Successfully Modified ");
                }
        }

        void data(account_name user) 
        {
                ab aba(_self,_self);
                auto i = aba.find(user);

                if(i != aba.end())
                {
                        auto user_dl = aba.get(user);

                        print("USER_NAME: ",name{user_dl.ac_name},"  ENTRY_COUNT: ",user_dl.count, " MESSAGES: ");

                        for(int j = 0;j < user_dl.msg.size(); j++)
                                print(user_dl.msg[j], " ,"); 
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }

	void delmsg(account_name user,uint64_t indx)
        {
                ab aba(_self, _self);

                auto i = aba.find(user);

                if(i != aba.end())
                {
                        aba.modify(i,_self,[&](auto& mod)
                        {
                                mod.msg.erase (mod.msg.begin() + indx);
                        });
                        print("Successfully Removed");
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }

        void del(account_name user)
        {
                ab aba(_self, _self);

                auto i = aba.find(user);

                if(i != aba.end())
                {
                        aba.erase(i);
                        print("Successfully Removed");
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }
};

EOSIO_ABI(test1, (reg)(data)(del)(delmsg));

