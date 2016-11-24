// Copyright [2016] <Felipe Longarai Trisotto (15103032) e William Magagnin Kair (15200624)>

#ifndef SUPERMARKET_HPP
#define SUPERMARKET_HPP

#include <cstdint>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "Client.hpp"
#include "Cashier.hpp"
#include "circular_list.h"

namespace structures {

class Supermarket {
 private:
 	int next_client;
 	int n_clients;
 	int count;  // contador
 	int t_time;
 	int n_cashiers;
 	int n_quits;
 	int val_quits;
 	int T_; // numero de comparacao da fila para adicionar caixa
 	structures::CircularList<Cashier> cachiers{};
    std::string name;
 	

 public:
 	Supermarket () {
        read_file();
 		n_quits = 0;
 		val_quits = 0;
        count = 0;
    }
 	void run(){
 		while(count < t_time){

 			bool new_cachier_ = check_cashiers();
            
 			// verifica se precisa adicionar cliente
 			if (next_client == count)
 			{
 				new_client();
 			}
 			// verifica necessidade de um novo caixa
 			if (new_cachier_)
 			{
 				new_cachier();
 			}

 			count++;

 		}

 	}

 	void new_client(){
 		Client* client = new Client(count);
        Cashier* cashier;
        Cashier* aux_cashier;
        cashier = &cachiers.at(0);
        aux_cashier = &cachiers.at(0);

 		if (full_queue())
 		{
 			++n_quits;
 			val_quits = val_quits + client->spend()*3;

 		} else {

	 		if (client->for_product()) // escolhe fila por produto
	 		{
	 			cashier = &cachiers.at(0);
                aux_cashier = &cachiers.at(0);

	 			for (int i = 1; i < n_cashiers; ++i)
	 			{
	 				aux_cashier = &cachiers.at(i);
	 				
	 				if (cashier->products() > aux_cashier->products() )
	 				{
	 					cashier = aux_cashier;
	 				}
	 			}

	 			
	 		} else {  // escolhe fila por pessoas

                cashier = &cachiers.at(0);
                aux_cashier = &cachiers.at(0);


	 			for (int i = 1; i < n_cashiers; ++i)
	 			{
	 				aux_cashier = &cachiers.at(i);
                    
	 				
	 				if (cashier->size() > aux_cashier->size() )
	 				{
	 					cashier = aux_cashier;
	 				}
	 			}
	 		}
            
            if (cashier->size() > 15)
            {
                ++n_quits;
                val_quits = val_quits + client->spend()*3;
            }
            else
            {
               cashier->add_client(*client);
            }
            
            next_client = count + n_clients;

	 	}	

 	}
 	void read_file(){
 	    bool choice;
 	    std::cout << "DIGITE 0 : INSERIR DADOS\n"
 	                "DIGITE 1 : RECEBER DADOS DO ARQUIVO PADRAO";
 	    std::cin >> choice;
 	    if(choice){
     	    std::ifstream file;
            file.open("teste.txt");
            
            if (file.is_open()) {
                char line[40];
                
                file.getline(line,40); //le nome
                name = line;
                
                file >> t_time; //tempo total de simulacao
                t_time = t_time*3600;
                
                file >> n_clients;
                
                file >> T_;
                
                n_cashiers = T_;
                
                
                Cashier* cashier ;
                std::string id;
                int pro;
                int sal;
    
                for (int i = 0; i < n_cashiers; i++) {
                    
                    file >> id;
                    file >> pro;
                    file >> sal;
                    
                    cashier = new Cashier(id, pro, sal);
                    cachiers.push_back(*cashier);
                    
                }
                
                while (!file.eof()) {
                    file >> line;
                }
                
                
            }
 	    } else {
 	        std::string line;
            std::cout << "DIGITE O NOME DO SUPERMERCADO\n";
            std::cin >> line; //le nome
            name = line;
            
            std::cout << "DIGITE O TEMPO DE SIMULAÇÃO\n";
            std::cin >> t_time; //tempo total de simulacao
            t_time = t_time*3600;
            
            std::cout << "DIGITE O NUMERO DE CLIENTES POR SEG\n";
            std::cin >> n_clients;
            
            std::cout << "DIGITE O NUMERO DE CAIXAS\n";
            std::cin >> T_;
            
            n_cashiers = T_;
            
            
            Cashier* cashier ;
            std::string id;
            int pro;
            int sal;

            for (int i = 0; i < n_cashiers; i++) {
                
                std::cout << "DIGITE O NOME DO CAIXA\n";
                std::cin >> id;
                std::cout << "DIGITE 1,2,3 DE ACORDO COM O NIVEL DE PRODUTIVIDADE\n";
                std::cin >> pro;
                std::cout << "DIGITE O SALARIO DO CAIXA\n";
                std::cin >> sal;
                
                cashier = new Cashier(id, pro, sal);
                cachiers.push_back(*cashier);
                
            }
 	    }
        

 	}

 	void new_cachier(){

 		

 		int productivity = std::rand()%3 + 1; // numero entre 1 e 3
 		int salary_ = 1600; // salario minimo dobrado (sobre_hora) ~POG
        Cashier* cashier ;
        cashier = new Cashier("Caixa Extra", productivity, salary_);

 		cachiers.push_back(*cashier);
 		n_cashiers++;


 	}
 	bool check_cashiers(){

 		Cashier* cashier;

 		for (int i = 0; i < n_cashiers; ++i)
 			{
 				cashier = &cachiers.at(i);
                int end_time = cashier->next_end();

 				if (end_time <= count && end_time > 0)
 				{
 					cashier->new_visit();
 				}

 				if (cashier->size() < T_ )
 				{
 					return false;
 				}
 			}
        return true;
 	}
 	bool full_queue(){
 		Cashier* cashier;
 		bool full = true;

 		for (int i = 0; i < n_cashiers; ++i)
 			{
 				cashier = &cachiers.at(i);

 				if (cashier->size() < 10 )
 				{
 					full = false;
 				}

 			}

 		return full;

 	}
    void outputs(){
        int t_earning = 0;
        int t_clients = 0;
        
        std::cout << "SUPERMERCADO " << name << std::endl;
        
        for (int i = 0; i < n_cashiers; ++i)
        {
            Cashier& cashier = cachiers.at(i);
            
            t_earning += cashier.t_earning();
            t_clients += cashier.n_visits();

            auto mean_revenue = 0;
            if (cashier.n_visits() > 0) {
                cashier.t_earning()/cashier.n_visits();
            }
            
            std::cout << "CAIXA: " << cashier.id()
                << "\nEFICIÊNCIA: " << cashier.productivity()
                << "\nFATURAMENTO: " << cashier.t_earning()
                << "\nLUCRO: " << cashier.t_earning()-cashier.salary()
                << "\nFATURAMENTO MEDIO POR CLIENTE: " << mean_revenue
                << std::endl;
        }
        int m_clients = t_clients/n_cashiers; // media de clientes por caixa
        
        std::cout << "FATURAMENTO TOTAL: " << t_earning
            << "\nFATURAMENTO MEDIO POR CAIXA: " << t_earning/n_cashiers
            << "\nTEMPO MEDIO NA FILA: " << t_time/m_clients
            << "\nTOTAL DE CLIENTES: " << t_clients
            << "\nTOTAL DE CLIENTES DESISTENTES: " << n_quits
            << "\nFATURAMENTO PERDIDO POR DESISTENCIA: " << val_quits
            << std::endl;
        
        
    }
 	
};

} // fim do namespace


#endif
