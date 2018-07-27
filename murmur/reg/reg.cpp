#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class reg : public contract
{
public:
        using contract::contract;

        ///@abi table regi1 i64
        struct regi1
        {
                account_name ac_name;
                std::string passwd;
                std::string mnemonic;

                uint64_t primary_key() const { return ac_name; }

                EOSLIB_SERIALIZE(regi1, (ac_name)(passwd)(mnemonic))
        };

        typedef multi_index<N(regi1),regi1> regi;

	///@abi table accounts1 i64
        struct accounts1
        {
		account_name ac_name;
		uint64_t acc_id;
                uint64_t login;

                uint64_t primary_key() const { return ac_name; }

                EOSLIB_SERIALIZE(accounts1, (ac_name)(acc_id)(login))
        };

        typedef multi_index<N(accounts1),accounts1> acc;

	///@abi table details1 i64
        struct details1
        {
                uint64_t user_count;
		std::vector<account_name> users;
		uint64_t msg_count;

		uint64_t primary_key() const { return 0; }

                EOSLIB_SERIALIZE(details1, (user_count)(users)(msg_count))
        };

        typedef multi_index<N(details1),details1> dtl;

	uint64_t dtl_index = 0;


	void setup(uint64_t in)
	{
		dtl dls(_self, _self);
		auto i = dls.find(dtl_index);

		if(i == dls.end())
                {
                        dls.emplace(_self, [&](auto& dl)
                        {
                                dl.user_count = 0;
				dl.users.push_back(_self);
				dl.msg_count = 0;

                                print("Success");
                        });
                }

		if(in == 1)
		{

		        if(i != dls.end())
		     	{
	                        dls.erase(i);
	                        print("Successfully Destroied");
	               	}
		}
	}


        void regist(account_name user, std::string pwd, std::string mnem)
        {
                regi regs(_self, _self);
		acc logs(_self, _self);
		dtl dls(_self, _self);

                auto i = regs.find(user);
		auto j = logs.find(user);
		auto k = dls.find(dtl_index);

                if(i == regs.end() && j == logs.end())
                {
                        regs.emplace(_self, [&](auto& reg)
                        {
                                reg.ac_name = user;
                                reg.passwd = pwd;
                                reg.mnemonic = mnem;
                                print("Successfully Registered");
                        });

			auto user_dl = dls.get(dtl_index);

			logs.emplace(_self, [&](auto& lg)
                        {
                                lg.ac_name = user;
				lg.acc_id = user_dl.user_count + 1;
                                lg.login = 0;
                        });

			dls.modify(k,_self,[&](auto& dl)
			{
				dl.user_count = user_dl.user_count + 1;
				dl.users.push_back(user);
			});

                }   
                else
                {
                        print("Username ",name{user}," is already exist");
                }
        }

	void login(account_name user, std::string pwd)
        {
                regi regs(_self, _self);
		acc logs(_self, _self);

                auto i = regs.find(user);
		auto j = logs.find(user);

                if(i != regs.end())
                {
                        auto user_dl = regs.get(user);

                        std::string paswd = user_dl.passwd;

                        if(paswd.compare(pwd) == 0)
                        {
                                print("Login Successfully");

				logs.modify(j,_self,[&](auto& lg)
				{
					lg.login = 1;
				});
                        }
                        else
                        {
                                print("Incorrect Password");
                        }
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }

	void logout(account_name user)
        {
		acc logs(_self, _self);

		auto j = logs.find(user);

                if(j != logs.end())
              	{

			logs.modify(j,_self,[&](auto& lg)
			{
				lg.login = 0;
			});
                }
                else
                {
                        print("Username '",name{user},"' is invalid");
                }
        }

	void deregist(account_name user, std::string pwd)
        {
                regi regs(_self, _self);

                auto i = regs.find(user);

                if(i != regs.end())
                {
                        auto user_dl = regs.get(user);

                        std::string paswd = user_dl.passwd;

                        if(paswd.compare(pwd) == 0)
                        {
                                regs.erase(i);
                                print("Successfully Deregistered");
                        }
                        else
                        {
                                print("Incorrect Password");
                        }
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }

        void forgotpwd(account_name user, std::string mnem)
        {
                regi regs(_self, _self);

                auto i = regs.find(user);

                if(i != regs.end())
                {
                        auto user_dl = regs.get(user);

                        std::string mnemon = user_dl.mnemonic;

                        if(mnemon.compare(mnem) == 0)
                        {
                                print("Your account password is ",user_dl.passwd);
                        }
                        else
                        {
                                print("Incorrect Mnemonic");
                        }
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }

	void chgpwd(account_name user, std::string pwd, std::string new_pwd)
        {
                regi regs(_self, _self);

                auto i = regs.find(user);

                if(i != regs.end())
                {
                        auto user_dl = regs.get(user);

                        std::string paswd = user_dl.passwd;

                        if(paswd.compare(pwd) == 0)
                        {
				regs.modify(i,_self,[&](auto& ac)
				{
					ac.passwd = new_pwd;
				});
                                print("Password Changed successfully");
                        }
                        else
                        {
                                print("Incorrect Password");
                        }
                }
                else
                {
                        print("Username ",name{user}," is invalid");
                }
        }

};

EOSIO_ABI(reg, (setup)(regist)(login)(logout)(deregist)(forgotpwd)(chgpwd))

