// Copyright [2016] <Felipe Longarai Trisotto>

#include <memory>
#include <stdexcept>

namespace structures {
/**
 * @brief  		Implementação de uma estrutura de Lista Encadeada Dupla
 *              Circular em C++
 */
template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList() {
        size_= 0;
        head = std::make_shared<Node>(0, nullptr, nullptr);
        head->next(head);
		head->prev(head);
    }
    ~DoublyCircularList() {
        clear();
    }
    /**
	 * @brief 		Limpa Lista
	 *
	 * @details 	Destroi todos os elementos da lista.
	 */
    void clear() {
        while (size_) {
			head->prev(nullptr);
			head = head->next();
			--size_;
		}
		head = std::make_shared<Node>(0, nullptr, nullptr);
		head->next(head);
		head->prev(head);
    }
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
		auto new_ = std::make_shared<Node>(data, head->prev(), head);

		head->prev()->next(new_);

		head->prev(new_);

		++size_;
    }  // insere no fim
    /**
	 * @brief       Inserir no Ini­cio 		
	 *
	 * @details 	Inseri um elemento no ini­cio da lista.
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 */
    void push_front(const T& data) {
        auto new_ = std::make_shared<Node>(data, head, head->next());
		head->next()->prev(new_);
		head->next(new_);
		++size_;
    }  // insere no início
    /**
	 * @brief       Inserir na Posição 		
	 *
	 * @details 	Inseri um elemento na posição passada como parametro. 
	 *
	 * @param       data    Elemento a ser inserido na lista.
	 * @param       index   Posição da lista a ser inserido o elemento.
	 */
    void insert(const T& data, std::size_t index) {
        if (index > size_ || index < 0) {
			throw std::out_of_range("ERRO POSIÇÃO INVALIDA");
        }
		if (index == 0)
			return push_front(data);

		if (index == size_)
			return push_back(data);

		auto it = ptr(index-1);

		auto new_ = std::make_shared<Node>(data, it, it->next());

		it->next()->prev(new_);

		it->next(new_);

		++size_;
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
			return push_front(data);
        }
		int index = 0;

		auto it = head->next();

		while (index < size_ && data > it->data()) {
			index++;
			it = it->next();
		}

		insert(data, index);
    }  // insere em ordem
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
		if (size_ == 1)
			return pop_front();

		if (index == size_-1)
			return pop_back();

		auto it = ptr(index);

		T back = it->data();

		it->prev()->next(it->next());
		it->next()->prev(it->prev());

		--size_;

		return back;
    }  // retira da posição
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
		auto it = ptr(size_-1);

		T back = it->data();

		it->prev()->next(it->next());
		it->next()->prev(it->prev());
        --size_;
		return back;
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
        }
		T back = head->next()->data();

		head->next(head->next()->next());

		--size_;

		return back;
    }  // retira do início
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
    }  // retira específico
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
    }  // contém
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
         return ptr(index)->data();
    }  // getter constante a um elemento
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
    }  // posição de um dado
    /**
	 * @brief       Tamanho da Lista 		
	 *
	 * @details 	Verifica o tamanho da lista.
	 * 
	 * @return      Retorna o tamanho da lista.
	 */
    std::size_t size() const  {
       return size_;
    }  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data) : data_{data}
        {}
        Node(const T& data, std::shared_ptr<Node> next) :
        data_{data}, next_{next}
        {}
        Node(const T& data, std::shared_ptr<Node> prev,
        std::shared_ptr<Node> next) :
        data_{data}, prev_{prev}, next_{next}
        {}

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        std::shared_ptr<Node> prev() {
            return prev_;
        }
        const std::shared_ptr<Node> prev() const {
            return prev_;
        }

        void prev(std::shared_ptr<Node> node) {
            prev_ = node;
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
        std::shared_ptr<Node> prev_;
        /**
        * next    Aponta para proximo elemento da lista.
        */
        std::shared_ptr<Node> next_;
    };
    /**
    * head    Sentinela da lista.
    */
    std::shared_ptr<Node> head;
    /**
    * size_    Ultima posição da lista.
    */
    std::size_t size_;
    std::shared_ptr<Node> ptr(int index) {
		if (index >= size_ || index < 0)
			throw std::out_of_range("ERRO POSIÇÃO INVALIDA");
		if (index < size_/2) {
			auto it = head->next();

			for (int i = 0; i < index; ++i)
				it = it->next();

			return it;
		} else {
			auto it = head->prev();

			for (int i = size_-1; i > index; --i)
				it = it->prev();

			return it;
		}
	}
};

}  // namespace structures
