# Get Next Line

## 📚 Descrição

**Get Next Line** é um projeto da 42 que implementa uma função para ler uma linha de um arquivo de cada vez. A função é capaz de ler de um file descriptor e retornar a próxima linha disponível, gerenciando eficientemente a memória e buffers.

## 🎯 Objetivos

- Implementar uma função que lê uma linha por vez de um arquivo
- Gerenciar corretamente a memória e buffers
- Trabalhar com diferentes tamanhos de buffer (definido por `BUFFER_SIZE`)
- Suportar múltiplos file descriptors simultaneamente (versão bonus)

## 🔧 Funcionalidades

### Versão Mandatória
- `get_next_line(int fd)` - Lê e retorna a próxima linha de um file descriptor
- Suporte para leitura de arquivos, entrada padrão, etc.
- Gerenciamento automático de memória

### Versão Bonus
- Suporte para múltiplos file descriptors simultaneamente
- Cada file descriptor mantém seu próprio buffer interno

## 📦 Estrutura do Projeto

```
get_next_line/
├── get_next_line.c          # Implementação principal
├── get_next_line_utils.c    # Funções auxiliares
├── get_next_line.h          # Header file
├── get_next_line_bonus.c    # Versão bonus
├── get_next_line_utils_bonus.c
└── get_next_line_bonus.h
```

## 🛠️ Compilação

### Compilação Manual

```bash
# Versão mandatória
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c main.c -o test_gnl

# Versão bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o test_gnl
```

### Com seu próprio main.c

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("arquivo.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## 📖 Uso

```c
#include "get_next_line.h"

int fd = open("arquivo.txt", O_RDONLY);
char *line;

line = get_next_line(fd);  // Lê primeira linha
printf("%s", line);
free(line);

line = get_next_line(fd);  // Lê segunda linha
printf("%s", line);
free(line);

close(fd);
```

## ⚙️ Configuração

O tamanho do buffer é definido em tempo de compilação através da macro `BUFFER_SIZE`:

```bash
gcc -D BUFFER_SIZE=1024 get_next_line.c ...
```

Ou no header file:
```c
# define BUFFER_SIZE 1024
```

## 🔍 Características

- **Eficiência**: Lê apenas o necessário usando buffers
- **Segurança**: Gerenciamento correto de memória, sem vazamentos
- **Flexibilidade**: Funciona com qualquer file descriptor (arquivos, stdin, etc.)
- **Robustez**: Trata erros de leitura adequadamente

## 📝 Notas Importantes

- A função retorna `NULL` quando não há mais linhas para ler ou em caso de erro
- É responsabilidade do usuário liberar a memória retornada com `free()`
- A função adiciona o caractere `\n` no final da linha (exceto na última linha do arquivo)
- O `BUFFER_SIZE` pode ser qualquer valor positivo

## 🏫 42 School

Este projeto é parte do currículo da 42 School e testa conhecimentos em:
- Gerenciamento de memória
- File descriptors
- Algoritmos de buffer
- Estruturas de dados estáticas
