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
class DoublyLinkedList {
 public:
    DoublyLinkedList() {
        head = nullptr;
        size_ = 0;
    }

    ~DoublyLinkedList() {
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
    }  // insere no fim
    /**
	 * @brief       Inserir no Ini­cio 		
	 *
	 * @details 	Inseri um elemento no ini­cio da lista.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void push_front(const T& data) {
    Node *new_ = new Node(data, nullptr, head);
	head = new_;
	 if (new_->next() != nullptr) {
		new_->next()->prev(new_);
	 }
		++size_;
    }  // insere no início
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
			throw std::out_of_range("ERRO POSIÇÃO INVALIDA");
		}
		if(index == 0) {
			push_front(data);
		} else {
			Node *it = head;
			Node *new_ = new Node(data, nullptr, nullptr);
			for(int i = 0; i < (index-1); i++) {
				it = it->next();
			}
			new_->next(it->next());
			if(it->next() != nullptr) {
				it->next()->prev(new_);
			}
			new_->prev(it);
			it->next(new_);
			++size_;
		}
    }  // insere na posição
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
			while(it != nullptr && data > it->data()) {
				it = it->next();
				++index;
			}
			insert(data, index);
		}
    }  // insere em ordem
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
			throw std::out_of_range("ERRO POSIÇÃO INVALIDA");
		} else {
			if(index == 0) {
				return pop_front();
			} else {
				Node *prev_ = head;
				Node *delete_;
				for(int i = 0; i < (index-1); i++) {
					prev_ = prev_->next();
				}
				delete_ = prev_->next();
				T back = delete_->data();
				if(delete_->next() != nullptr) {
					delete_->next()->prev(prev_);
				}
				prev_->next(delete_->next());
				delete delete_;
				--size_;
				return back;
			}
		}
    }  // retira da posição
    /**
	 * @brief       Retirar do Fim 		
	 *
	 * @details 	Retira o ultimo elemento da lista, usando o método pop().
	 * 
	 * @return      Retorna o elemento retirado da ultima posição da lista.
	 */
    T pop_back() {
       return pop(size_-1);
    }  // retira do fim
    /**
	 * @brief 		Retirar do Ini­cio
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
			if(head != nullptr) {
				head->prev(nullptr);
			}
			delete it;
			--size_;
			return back;
		}
    }  // retira do início
    /**
	 * @brief       Remover Especí­fico 		
	 *
	 * @details 	Remove um elemento especí­fico da lista, utilizando métodos
	 *              pop() e find().
	 *
	 * @param       data    Elemento a ser retirado da lista.
	 */
    void remove(const T& data) {
       pop(find(data));
    }  // retira específico
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
    }  // lista vazia
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
        if (empty()) {
			return false;
		} else {
			Node *it = head;
			for(int i = 0; i < size_; i++) {
				if(data == it->data()) {
					return true;
				} else {
					it = it->next();
				}
			}
			return false;
		}
    }  // contém
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
        throw std::out_of_range("ERRO POSIÇÃO INVÁLIDA");
    }  // acesso a um elemento (checando limites)
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
        throw std::out_of_range("ERRO POSIÇÃO INVÁLIDA");
    }  // getter constante a um elemento
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
    }  // posição de um dado
    /**
	 * @brief       Tamanho da Lista 		
	 *
	 * @details 	Verifica o tamanho da lista.
	 * 
	 * @return      Retorna o tamanho da lista.
	 */
    std::size_t size() const {
        return size_;
    }  // tamanho

 private:
    class Node {
     public:
       explicit Node(const T& data) : data_{data}
        {}

        Node(const T& data, Node* next) : data_{data}, next_{next}
        {}

        Node(const T& data, Node* prev, Node* next) :
        data_{data}, prev_{prev}, next_{next}
        {}

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        /**
        * prev_   Node anterior.
        */
        Node* prev_;
        /**
        * next_   Próximo node.
        */
        Node* next_;
    };
    /**
	 * head    Ponteiro para primeiro node da lista.
	 */
    Node* head;
    /**
	 * size_   Tamanho da lista. 
	 */
    std::size_t size_;
};

}  // namespace structures

#endif
