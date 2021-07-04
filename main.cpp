#include <iostream>
#include <cmath>
#include <math.h>
#include <fstream>

using namespace std;

//Estrutura do Triângulo
struct tTriangulo{
  float l1, l2, l3, area, perimetro;

};

//Função que calcula e retorna a area
float calculoArea(tTriangulo tri){
  return ((tri.l1*tri.l2)/2);
}

//Função que calcula e retorna a hipotenusa
float calculoHipotenusa(tTriangulo tri){
  tri.l3 = sqrt(pow(tri.l1, 2) + (pow(tri.l2, 2)));
  return tri.l3;
}

//Função que calcula e retorna o perimetro
float calculoPerimetro(tTriangulo tri){
  return(tri.l1+tri.l2+tri.l3);
}

//Criação do Nó
struct tNo{
  tTriangulo info;
  tNo* proximo;
};

tNo* criaNo (tTriangulo item){
  tNo* no = new tNo;

  no -> info = item;
  no -> proximo = NULL;

  return no;
}
/////////////////////

//////////////////// Bloco da lista ////////////////////////////
//Estrutura da lista
struct tLista{
  tNo* primeiro;
  tNo* ultimo;
  tNo* marcador;
  int tamanho = 0;
};

//Função que retorna se a lista está vazia ou não.
bool listaVazia(tLista* pLista){
  return (pLista->tamanho == 0);
}

//Função que verifica se a lista está no final ou não.
bool finalLista(tLista* pLista){
  return (pLista->marcador == 0);
}

//Inclui informação no final da lista.
void incluirNoFim(tLista* pLista, tTriangulo info){
  tNo* no;
  no = criaNo(info);

  if (listaVazia(pLista)){
    pLista -> primeiro = no;
  }else{
    pLista -> ultimo -> proximo = no;
  }

  pLista -> ultimo = no;
  pLista -> marcador = no;
  pLista -> tamanho++;
}
/////////////////////////////////////////////////////////

//Função para imprimir a lista na tela.
void imprimirLista(tLista* pLista){
  pLista -> marcador = pLista -> primeiro;
  int cont = 1;

  //Percorre a lista e imprime as informações do nó na tela
  while(!finalLista(pLista)){
    tTriangulo informacao = pLista -> marcador -> info;

    cout << "Triângulo " << cont << endl;
    cout << "Lado 1 (base): " << informacao.l1 << endl;
    cout << "Lado 2 (Altura): " << informacao.l2 << endl;
    cout << "Lado 3 (hipotenusa): " << informacao.l3 << endl;

    cout << "Área: " << informacao.area << endl;
    cout << "Perimetro: " << informacao.perimetro << endl;

    pLista->marcador = pLista->marcador->proximo;
    cont++;
  }
}

//Impedir bug
void clearInput() {
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


//Salva a lista em um arquivo .txt
void salvarLista(tLista* pLista){
  ofstream arq;

  //Abre o arquivo para gravar as informações dentro dele
  arq.open("triangulo.txt", ios::out);
  
  //Percorre a lista e salva as informações do nó no arquivo.
  pLista -> marcador = pLista -> primeiro;
  while(!finalLista(pLista)){
    tTriangulo triangulo = pLista -> marcador -> info;

    arq << "l1: " << triangulo.l1 << endl;
    arq << "l2: " << triangulo.l2 << endl;
    arq << "l3: " << triangulo.l3 << endl;
    arq << "a: " << triangulo.area << endl;
    arq << "p: " << triangulo.perimetro << endl;

    pLista->marcador = pLista->marcador->proximo;
  }

  arq.close();
}

//Grava os dados na lista para depois salvar
void gravarDados(tLista* pLista, tTriangulo lados){
  int triangulos;

  //Vai determinar quantas vezes o loop vai rodar
  cout << "Digite a quantidade de informacoes que ira digitar: " << endl;
  cin >> triangulos;

  //Loop que grava os dados na struct
  for (int i = 0; i < triangulos; i++){
    cout << "Lado 1(base): ";
    cin >> lados.l1;
    cout << "Lado 2(Altura): ";
    cin >> lados.l2;

    lados.l3 = calculoHipotenusa(lados);
    cout << "Hipotenusa: " << lados.l3 << endl;

    lados.area = calculoArea(lados);
    cout << "Área: " << lados.area << endl;

    lados.perimetro = calculoPerimetro(lados);
    cout << "Perimetro: " << lados.perimetro << endl;

    incluirNoFim(pLista, lados);

  }
  
  salvarLista(pLista);

}

//Ler os dados no arquivo e imprime eles na tela
void lerDados(tLista* pLista, tTriangulo info){
  ifstream arq;
  string text = " ";
  int aux;

  //Abre o arquivo, e armazena as informações dele na lista.
  arq.open("triangulo.txt", ios::in);
  while(!arq.eof()){
    arq >> text;
    if (text == "l1:"){
      arq >> text;
      info.l1 = stof(text);
    }else if(text == "l2:"){
      arq >> text;
      info.l2 = stof(text);
    }else if(text == "l3:"){
      arq >> text;
      info.l3 = stof(text);
    }else if(text == "a:"){
      arq >> text;
      info.area = stof(text);
    }else if(text == "p:"){
      arq >> text;
      info.perimetro = stof(text);
    }

    //Variável auxiliar para garantir que só entre na lista depois que todos os dados forem salvos
    aux++;

    //Inclui no final da lista as informações
    if (aux == 5){
      incluirNoFim(pLista, info);
      aux = 0;
    }
    
  }
  //Fecha o arquivo
  arq.close();

  imprimirLista(pLista);
}

void limparTela(){
  cout << "\033[2J\033[1;1H";
}

int main() {
  tTriangulo trilado;
  bool controle = true;
  
  //Loop principal de controle do programa
  while (controle){
    //Cria uma nova lista
    tLista* lados = new tLista;
    int choice;

    cout << "Menu: " << endl;
    cout << "1. Para salvar os dados em um arquivo" << endl;
    cout << "2. Para ler os dados em um arquivo" << endl;
    cout << "3. Para sair do código" << endl;
    cout << "Digite um numero abaixo para executar a função: " << endl;
    cin >> choice;

    switch (choice){
      case 1:
        //Limpa a tela e chama a função para gravar os dados
        limparTela(); 
        gravarDados(lados, trilado);
        break;
      case 2: 
        //Limpa a tela e chama a função para ler o arquivo
        limparTela();
        lerDados(lados, trilado);
        break;
      case 3:
        //Sai do programa
        limparTela();
        controle = false;
        break;
      default:
        //Limpa a tela e repete o while
        limparTela();
        cout << "Numero inválido" << endl;
        //Impede bug do programa caso o usuário digite algo que não seja um inteiro
        clearInput();
        break;
    }
  }

  return 0;
}