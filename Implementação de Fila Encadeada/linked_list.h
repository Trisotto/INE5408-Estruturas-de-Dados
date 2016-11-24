// Copyright [2016] <Felipe Longarai Trisotto>

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

/**
 * @brief  		Implementação de uma Estrutura de Lista Encadeada em C++
 */
template<typename T>
class LinkedList {
 public:
     /**
	 * @brief 		Construtor Padrão
	 *
	 * @details 	Head aponta para null e size_ é igual a 0.
	 */
    LinkedList() = default;
     /**
	 * @brief 		Destrutor
	 *
	 * @details 	Chamado o método clear().
	 */
    ~LinkedList() {
        clear();
    }
    /**
	 * @brief 		Limpa Lista
	 *
	 * @details 	Destroi todos os elementos da lista.
	 */
    void clear() {
        Node *it = head;
		while (it != nullptr) {
			it = it->next();
			pop_front();
		}
		size_ = 0;
    }
    /**
	 * @brief       Inserir no Fim 		
	 *
	 * @details 	Inseri um elemento no fim da lista.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void push_back(const T& data) {
        insert(data, size_);
    }
    /**
	 * @brief       Inserir no Início 		
	 *
	 * @details 	Inseri um elemento no início da lista.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void push_front(const T& data) {
        Node *new_ = new Node(data, head);
        head = new_;
		++size_;
    }
    /**
	 * @brief       Inserir na Posição 		
	 *
	 * @details 	Inseri um elemento na posição passada como parâmetro. 
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 * @param       index   Posição da lista a ser inserido o elemento.
	 */
    void insert(const T& data, std::size_t index) {
        if (index > size_ || index < 0) {
			throw std::out_of_range("ERRO POSIÇÃO INVÁLIDA");
		}
		if(index == 0) {
			push_front(data);
		} else {
			Node *it = head;
			Node *new_ = new Node(data);
			for(int i = 0; i < (index-1); i++) {
				it = it->next();
			}
			new_->next(it->next());
			it->next(new_);
			++size_;
		}
	}
	/**
	 * @brief       Inserir em Ordem 		
	 *
	 * @details 	Inseri um elemento em ordem crescente.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void insert_sorted(const T& data) {
        if (empty()) {
			push_front(data);
		} else {
			Node *it = head;
			int index = 0;
			while(it != nullptr && data > (it->data())) {
				it = it->next();
				++index;
			}
			insert(data, index);
		}
    }
    /**
	 * @brief       Acessar Elemento na Posição		
	 *
	 * @details 	Acessa um elemento na posição recebida como parâmetro.
	 *
	 * @param       index   Posição do elemento a ser acessado na lista.
	 * 
	 * @return      Retorna o elemento que está na posição passado como
	 *              parâmetro.
	 */
    T& at(std::size_t index) {
        if (index < size_) {
            Node *it = head;
			for(int i = 0; i < index; i++) {
					it = it->next();
				}
			return it->data();
        }
        throw std::out_of_range("POSIÇÃO INVÁLIDA");
    }
    /**
	 * @brief       Acessar Elemento na Posição	como Constante	
	 *
	 * @details 	Acessa um elemento na posição recebida como parâmetro.
	 *
	 * @param       index   Posição do elemento a ser acessado na lista.
	 * 
	 * @return      Retorna o elemento que está na posição passado como
	 *              parâmetro.
	 */
    const T& at(std::size_t index) const {
        if (index < size_) {
            Node *it = head;
			for(int i = 0; i < index; i++) {
					it = it->next();
				}
			return it->data();
        }
        throw std::out_of_range("POSIÇÃO INVÁLIDA");
    }
    /**
	 * @brief       Retirar da Posição 		
	 *
	 * @details 	Retira da lista o elemento na posição passada como
	 *              parâmetro.
	 *
	 * @param       index   Posição na lista do elemento a ser retirado.
	 * 
	 * @return      Retorna o elemento retirado na posição passada como
	 *              parâmetro.
	 */
    T pop(std::size_t index) {
        if (empty()) {
			throw std::out_of_range("ERRO LISTA VAZIA");
		}
		if(index > size_-1 || index < 0) {
			throw std::out_of_range("ERRO POSIÇÃO INVÁLIDA");
		} else {
			if(index == 0) {
				return pop_front();
			} else {
				Node *prev = head;
				Node *delete_;
				for(int i = 0; i < (index-1); i++) {
					prev = prev->next();
				}
				delete_ = prev->next();
				T back = delete_->data();
				prev->next(delete_->next());
				delete delete_;
				--size_;
				return back;
			}
		}
    }
    /**
	 * @brief       Retirar do Fim 		
	 *
	 * @details 	Retira o ultimo elemento da lista, usando o método pop().
	 * 
	 * @return      Retorna o elemento retirado da ultima posição da lista.
	 */
    T pop_back() {
       return pop(size_-1);
    }
    /**
	 * @brief 		Retirar do Início
	 *
	 * @details 	Retira o primeiro elemento da lista.
	 * 
	 * @return      Retorna o elemento retirado da primeira posição da lista.
	 */
    T pop_front() {
        if (empty()) {
			throw std::out_of_range("ERRO LISTA VAZIA");
		} else {
			Node *it = head;
			T back = it->data();
			head = it->next();
			delete it;
			--size_;
			return back;
		}
    }
    /**
	 * @brief       Remover Específico 		
	 *
	 * @details 	Remove um elemento específico da lista, utilizando o método
	 *              pop() e find().
	 *
	 * @param       data    Elemento a ser retirado da lista.
	 */
    void remove(const T& data) {
        pop(find(data));
    }
    /**
	 * @brief       Lista Vazia 		
	 *
	 * @details 	Verifica se a lista está vazia.
	 * 
	 * @return      Retorna verdadeiro se a lista está vazia e falso caso
	 *              contrário.
	 */
    bool empty() const {
        return size_ == 0;
    }
    /**
	 * @brief       Contém 		
	 *
	 * @details 	Verifica se o elemento passado como parâmetro está na lista.
	 *
	 * @param       data    Elemento a ser checado se está ou não na lista.
	 * 
	 * @return      Retorna verdadeiro se o elemento está na lista e falso caso
	 *              não esteja.
	 */
    bool contains(const T& data) const {
        		if(empty()) {
			return false;
		} else {
			Node *it = head;
			for(int i = 0; i < size_; i++) {
				if(data == (it->data())) {
					return true;
				} else {
					it = it->next();
				}
			}
			return false;
		}
    }
    /**
	 * @brief       Posição do Dado 		
	 *
	 * @details 	Verifica qual a posição na lista do elemento passado como
	 *              parâmetro.
	 *
	 * @param       data    Elemento para qual deve ser encontrado sua posição
	 *                      na lista.
	 * 
	 * @return      Retorna a posição na lista onde se encontra o elemento.
	 */
    std::size_t find(const T& data) const {
		Node *it = head;
		for(int i = 0; i < size_; i++) {
			if(data == (it->data())) {
				return i;
			}
			it = it->next();
		}
		return size_;
    }
    /**
	 * @brief       Tamanho da Lista 		
	 *
	 * @details 	Verifica o tamanho da lista.
	 * 
	 * @return      Retorna o tamanho da lista.
	 */
    std::size_t size() const {
        return size_;
    }

 private:
    /**
	 * @brief 		Representa um Elemento da Lista
	 */
class Node {
 public:
        /**
    	 * @brief 		Construtor
    	 *
    	 * @details 	Constroi um node com o dado passado como parâmetro.
    	 *
    	 * @param       data    Dado a ser gardado pelo node.
    	 */
        explicit Node(const T& data):
            data_{data}
        {}
        /**
    	 * @brief       Construtor 		
    	 *
    	 * @details 	Constroi um node com o dado passado como parâmetro e o
    	 *              próximo node.
    	 *
    	 * @param       data    Dado a ser gardado pelo node.
    	 * @param       next    Próximo node a ser gardado pelo node.
    	 */
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
       /**
	    * @brief    Getter do Dado		
	    *
	    * @details 	Pega o dado do node.
	    * 
	    * @return   Retorna o dado do node.
	    */
        T& data() {
            return data_;
        }
       /**
	    * @brief 		Getter Constante do Dado
	    *
	    * @details 	    Pega o dado, como constante, do node.
	    * 
	    * @return       Retorna o dado, como constante, do node.
	    */
        const T& data() const {
            return data_;
        }
       /**
	    * @brief        Getter do Próximo Node 		
	    *
	    * @details 	    Pega o próximo node.
	    *  
	    * @return       Retorna o próximo node.
	    */
        Node* next() {
            return next_;
        }
       /**
	    * @brief        Getter Constante do Próximo Node 		
	    *
	    * @details 	    Pega o próximo node como constante.
	    * 
	    * @return       Retorna o próximo node como constante.
	    */
        const Node* next() const {
            return next_;
        }
       /**
	    * @brief        Setter do Próximo Node 		
	    *
	    * @details 	    Altera o próximo node.
	    *
	    * @param        node    Novo valor do próximo node.
	    */
        // setter: próximo
        void next(Node* node) {
            next_ = node;
        }

 private:
       /**
	    * data_   Dado guardado pelo node.
	    */     
        T data_;
       /**
        * next_   Próximo node.
        */
        Node* next_{nullptr};
};
    /**
	 * @brief 		Último Nodo da Lista
	 *
	 * @details 	Pega o último nodo da lista.
	 *
	 * @return      Retorna o último nodo da lista.
	 */
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    /**
	 * head    Ponteiro para primeiro node da lista.
	 */
    Node* head{nullptr};
    /**
	 * size_   Tamanho da lista. 
	 */
    std::size_t size_{0u};
};

}  // namespace structures

#endif

