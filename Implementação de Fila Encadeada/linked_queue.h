// Copyright [2016] <Felipe Longarai Trisotto>

#include "./linked_list.h"
namespace structures {

/**
 * @brief  		Implementação de uma Estrutura de Fila Encadeada em C++
 */
template<typename T>
class LinkedQueue {
 public:
    LinkedQueue() = default;

    ~LinkedQueue() {
    }
    /**
	 * @brief 		Limpa Fila
	 *
	 * @details 	Destroi todos os elementos da Fila.
	 */
    void clear() {
        list.clear();
    }   // limpar
    /**
	 * @brief       Enfilerar um Elemento		
	 *
	 * @details 	Enfilera um elemento na fila.
	 *
	 * @param       data    Elemento a ser inserido na fila.
	 */
    void enqueue(const T& data) {
        list.push_back(data);
    }  // enfilerar
    /**
	 * @brief 		Retirar um Elemento da Fila
	 * 
	 * @return      Retorna o elemento retirado da fila.
	 */
    T dequeue() {
        return list.pop_front();
    }  // desenfilerar
    /**
	 * @brief       Acessar o Primeiro Elemento da Lista	
	 *
	 * @return      Retorna o primeiro elemento da lista.
	 */
    const T& front() const {
        return list.at(0);
    }  // primeiro dado
    /**
	 * @brief       Acessar Elemento no Final da Fila	
	 *
	 * @return      Retorna o elemento que está no final da fila.
	 */
    const T& back() const {
        return list.at(size()-1);
    }  // último dado
    /**
	 * @brief       Fila Vazia 		
	 *
	 * @details 	Verifica se a fila está vazia.
	 * 
	 * @return      Retorna verdadeiro se a fila está vazia e falso caso
	 *              contrário.
	 */
    bool empty() const {
        return list.empty();
    }  // fila vazia
    /**
	 * @brief       Tamanho da Fila
	 *
	 * @details 	Verifica o tamanho da fila.
	 * 
	 * @return      Retorna o tamanho da fila.
	 */
    std::size_t size() const {
        return list.size();
    }  // tamanho

 private:
    LinkedList<T> list{};
};

}  // namespace structures
