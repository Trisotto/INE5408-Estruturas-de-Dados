// Copyright [2016] <Felipe Longarai Trisotto>

/**
 * @brief  		Implementação de uma estrutura de Fila em C++
 */
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

template<typename T>
class ArrayQueue {
    
private:
/**
 * @param  		contents -	Ponteiro para o início da Fila.
 * @param  		size_	-	Armazena o fim da Fila.
 * @param  		max_size_ - Armazena o tamanho da Fila.
 */
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    const static auto DEFAULT_SIZE = 10u;


public:
    /**
	 * @brief  		Construtor Genérico da Classe Fila
 	 *
 	 * @details  	Valor do tamanho definido em uma constante
 	 * @details     como DEFAULT_SIZE.
	 */
    ArrayQueue() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        size_ = -1;
    }
    /**
	 * @brief  		Construtor da classe Fila com Parâmetro
	 *
	 * @param  		max	- Valor para o tamanho da fila.
	 */
    ArrayQueue(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        size_ = -1;
    }
    /**
	 * @brief  		Deleta a fila e libera memória.
	 */
    ~ArrayQueue() {
        delete contents;
    }
    /**
	 * @brief  		Coloca um dado a fila.
	 *
	 * @param  		data - Dado Template.
	 */
    void enqueue(const T& data) {
         if (full()) {
            throw std::out_of_range("FILA CHEIA");
        } else {
            size_++;
            contents[size_] = data;
        }
    }
    /**
	 * @brief  		Retira o valor que está na primeira posição da fila.
	 *
	 * @details  	Retira por ordem de itens colocados na fila, o primeiro
	 * 				colocado é o primeiro a ser retirado. A fila é reorganizada
	 * 				movimentando todos os dados uma posição para frente.
	 */
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("FILA VAZIA");
        } else {
            T aux = contents[0];
            for (int i = 0; i < max_size_ -1; ++i) {
                contents[i] = contents[i + 1];
            }
            size_--;
            return aux;
        }
    }
    /**
	 * @brief      Retorna o último valor adicionado a fila.
	 */
    T& back() {
        if (empty()) {
            throw std::out_of_range("FILA VAZIA");
        } else {
            return contents[size_];
        }
    }
    /**
	 * @brief      Limpa a fila.
	 */
    void clear() {
        size_ = -1;
        contents = new T[max_size_];
    }
    /**
	 * @brief      Retorna a posição do último valor da fila.
	 */
    std::size_t size() {
        return size_ + 1;
    }
    /**
	 * @brief      Retorna a posição do tamanho da fila.
	 */
    std::size_t max_size() {
        return max_size_;
    }
    /**
	 * @brief      Verifica se a fila está vazia.
	 *
	 * @return     Retorna verdadeiro caso a fila esteja vazia.
	 */
    bool empty() {
        return size_ == -1;
    }
    /**
	 * @brief      Verifica se a fila está cheia.
	 *
	 * @return     Retorna verdadeiro caso a fila esteja cheia.
	 */
    bool full() {
        return size_ == max_size_ -1;
    }

};

}
#endif 
