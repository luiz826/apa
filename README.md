# Projeto final da disciplina de Análise e Projeto de Algoritmos

Alunos: Caio Lucas da Silva Chacon, João Paulo do Nascimento Borges e Luiz Fernando Costa dos Santos

## Descrição do problema

Estamos nos aproximando da época do Natal e o Papai Noel está muito atarefado preparando todos os presentes. Além de gerenciar a fabricação, ele ainda tem que tomar uma série de decisões logı́sticas para garantir que todas as crianças recebam seu presente. Visto que ele já tem muito o que fazer, são seus ajudantes que ficam encarregados por realizar as entregas utilizando uma frota de trenós. Como os trenós são extremamente rápidos o maior problema não é a rota de entrega, mas sim decidir quais presentes serão carregados em cada um dos trenós. O problema fica mais complexo pelo fato de que existem presentes que não podem ser carregados juntos por questões variadas (como, por exemplo, fragilidade ou regiões muito diferentes de entrega).

Neste ano, o Papai Noel encarregou um de seus ajudantes de pesquisar alguma forma de resolver o problema de forma mais otimizada e automatizada. Depois de algum tempo pesquisando, o ajudante ficou sabendo da existência de algoritmos de otimização e sugeriu ao Papai Noel que isso poderia ser uma solução interessante. Após contratar um consultor especializado, o problema foi formalizado da seguinte forma:


    “Seja I o conjunto de presentes que devem ser empacotados e k o número de trenós disponı́veis.
    Cada presente i ∈ I possui um determinado peso pi (em kg) e cada trenó possui uma capaci-
    dade máxima Q (em kg). Devido ao fato de que alguns presentes não podem ser empacotados
    no mesmo trenó, é fornecida uma lista L que contem todos os pares de presentes (i, j), tal
    que i, j ∈ I, que são incompatı́veis entre si e que devem ser carregados em trenós diferentes.
    O objetivo do problema é empacotar todos os presentes de forma a minimizar o número
    de trenós utilizados ao mesmo tempo em que são respeitadas as restrições de capacidade e
    incompatibilidade.”

## Execução do Código

```
$ cd /src
$ g++ main.cpp read_file.cpp algorithm.cpp -std=c++17
$ ./a.out
```

A saída irá ser uma tabela na pasta outputs, com os dados pedidos pelo professor

O cálculo do GAP e a criação da tabela estão no arquivo .ipynb, na pasta /GAP.
