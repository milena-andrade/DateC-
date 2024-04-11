#include <iostream>
#include <locale.h>
#include <string>
#include <ctime>
using namespace std;

class Data {
private:
    int dia;
    int mes;
    int ano;
public:
    Data(int dia, int mes, int ano) {
        this->dia = dia;
        this->mes = mes;
        this->ano = ano;
    }
    Data() {
        this->dia = 0;
        this->mes = 0;
        this->ano = 0;
    }
    void setDia(int dia) {
        this->dia = dia;
    }
    void setMes(int mes) {
        this->mes = mes;
    }
    void setAno(int ano) {
        this->ano = ano;
    }
    int getDia() const {
        return this->dia;
    }
    int getMes() const {
        return this->mes;
    }
    int getAno() const {
        return this->ano;
    }
    string getData() const {
        string sDia = to_string(this->dia);
        string sMes = to_string(this->mes);
        string sAno = to_string(this->ano);
       
        return sDia.insert(0, 2 - sDia.size(), '0') + "/" +
               sMes.insert(0, 2 - sMes.size(), '0') + "/" +
               sAno;
    }
   
    Data* dia_seguinte() const {
        Data *d1 = new Data(this->dia, this->mes, this->ano);
        int diasNoMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};;
        if (d1->ano%4 == 0) {
            diasNoMes[1] = 29;
        }
        d1->dia++;
        if (d1->dia > diasNoMes[d1->mes - 1]) {
            d1->dia = 1;
            d1->mes++;
            if(d1->mes > 12) {
                d1->mes = 1;
                d1->ano++;
            }
        }
        return d1;
    }
};

class Contato {
private:
    string email;
    string nome;
    string telefone;
    Data dtnasc;
public:
    Contato(string email, string nome, string telefone, const Data& dtnasc) :
        email(email), nome(nome), telefone(telefone), dtnasc(dtnasc) {}

    // Construtor default
    Contato() {}

    // Getter e Setter para o email
    string getEmail() const {
        return this->email;
    }

    void setEmail(const string& email) {
        this->email = email;
    }

    // Getter e Setter para o nome
    string getNome() const {
        return this->nome;
    }

    void setNome(const string& nome) {
        this->nome = nome;
    }

    // Getter e Setter para o telefone
    string getTelefone() const {
        return this->telefone;
    }

    void setTelefone(const string& telefone) {
        this->telefone = telefone;
    }

    // Getter e Setter para a data de nascimento
    const Data& getDtNasc() const {
        return this->dtnasc;
    }

    void setDtNasc(const Data& dtnasc) {
        this->dtnasc = dtnasc;
    }

    // Método para calcular a idade com base no ano de 2024
    int idade() const {
        time_t t = time(NULL);
        tm* timePtr = localtime(&t);
        int anoAtual = timePtr->tm_year + 1900; // Adicionando 1900 para obter o ano atual
        int idade = anoAtual - this->dtnasc.getAno();
        if (timePtr->tm_mon + 1 < this->dtnasc.getMes() ||
            (timePtr->tm_mon + 1 == this->dtnasc.getMes() && timePtr->tm_mday < this->dtnasc.getDia())) {
            idade--;
        }
        return idade;
    }
};

int main() {
    // Definindo a localidade para que o método getData() funcione corretamente
    setlocale(LC_ALL, "Portuguese");

    // Criando um vetor de contatos
    Contato contatos[5];

    // Entrada de dados para os contatos
    cout << "Digite os dados dos contatos:\n";
    for (int i = 0; i < 2; i++) {
        cout << "Contato " << i + 1 << ":\n";
        string nome, email, telefone;
        int dia, mes, ano;
        cout << "Nome: ";
        getline(cin, nome);
        cout << "Email: ";
        getline(cin, email);
        cout << "Telefone: ";
        getline(cin, telefone);
        cout << "Data de Nascimento (dia mês ano): ";
        cin >> dia >> mes >> ano;
        cin.ignore(); // Limpar o buffer de entrada
        Data dataNasc(dia, mes, ano);
        contatos[i] = Contato(email, nome, telefone, dataNasc);
        cout << endl;
    }

    // Exibindo os contatos com suas informações
    cout << "Lista de contatos:\n";
    for (int i = 0; i < 2; i++) {
        cout << "Nome: " << contatos[i].getNome() << endl;
        cout << "Email: " << contatos[i].getEmail() << endl;
        cout << "Telefone: " << contatos[i].getTelefone() << endl;
        cout << "Idade: " << contatos[i].idade() << " anos\n";
        cout << endl;
    }

    return 0;
}