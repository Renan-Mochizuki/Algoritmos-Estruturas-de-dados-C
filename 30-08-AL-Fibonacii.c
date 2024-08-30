#include <stdio.h>

// Tempo de complexidade O(2^n)
int Fibonacci(int numero) {
  // Critério de parada
  // Os valores realmente retornados serão o 1 e 0 para realizar a soma corretamente
  // E também para se for digitado 0 ou um número negativo
  if (numero <= 1)
    return numero;
  // Como o valor de um dos quadrados de Fibonacci é igual a soma dos dois anteriores
  // Retornamos a soma do valor anterior e anterior do anterior
  return Fibonacci(numero - 1) + Fibonacci(numero - 2);
}

int main(void) {
  int limite = 20;
  for (int i = 1; i < limite; i++) {
    printf("%d, ", Fibonacci(i));
  }
  return 0;
}