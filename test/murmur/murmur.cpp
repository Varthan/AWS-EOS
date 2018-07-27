
#include<eosiolib/eosio.hpp>
#include<eosiolib/print.hpp>
#include<string>

using namespace eosio;
using namespace std;
using std::string;

namespace twitterdata{

class twitter: public contract{

 using contract::contract;

        public:
                twitter(account_name self):
			contract(self){}


	//@abi table accregdata i64
	struct accregdata{
		
		account_name _name;
		string password;
		string secret;

		uint64_t primary_key() const{return _name;}

		EOSLIB_SERIALIZE(accregdata,(_name)(password)(secret))
	
		};

	typedef multi_index<N(accregdata),accregdata> _regdatas;

	//@abi table statuslog i64

	struct statuslog{

		account_name _regnam;
		std::vector<account_name> _onlista;
		uint64_t count = 0;

		uint64_t primary_key() const{return _regnam;}

		EOSLIB_SERIALIZE(statuslog,(_regnam)(_onlista)(count))
	};

	typedef multi_index<N(statuslog),statuslog> _statuslog;



	//@abi action
	void admin(account_name admin_){

		
		_statuslog loggs(_self,_self);

		auto irt = loggs.find(admin_);


		if(irt == loggs.end()){
			loggs.emplace(_self,[&](auto& opt){

					opt._regnam = admin_;
				});
			}else{print("the name is alreday available");}
	}


	//@abi action

	void login(account_name _name,string pass,account_name admin_){

		_regdatas umss(_self,_self);

		auto ymr = umss.find(_name);

		if(ymr == umss.end()){
		print("you have to create a accout");
		}else{

			_statuslog loggs(_self,_self);

			auto igdr = loggs.find(admin_);

				if(igdr == loggs.end()){
					print("you have to create a account");
					}else{

						auto ddr = umss.get(_name);

						if(pass == ddr.password){

							loggs.modify(igdr,_self,[&](auto& kpst){

								kpst._onlista.push_back(_name);
							});
							}else{print("you have to check the password");}
						}
			}
	}


	//@abi logout

	void logout(account_name _name,account_name admin_){

		_statuslog loggs(_self,_self);

		auto your = loggs.find(_name);

		if(your == loggs.end()){
			print("you have to create a account");
		}else{
				auto isrp = loggs.get(admin_);

				for(uint64_t i=0;i<=isrp._onlista.size();i++){

						if(_name == isrp._onlista.at(i)){


							loggs.modify(your,_self,[&](auto& opys){

								opys._onlista.erase(opys._onlista.begin()+i);	
							});

						}else{print("you are not logged in");}
					}
			}
	}

	//@abi table chatreg i64

	struct chatreg{

		account_name _nam;
		std::vector<uint64_t> _time;
		std::vector<string> _msg;

		uint64_t primary_key() const{return _nam;}

		EOSLIB_SERIALIZE(chatreg,(_nam)(_time)(_msg))	
	};

	typedef multi_index<N(chatreg),chatreg> _chatreg;


	
	//@abi table postlike i64
	
	struct postlike{
		account_name _nam;
		std::vector<account_name> _liker;
		std::vector<uint64_t> _time;

		uint64_t primary_key() const{return _nam;}
		EOSLIB_SERIALIZE(postlike,(_nam)(_liker)(_time))
	};

	typedef multi_index<N(postlike),postlike> _postlikes;


	//@abi action
	
	void likespos(account_name _postac,account_name _liker,uint64_t _tim){
		 _regdatas dats(_self,_self);

		auto ijl = dats.find(_postac);

		if(ijl == dats.end()){
				print("you have to create the account");
			}else{
				 _regdatas ants(_self,_self);

					auto jus = ants.find(_liker);

						if(jus == ants.end()){

							print("You have to create the account");
							}else{

							_postlikes likes(_self,_self);

							auto yuml = likes.find(_postac);

								if(yuml == likes.end()){
									print("you have to create the account");
									}else{

										 _chatreg regs(_self,_self);
										
										//_postlikes umsc(_self,_self);

	

										auto ghs = regs.get(_postac);
										
										for(uint64_t i=0;i<=ghs._time.size();i++){
								
												if(_tim == ghs._time.at(i)){
													 auto tss = likes.get(_postac);

												
													for(uint64_t j=0;j<tss._liker.size();j++){

														if(_liker == tss._liker.at(j)){
															print("you have to like one time only the post");
															}else{


                                                                                                                                 likes.modify(yuml,_self,[&](auto& icss){

																	icss._liker.push_back(_liker);
																	icss._time.push_back(_tim);
																	});
  																}
														}
													}
												}
										}
							}

				}
	
	}



	//Dislike function

	//@abi action

        void dislikescha(account_name _posac,account_name _liker,uint64_t _tim){

                         _regdatas dats(_self,_self);

                        auto imr = dats.find(_posac);

                        if(imr == dats.end()){

                                print("You have to create the account");
                                }else{
                                        _regdatas ants(_self,_self);

                                        auto iop = ants.find(_liker);

                                        if(iop == ants.end()){
                                                        print("you have to create a account");
                                                }else{

                                                _postlikes jiop(_self,_self);

                                                auto lsp = jiop.find(_posac);

                                                        if(lsp == jiop.end()){

                                                                print("you have to create a account");
                                                                }else{

                                                                         _postlikes likes(_self,_self);

                                                                        auto imo = likes.get(_posac);

                                                                        for(uint64_t i=0;i<=imo._time.size();i++){

                                                                                                if(_tim == imo._time.at(i)){
														 for(uint64_t j=0;j<=imo._liker.size();j++){

                                                                                                                if(_liker == imo._liker.at(j)){

                                                                                                                        jiop.modify(lsp,_self,[&](auto& jsp){

                                                                                                                                jsp._liker.erase(jsp._liker.begin()+i);
                                                                                                                                jsp._time.erase(jsp._time.begin()+j);
                                                                                                                                });
                                                                                                                        }else{print("the person is not like any post");}
                                                                                                                }
                                                                                                        }else{print("the required post is not available in the list");}
                                                                                                }
                                                                                        }

                                                                                        }
                                                                        }


                }
	
	
        //@abi action

        void userreg(account_name _nam,string _pass,string _secret){

                _regdatas dats(_self,_self);

                auto iter = dats.find(_nam);
                if(iter == dats.end()){

                        dats.emplace(_self,[&](auto& atss){

                                        atss._name = _nam;
                                        atss.password = _pass;
                                        atss.secret = _secret;
                                });

			


                }else{

                                print("The details are already available");
                        }
		
		_chatreg regss(_self,_self);

		auto imr = regss.find(_nam);

		if(imr == regss.end()){
			
			regss.emplace(_self,[&](auto& stp){
				
				stp._nam = _nam;
			});
			}else{print("already exsists");}

		
		_fromchat chats(_self,_self);
		
		auto iqr = chats.find(_nam);
		
		if(iqr == chats.end()){
			
			chats.emplace(_self,[&](auto& lss){

				lss._nam = _nam;
			});
		}else{print("the person is already exsists in the table");}



		_pritos toss(_self,_self);
		
		auto ibl = toss.find(_nam);
		
		if(ibl == toss.end()){

		toss.emplace(_self,[&](auto& tss){

				tss._nam = _nam;
			});
		}else{
			
			print("the person is already in the table");
			}

		_followers werds(_self,_self);
		
		auto ipg = werds.find(_nam);

		if(ipg == werds.end()){
		
			werds.emplace(_self,[&](auto& klg){
				
				klg._nam = _nam;
			});
		}else{print("the name is already exsists");}

		_following owing(_self,_self);
	
		auto ixr = owing.find(_nam);
		
		if(ixr == owing.end()){
				owing.emplace(_self,[&](auto& ltp){
			
				ltp._name = _nam;
				});
			}else{print("the name is already exsist in the table");}
			
			_following owings(_self,_self);

                auto cvb = owings.find(_nam);

                if(cvb == owings.end()){

                                owings.emplace(_self,[&](auto& spo){

                                                spo._name = _nam;
                                        });
                        }else{print("you have already account ");}


		_sharepos reposs(_self,_self);
	
		auto rewqs = reposs.find(_nam);
	
		if(rewqs == reposs.end()){

				reposs.emplace(_self,[&](auto& vbsd){
					vbsd.poster = _nam;

				});
			}else{print("you have already account ");}

		_poshare uumss(_self,_self);

		auto ksgx = uumss.find(_nam);

		if(ksgx == uumss.end()){
						
			uumss.emplace(_self,[&](auto& cvbs){

			cvbs.posters = _nam;
			});
			}else{print("you have already account");}


		
		
        }

	//@abi action
        void changpass(account_name _nam,string _pass,string _sec){

                _regdatas datss(_self,_self);

                auto itr = datss.find(_nam);

                if(itr == datss.end()){
                        print("You have to create the account");
  }else{

                                auto pass_c = datss.get(_nam);

                                if(pass_c.secret == _sec){

                                                datss.modify(itr,_self,[&](auto& tss){

                                                        tss.password = _pass;
                                                        tss.secret = _sec;
                                                });
				}
		}
        }


	
	//@abi action
	void timechat(account_name _nam,string _msg){


			_chatreg regss(_self,_self);
			
			auto ikr = regss.find(_nam);
			
				if(ikr == regss.end()){
						print("you have to create the account");
					}else{
					
						regss.modify(ikr,_self,[&](auto& mss){
								
							mss._time.push_back(now());
							mss._msg.push_back(_msg);
							});
			}
		}


	//private chat
		
	//@abi table prifrom i64
	
	struct prifrom{
	
	account_name _nam;
	std::vector<uint64_t> _time;
	std::vector<string> _fromchat;

	uint64_t primary_key() const{return _nam;}

	EOSLIB_SERIALIZE(prifrom,(_nam)(_time)(_fromchat))
	};

	
	typedef multi_index<N(prifrom),prifrom> _fromchat;

	//@abi table prito i64
	struct prito{
		
	account_name _nam;
	std::vector<uint64_t> _time;
	std::vector<string> _tochat;

	uint64_t primary_key() const{return _nam;}
	EOSLIB_SERIALIZE(prito,(_nam)(_time)(_tochat))
	};

	typedef multi_index<N(prito),prito> _pritos;


	//@abi action
	
	void prichat(account_name fronam,account_name tonam,string _msg){

		_regdatas imss(_self,_self);

		auto iter = imss.find(fronam);
		
		if(iter == imss.end()){
			print("you have to create the person for chat");
		}else{
				
			_regdatas imrs(_self,_self);
		
			auto imr = imrs.find(fronam);

				if(imr == imrs.end()){

					print("you have to create a person for send the msg");
				}else{
					
						_fromchat froms(_self,_self);

						auto kpr = froms.find(fronam);

						if(kpr == froms.end()){
								print("you have to create the account for send");
							}else{

								froms.modify(kpr,_self,[&](auto& jus){
									
									jus._time.push_back(now());
									jus._fromchat.push_back(_msg);
									});
								}


							_pritos totas(_self,_self);

							auto iwq = totas.find(tonam);
							
							if(iwq == totas.end()){
								print("you have to create the account");
							}else{
						
								totas.modify(iwq,_self,[&](auto& moss){
									
									moss._time.push_back(now());
									moss._tochat.push_back(_msg);
								});
							}
					
					}

				
			}		
	}


	//@abi table follower i64
	
	struct follower{
		
	account_name _nam;
	std::vector<account_name> _follow;

	uint64_t primary_key() const{return _nam;}

	EOSLIB_SERIALIZE(follower,(_nam)(_follow))
	};

	typedef multi_index<N(follower),follower> _followers;

	
	//@abi action
	void follow(account_name _acc,account_name follo_){
		
		_regdatas mss(_self,_self);
	
		auto lop = mss.find(_acc);
		
		if(lop == mss.end()){
			print("you have to create the person");
			}else{
				
				_regdatas msrs(_self,_self);

				auto ipt = msrs.find(follo_);
		
				if(ipt == msrs.end()){
						print("you have to create the person or try to register");
					}else{
						
						_followers ssrs(_self,_self);
						
						auto rbs = ssrs.find(_acc);
					
							if(rbs == ssrs.end()){
								print("you have to create the person");
								}else{

									ssrs.modify(rbs,_self,[&](auto& lkd){
											
											lkd._follow.push_back(follo_);
										});

										ownfollow(_acc,follo_);
									}
					}
			}
	}


	//@abi action
	
	void unfollow(account_name _acc,account_name _unf){

		 _regdatas mss(_self,_self);

		auto iter = mss.find(_acc);

			if(iter == mss.end()){
			
				print("you have to create the person for chat");
			}else{
					_regdatas msrs(_self,_self);

					auto psr = msrs.find(_unf);

					if(psr == msrs.end()){
						print("you have to create the person for chat");
					}else{
							
						 _followers ssrs(_self,_self);
							
							auto lop = ssrs.find(_acc);
						
							if(lop == ssrs.end()){
								print("you have to create a person for chat");
								}else{
	
											auto its = ssrs.get(_acc);
										
											for (uint64_t i = 0; i < its._follow.size(); i++){
					
											
													if(_unf == its._follow.at(i)){
													ssrs.modify(lop,_self,[&](auto& klh){

														klh._follow.erase(klh._follow.begin() + i);
													});


													unfollowes(_acc,_unf);
													}else{

																print("the person is not in the table");
														}
													
												}
											}
									}
						}
				

		
	}


	//@abi table following i64
	
	struct following{
	
	account_name _name;
	std::vector<account_name> _folng;
	
	uint64_t primary_key() const{return _name;}

	EOSLIB_SERIALIZE(following,(_name)(_folng))
	};

	typedef multi_index<N(following),following> _following;


	//@abi action
	
	void ownfollow(account_name folnam,account_name unam){

	 _regdatas mss(_self,_self);

                auto iter = mss.find(folnam);

                        if(iter == mss.end()){
						print("the person have to register");
						}else{
							_regdatas msrs(_self,_self);

                                        auto psr = msrs.find(unam);

                                        if(psr == msrs.end()){
						
								print("you have to create the account ");

							}else{

								_following owss(_self,_self);
								
								auto uiq = owss.find(unam);
								
									if(uiq == owss.end()){
											print("you have to create a account");
										}else{

											owss.modify(uiq,_self,[&](auto& lps){
								
												lps._folng.push_back(folnam);
												});
										}
								}
	
						}
	}

	
	
	//@abi action	
	void unfollowes(account_name folnam,account_name unam_){

		_regdatas mss(_self,_self);

                auto iter = mss.find(folnam);

		if(iter == mss.end()){

				print("you have to create a account");
			}else{

				 _regdatas msc(_self,_self);

				auto yuml = msc.find(unam_);
				
				if(yuml == msc.end()){

					print("you have to create a account");
					}else{

						_following iows(_self,_self);

						auto ups = iows.find(unam_);

						if(ups == iows.end()){
							print("you have to create a account ");
							}else{

							auto yiop = iows.get(unam_);

								for(uint64_t i=0;i<= yiop._folng.size();i++){

										if(folnam == yiop._folng.at(i)){

											iows.modify(ups,_self,[&](auto& kjs){
													
												kjs._folng.erase(kjs._folng.begin() + i);
											});
											}else{
												print("the name is not in the list");
												}
									}
							}
					}
			}

	}


	
	

	//@abi table sharepos i64

	struct sharepos{
	
	account_name poster;
	std::vector<account_name> _poscr;
	std::vector<uint64_t> shartime;
	
	uint64_t primary_key() const{return poster;}

	EOSLIB_SERIALIZE(sharepos,(poster)(_poscr)(shartime))
	};	


	typedef multi_index<N(sharepos),sharepos> _sharepos;


	//@abi table poshare i64
	
	struct poshare{

	account_name posters;
	std::vector<account_name> _shareacc;
	std::vector<string> _sharemsg;

	uint64_t primary_key() const{return posters;}

	EOSLIB_SERIALIZE(poshare,(posters)(_shareacc)(_sharemsg))
	};

	typedef multi_index<N(poshare),poshare> _poshare;

	
	//@abi action

	void sharepost(account_name _poster,account_name shareac,account_name _poscr,string _msg){

		_regdatas tass(_self,_self);

		auto iter = tass.find(_poster);
		
		if(iter == tass.end()){
			print("You have to create a account");
			}else{
				
				_regdatas moss(_self,_self);
			
				auto isr = moss.find(shareac);

					if(isr == moss.end()){
						print("you have to create a account");
						}else{

							_regdatas yss(_self,_self);

							auto iso = yss.find(_poscr);
						
								if(iso == yss.end()){
									print("you have to create a account");
									}else{
										_sharepos klso(_self,_self);

										auto klst = klso.find(_poster);

											if(klst == klso.end()){
												print("you have to create a account");
												}else{
													klso.modify(klst,_self,[&](auto& omss){
													
													omss._poscr.push_back(_poscr);
													omss.shartime.push_back(now());
													});


															}

													_poshare shares(_self,_self);
													
													auto shj = shares.find(_poster);

													if(shj == shares.end()){
                                                                                                                print("you have to create the account");

                                                                                                                }else{

                                                                                                                        shares.modify(shj,_self,[&](auto& lvss){

                                                                                                                                lvss._shareacc.push_back(shareac);
                                                                                                                                lvss._sharemsg.push_back(_msg);
                                                                                                                        });

													}
										}
						     }
			     }
	}



};
EOSIO_ABI(twitter,(likespos)(dislikescha)(userreg)(changpass)(timechat)(prichat)(follow)(unfollow)(ownfollow)(unfollowes)(sharepost)(login)(logout)(admin))
}



