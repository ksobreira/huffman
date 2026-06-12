# Huffman - Compactador e Descompactador de Arquivos

Trabalho prático da disciplina **T198 - Construção e Análise de Algoritmos**
Universidade de Fortaleza (UNIFOR) — Bacharelado em Ciência da Computação
Professor: Bruno Lopes

---

## Sobre o Projeto

Implementação do algoritmo de Codificação de Huffman em C, capaz de compactar e descompactar arquivos de texto.

O algoritmo de Huffman é um método de compressão sem perdas que atribui códigos binários menores aos caracteres mais frequentes e códigos maiores aos menos frequentes, reduzindo o tamanho total do arquivo.

---

## Estrutura do Projeto

```text
huffman/
├── Makefile
├── README.md
├── book.txt
└── src/
    ├── huffman.h       # declarações e structs
    ├── huffman.c       # árvore: node, serialize, deserialize
    ├── heap.c          # min-heap / fila de prioridade
    ├── compress.c      # compactação
    ├── decompress.c    # descompactação
    └── main.c          # entrada do programa
```

---

## Como Funciona

### Compactação

1. Lê o arquivo e conta a frequência de cada caractere.
2. Insere cada caractere no min-heap ordenado pela frequência.
3. Constrói a árvore de Huffman extraindo os dois nós de menor frequência e combinando-os.
4. Gera a tabela de códigos binários percorrendo a árvore.
5. Serializa a árvore no cabeçalho do arquivo `.huff`.
6. Escreve os bits codificados no arquivo de saída.

### Descompactação

1. Lê e deserializa a árvore do cabeçalho do arquivo `.huff`.
2. Lê o total de bits gravado no cabeçalho.
3. Percorre a árvore bit a bit, emitindo o caractere ao chegar em uma folha.
4. Para exatamente ao atingir o total de bits, evitando leitura do padding.

---

## Compilação

```bash
make
```

O binário será gerado em:

```text
bin/huffman
```

Para limpar os arquivos compilados:

```bash
make clean
```

---

## Uso

### Compactar

```bash
./bin/huffman --compactar arquivo.txt
```

Gera o arquivo `arquivo.huff` no mesmo diretório.

### Descompactar

```bash
./bin/huffman --descompactar arquivo.huff
```

Gera o arquivo `descompactado_arquivo.txt` no mesmo diretório.

---

## Exemplo com o Arquivo de Teste

```bash
./bin/huffman --compactar book.txt
# Compactado: book.huff

./bin/huffman --descompactar book.huff
# Descompactado: descompactado_book.txt
```

### Resultado da Compressão

| Arquivo                | Tamanho |
| ---------------------- | ------- |
| book.txt (original)    | 768 KB  |
| book.huff (compactado) | 438 KB  |
| descompactado_book.txt | 768 KB  |

Redução de **43%** no tamanho do arquivo.

O arquivo descompactado é **idêntico** ao original (verificado com `diff`).

---

## Dependências

* GCC
* Make

## Autor
Feito por: Kauam Sobreira
