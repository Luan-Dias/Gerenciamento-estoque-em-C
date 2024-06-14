#include<stdio.h>
#include <stdlib.h>

typedef struct { // Typedef => Definição de um novo tipo de dados
    int cadastro;
    char marca[20];
    char modelo[20];
    int ano;
}dados_veiculo; // Declaração do novo tipo de dados

// Declaração das funções
int menu();
void cadastrar_veiculo();
void remover_veiculo();
void listar_estoque();
int codigo_cadastro();

int main(){

    int opcao, repetir = 1; // Variável incializada como sendo verdadeira
    

    while (repetir == 1){

        opcao = menu();

        switch (opcao){
            case 1:
                cadastrar_veiculo();
                break;
            case 2:
                remover_veiculo();
                break;
            case 3:
                listar_estoque();
                break;
            case 4:
                repetir = 0; // Atualiza a variável para falso e encerra o laço
                break;
        }
    }

    return 0;
}

// Escopo das funções
int menu(){

    int opcao;

        do{

            printf("Barata Veículos\n");
            printf("---------------\n");

            printf("\nO que deseja fazer?\n");
            printf("1 - Cadastrar veículo\n");
            printf("2 - Remover veículo vendido\n");
            printf("3 - Listar estoque\n");
            printf("4 - Sair\n");
            printf("Selecione uma opção: ");
            scanf("%d", &opcao);
            getchar();

            if (opcao < 1 || opcao > 4){
                printf("Opção inválida! Selecione novamente.\n");
            }
        } while (opcao < 1 || opcao > 4);
    return opcao;
}
void cadastrar_veiculo(){

    system("cls");
    FILE *file = fopen("base dados.txt","a"); // "a" => abre um arquivo no modo de inclusão (append)

        if(file == NULL){
            printf ("Erro ao abrir o arquivo!");
            return;
        }

        dados_veiculo veiculo;

                veiculo.cadastro = codigo_cadastro() + 1;

                printf("\nInsira os dado do veiculo\n");

                printf("\nMarca: ");
                scanf("%19[^\n]", veiculo.marca); // "19[^\n]" => Lê 19 caracteres ou até encontrar um \n
                getchar();

                printf("Modelo: ");
                scanf("%19[^\n]", veiculo.modelo);
                getchar();
            
                printf("Ano: ");
                scanf("%d", &veiculo.ano);
                getchar();

            fprintf(file, "%d, %s, %s, %d\n", veiculo.cadastro, veiculo.marca, veiculo.modelo, veiculo.ano);

    fclose(file);

        printf("\nVeículo %03d cadastrado com sucessso!\n", veiculo.cadastro);
        printf("-------------------------------------\n");
}
void remover_veiculo(){
    
    system("cls");
    int codigo, encontrado = 0;

        printf("Insira o código do veiculo que será removido: ");
        scanf("%d", &codigo);
        getchar();

    FILE *file = fopen("base dados.txt", "r");    
    FILE *temp = fopen("temp.txt", "w");

        if (file == NULL || temp == NULL){
            printf("Erro ao abrir o arquivo\n");
            return;
        }

        dados_veiculo veiculo;

            while(fscanf(file, "%d, %19[^,], %19[^,], %d", &veiculo.cadastro, veiculo.marca, veiculo.modelo, &veiculo.ano) != EOF){

                if(veiculo.cadastro == codigo){
                    encontrado = 1;
                    codigo = veiculo.cadastro;
                } else {
                    fprintf(temp, "%d, %s, %s, %d\n", veiculo.cadastro, veiculo.marca, veiculo.modelo, veiculo.ano);
                }
            }

    fclose(temp);
    fclose(file);
    
    remove("base dados.txt");
    rename("temp.txt", "base dados.txt");

        if (encontrado == 1){
            printf("Veiculo %03d removido com sucesso!\n", codigo);
        } else {
            printf("Veiculo não encontrado!\n");
        }
}
void listar_estoque(){
    
    system("cls");
    FILE *file = fopen("base dados.txt","r");

        if(file == NULL){
            printf ("Erro ao abrir o arquivo!");
            return;
        }

        dados_veiculo veiculo;

            printf("Veículos em estoque\n");
            printf("--------------------\n");

        while(fscanf(file, "%d, %19[^,], %19[^,], %d\n", &veiculo.cadastro, veiculo.marca, veiculo.modelo, &veiculo.ano) != EOF){ // != EOF => Lê todas as linhas até o fim do arquivo

            printf("Código de cadastro: %03d\n", veiculo.cadastro);
            printf("Marca: %s\n", veiculo.marca);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Ano: %d\n", veiculo.ano);
            printf("--------------------\n");
        }

            printf("Pressione enter para voltar ao menu...");
            getchar();
            system("cls");

    fclose(file);
}
int codigo_cadastro(){
    
    FILE *file = fopen("base dados.txt","r");

        if(file == NULL){
            printf ("Erro ao abrir o arquivo!");
            return 1;
        }

        dados_veiculo veiculo;
        int codigo = 0;

        while(fscanf(file,"%d, %19[^,], %19[^,], %d", &veiculo.cadastro, veiculo.marca, veiculo.modelo, &veiculo. ano) != EOF){

            if(veiculo.cadastro > codigo){
                codigo = veiculo.cadastro; // Verifica qual o maior código encontrado e atualiza a variável
            }
        }
        
    fclose(file);
    return codigo;
} 