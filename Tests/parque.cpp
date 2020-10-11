#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :
        lotacao(lot), numMaximoClientes(nMaxCli)
{
    vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const
{
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string& nome) const {
    for (unsigned int i = 0; i < clientes.size(); i++) {
        if (clientes[i].nome == nome) {
            return i;
        }
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string& nome) {
    if (clientes.size() == numMaximoClientes) { //check if capacity isn't maxed out
        return false;
    }
    if (posicaoCliente(nome) != -1) { //check if the client isn't already inside
        return false;
    }
    InfoCartao newc;
    newc.nome = nome;
    newc.presente = false;
    clientes.push_back(newc);
    return true;
}

bool ParqueEstacionamento::entrar(const string& nome) {
    int posc = posicaoCliente(nome);
    if (posc == -1) { //check if it's register
        return false;
    }
    if (clientes[posc].presente == true) { //check if vehicle is already inside
        return false;
    }
    if (vagas == 0) { //check if there's space
        return false;
    }
    clientes[posc].presente = true;
    vagas--;
    return true;
}

bool ParqueEstacionamento::retiraCliente(const string& nome) {
    for (vector<InfoCartao>::iterator i = clientes.begin(); i != clientes.end(); i++)
        if ((*i).nome == nome) {
            if ((*i).presente == false) {
                clientes.erase(i);
                return true;
            }
            else {
                return false;
            }
        }
    return false;
}

bool ParqueEstacionamento::sair(const string& nome) {
    int posc = posicaoCliente(nome);
    if (posc == -1) { //check if it's register
        return false;
    }
    if (clientes[posc].presente == false) { //check if vehicle is inside
        return false;
    }
    clientes[posc].presente = false;
    vagas++;
    return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}









/*const ParqueEstacionamento & ParqueEstacionamento::operator += (const ParqueEstacionamento & p2)
{
	for (vector<InfoCartao>::const_iterator it = p2.clientes.begin(); it != p2.clientes.end(); it++) {
		adicionaCliente(it->nome);
		if (clientes.size() == numMaximoClientes) break;
	}
	return *this;
}*/