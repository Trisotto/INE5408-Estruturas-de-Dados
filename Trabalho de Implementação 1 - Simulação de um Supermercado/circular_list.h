// Copyright [2016] <Felipe Longarai Trisotto (15103032) e William Magagnin Kair (15200624)>

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <memory>
#include <cstdint>
#include <stdexcept>

namespace structures {
/**
 * @brief  		Implementação de uma estrutura de Lista Encadeada Circular em C++
 */
template<typename T>
class CircularList {
 public:
    CircularList() {
        head = std::make_shared<Node>(T{}, nullptr);
		head->next(head);
		size_ = 0;
    }
    ~CircularList() {
        clear();
    }
    /**
	 * @brief 		Limpa Lista
	 *
	 * @details 	Destroi todos os elementos da lista.
	 */
    void clear() {
        head = std::make_shared<Node>(T{}, nullptr);
		size_ = 0;
    }  // limpar lista
    /**
	 * @brief       Inserir no Fim 		
	 *
	 * @details 	Inseri um elemento no fim da lista.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void push_back(const T& data) {
        if (empty()) {
			return push_front(data);
        }
		auto it = ptr(size_-1);
		it->next(std::make_shared<Node>(data, head));
        ++size_;
    }  // inserir no fim
    /**
	 * @brief       Inserir no Ini­cio 		
	 *
	 * @details 	Inseri um elemento no ini­cio da lista.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void push_front(const T& data) {
      head->next(std::make_shared<Node>(data, head->next()));
      ++size_;
    }  // inserir no início
    /**
	 * @brief       Inserir na Posição 		
	 *
	 * @details 	Inseri um elemento na posição passada como parametro. 
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 * @param       index   Posição da lista a ser inserido o elemento.
	 */
    void insert(const T& data, std::size_t index) {
        if (index < 0 || index > size_) {
        throw std::out_of_range("ERRO POSIÇÃO INVALIDA");
        }
        if (index == 0) {
	        return push_front(data);
        }
	    if (index == size_) {
		    return push_back(data);
	    }
	    auto it = ptr(index-1);
	    it->next(std::make_shared<Node>(data, it->next()));
        ++size_;
    }  // inserir na posição
    /**
	 * @brief       Inserir em Ordem 		
	 *
	 * @details 	Inseri um elemento em ordem crescente.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void insert_sorted(const T& data) {
        if (empty()) {
			return push_front(data);
        }
		int index = 0;
		auto it = head->next();
		while (index < size_ && data > it->data()) {
			index++;
			it = it->next();
		}

		insert(data, index);
    }  // inserir em ordem
    /**
	 * @brief       Acessar Elemento na Posição		
	 *
	 * @details 	Acessa um elemento na posição recebida como parametro.
	 *
	 * @param       index   Posição do elemento a ser acessado na lista.
	 * 
	 * @return      Retorna o elemento que esta na posição passado como
	 *              parametro.
	 */
    T& at(std::size_t index) {
        return ptr(index)->data();
    }  // acessar em um indice (com checagem de limites)
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
         return ptr(index)->data();
    }  // versão const do acesso ao indice
    /**
	 * @brief       Retirar da Posição 		
	 *
	 * @details 	Retira da lista o elemento na posição passada como
	 *              parametro.
	 *
	 * @param       index   Posição na lista do elemento a ser retirado.
	 * 
	 * @return      Retorna o elemento retirado na posição passada como
	 *              parametro.
	 */
    T pop(std::size_t index) {
        if (empty()) {
			throw std::out_of_range("ERRO LISTA VAZIA");
        }
        if (index < 0 || index >= size_) {
            throw std::out_of_range("ERRO POSIÇÃO INVALIDA");
        }
		if (size_ == 1 || index == 0) {
			return pop_front();
		}
		if (index == size_-1) {
			return pop_back();
		}
		auto it = ptr(index-1);

		T back = it->next()->data();

		it->next(it->next()->next());

		--size_;

		return back;
    }  // retirar da posição
    /**
	 * @brief       Retirar do Fim 		
	 *
	 * @details 	Retira o ultimo elemento da lista, usando o metodo pop().
	 * 
	 * @return      Retorna o elemento retirado da ultima posição da lista.
	 */
    T pop_back() {
        if (empty()) {
			throw std::out_of_range("ERRO LISTA VAZIA");
        }
		if (size_ == 1) {
			return pop_front();
		}
		auto it = ptr(size_-2);

		T back = it->next()->data();

		it->next(head);

		--size_;

		return back;
    }  // retirar do fim
    /**
	 * @brief 		Retirar do Ini­cio
	 *
	 * @details 	Retira o primeiro elemento da lista.
	 * 
	 * @return      Retorna o elemento retirado da primeira posição da lista.
	 */
    T pop_front() {
       if (empty())
			throw std::out_of_range("ERRO LISTA VAZIA");
		T back = head->next()->data();

		head->next(head->next()->next());

		--size_;

		return back;
    }  // retirar do início
    /**
	 * @brief       Remover Especi­fico 		
	 *
	 * @details 	Remove um elemento especi­fico da lista, utilizando o metodo
	 *              pop() e find().
	 *
	 * @param       data    Elemento a ser retirado da lista.
	 */
    void remove(const T& data) {
         pop(find(data));
    }  // remover dado específico
    /**
	 * @brief       Lista Vazia 		
	 *
	 * @details 	Verifica se a lista esta vazia.
	 * 
	 * @return      Retorna verdadeiro se a lista esta vazia e falso caso
	 *              contrario.
	 */
    bool empty() const {
        return size_ == 0;
    }  // lista vazia
    /**
	 * @brief       Contem 		
	 *
	 * @details 	Verifica se o elemento passado como parametro esta na lista.
	 *
	 * @param       data    Elemento a ser checado se esta ou não na lista.
	 * 
	 * @return      Retorna verdadeiro se o elemento esta na lista e falso caso
	 *              não esteja.
	 */
    bool contains(const T& data) const {
		return find(data) != size_;
    }  // lista contém determinado dado?
    /**
	 * @brief       Posição do Dado 		
	 *
	 * @details 	Verifica qual a posição na lista do elemento passado como
	 *              parametro.
	 *
	 * @param       data    Elemento para qual deve ser encontrado sua posição
	 *                      na lista.
	 * 
	 * @return      Retorna a posição na lista onde se encontra o elemento.
	 */
    std::size_t find(const T& data) const {
        if (empty()) {
			throw std::out_of_range("ERRO LISTA VAZIA");
        }
		auto it = head->next();

		for (int i = 0; i < size_; ++i) {
			if (data == it->data()) {
				return i;
			}
			it = it->next();
		}
		return size_;
    }  // posição de um item na lista
    /**
	 * @brief       Tamanho da Lista 		
	 *
	 * @details 	Verifica o tamanho da lista.
	 * 
	 * @return      Retorna o tamanho da lista.
	 */
    std::size_t size() const {
       return size_;
    }  // tamanho da lista

 private:
    class Node {
     public:
     explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, std::shared_ptr<Node> next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        std::shared_ptr<Node> next() {
            return next_;
        }

        const std::shared_ptr<Node> next() const {
            return next_;
        }

        void next(std::shared_ptr<Node> node) {
            next_ = node;
        }

     private:
        T data_;
        std::shared_ptr<Node> next_{nullptr};
    };

    std::shared_ptr<Node> end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    std::shared_ptr<Node> ptr(int index) {
		if (index >= size_ || index < 0)
			throw std::out_of_range("ERRO POSIÇÃO INVALIDA");

		auto it = head->next();

		for (int i = 0; i < index; ++i)
			it = it->next();

		return it;
    }
    std::shared_ptr<Node> head;
    std::size_t size_;
};

}  // namespace structures

#endif
